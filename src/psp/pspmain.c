#include <pspkernel.h>
#include <pspthreadman.h>
#include <psppower.h>
#include <pspctrl.h>
#include <time.h>
#include <sys/stat.h>
#include "driver.h"

//#include "pg.h"
#include "menu.h"

#define PATHLIST_H 20
#define MAXPATH   0x108
int	dlist_num;
int	dlist_start;
int	dlist_curpos;
extern SETTING setting;

int psp_exit =0;

#define DRVIDX_MAX	1000
short drv_idx[DRVIDX_MAX];

extern char *drivers_descriptionj[];

int mame_main (int argc, char **argv);
void Verify_Load(void);
void Verify_Save(void);
unsigned char *getDesc(int idx);

/* Define the module info section */
PSP_MODULE_INFO("PSPMAME", 0, 1, 10);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

PSP_HEAP_SIZE_KB(-512); //-1024

//============================================================
//	HOMEキー関連
//============================================================
int exit_callback(int arg1, int arg2, void *common)
{
	psp_exit =1;

//	malloc_psp_term();
//	malloc_term();
	pgaTerm();

	scePowerSetClockFrequency(222, 222, 111);
	save_config();
	if (1 == setting.rom_verify)
		Verify_Save();

	sceKernelExitGame();

	return 0;
}

int power_callback(int unknown, int pwrflags, void *common)
{
	if(pwrflags & PSP_POWER_CB_POWER_SWITCH){
		scePowerSetClockFrequency(222,222,111);

		save_config();
		if (1 ==setting.rom_verify)
			Verify_Save();
	} else if (pwrflags & PSP_POWER_CB_RESUME_COMPLETE) {
	}

	int cbid = sceKernelCreateCallback("Power Callback", power_callback, 0);
	scePowerRegisterCallback(0, cbid);
}

int CallbackThread(int args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, 0);
	sceKernelRegisterExitCallback(cbid);
	cbid = sceKernelCreateCallback("Power Callback", power_callback, 0);
	scePowerRegisterCallback(0, cbid);

//	sceKernelPollCallbacks();
	sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x12, 0xFA0, 0, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

int gvblank_counter=0;
volatile extern int gdrawed;
void vblank_intr(void *parg)
{
	if (2 ==gdrawed) {
		sceGuSwapBuffers();
		gdrawed =0;
	} else if (20 ==gdrawed) {
		pgScreenFlip();
		gdrawed =0;
	}

	gvblank_counter ++;
}

int SetupVblankCallback(void)
{
	int no =0;
	void *arg =0;

	gvblank_counter =0;

	sceKernelRegisterSubIntrHandler(PSP_VBLANK_INT, no, vblank_intr, arg);
	sceKernelEnableSubIntr(PSP_VBLANK_INT, no);
}

int TermVblankCallback(void)
{
	int no =0;

	sceKernelDisableSubIntr(PSP_VBLANK_INT, no);
	sceKernelReleaseSubIntrHandler(PSP_VBLANK_INT, no);
}

static char curdir[MAXPATH];

char *getCrDir(void) {
	return curdir;
}

int chdir(const char *path)
{
	if (strchr(path, ':')) {
		strcpy(curdir, path);
	} else {
		return -1; //FIXME
	}

	int curdir_length = strlen(curdir);
	curdir[curdir_length++] = '/';
	curdir[curdir_length] = 0;

	return 0;
}

//============================================================
//	GUI
//============================================================
#define REPEAT_TIME 0x40000
static unsigned int control_bef_ctl  = 0;
static unsigned int control_bef_tick = 0;

unsigned long Read_Key(void) {

	SceCtrlData ctl;

	sceCtrlReadBufferPositive(&ctl, 1);

	if (ctl.Buttons == control_bef_ctl) {
		if ((ctl.TimeStamp - control_bef_tick) > REPEAT_TIME) {
			return control_bef_ctl;
		}
		return 0;
	}

	control_bef_ctl  = ctl.Buttons;
	control_bef_tick = ctl.TimeStamp;

	return control_bef_ctl;
}

void Get_DriverList(int mode) {
	int i;

	dlist_num = 0;

	for (i =0; drivers[i]; i++)
		dlist_num++;

	if (0 ==mode) // no check
	{
		for (i =0; i <dlist_num; i++)
			drv_idx[i] =i;

	} else if (1 ==mode) // 保存情報
	{
		for (i =0;i <DRVIDX_MAX; i++) {
			if (0 >drv_idx[i] || i >=dlist_num)
				break;
		}
		dlist_num =i;

	} else if (2 ==mode) // 起動時チェック
	{
		dlist_num =Verify_Roms();

	}
}

void Draw_All(void)
{
	int	i, col;
	char wk[20];

	sprintf(wk, "(%d/%d)", dlist_curpos+1, dlist_num);

	psp_frame(wk, 0);

	// ゲームリスト
	i = dlist_start;
	while (i<(dlist_start+PATHLIST_H)) {
		if (i<dlist_num) {
			col = setting.color[2];
			if (i==dlist_curpos) {
				col = setting.color[3];
			}
//			mh_print(32, ((i-dlist_start)+2)*10, (unsigned char *)drivers[i]->name, col);
//			mh_print(32, ((i-dlist_start)+4)*10, (unsigned char *)drivers[i]->description, col);
//			mh_print(32, ((i-dlist_start)+4)*10, (unsigned char *)drivers[(int)drv_idx[i]]->description, col);
			mh_print(32, ((i-dlist_start)+4)*10, getDesc((int)drv_idx[i]), col);
		}
		i++;
	}
	pgScreenFlipV();
}

void Verify_Confirm(void) {

	psp_frame(0, 0);

	mh_print(40,80, (unsigned char *)"ROMチェックを実行します。", setting.color[3]);
	mh_print(40,90, (unsigned char *)"MSにデータが存在するものだけをリスト表\示します。", setting.color[3]);

	mh_print(40,160, (unsigned char *)"実行：○  キャンセル：×", setting.color[3]);
	pgScreenFlipV();
}

void Draw_Confirm(void) {
//	pgFillvram(0);
	psp_frame(0, 0);

	mh_print(40, 70, getDesc((int)drv_idx[dlist_curpos]), setting.color[3]);
	mh_print(50, 90, (unsigned char *)drivers[(int)drv_idx[dlist_curpos]]->name, setting.color[3]);
	mh_print(50, 100, (unsigned char *)drivers[(int)drv_idx[dlist_curpos]]->description, setting.color[3]);
	mh_print(40,120, (unsigned char *)"を実行します。", setting.color[3]);

	mh_print(40,160, (unsigned char *)"実行：○  キャンセル：×", setting.color[3]);
	pgScreenFlipV();
}

int Confirm_Control(void) {
	unsigned long key;

	while(1) {
		while(1) {
			key = Read_Key();
			if (key != 0) break;
			pgWaitV();
		}

		if (key & PSP_CTRL_CIRCLE) {
			return 1;
		}
		if (key & PSP_CTRL_CROSS) {
			return 0;
		}
	}
}

int Control(void) {
	unsigned long key;
//	int i;

	// wait key
	while(1) {
		key = Read_Key();
		if (key != 0) break;
		pgWaitV();
	}

	if (key & PSP_CTRL_UP) {
		if (dlist_curpos > 0) {
			dlist_curpos--;
			if (dlist_curpos < dlist_start) { dlist_start = dlist_curpos; }
		}
	}
	if (key & PSP_CTRL_DOWN) {
		if (dlist_curpos < (dlist_num-1)) {
			dlist_curpos++;
			if (dlist_curpos >= (dlist_start+PATHLIST_H)) { dlist_start++; }
		}
	}
	if (key & PSP_CTRL_LEFT) {
		dlist_curpos -= PATHLIST_H;
		if (dlist_curpos <  0)          { dlist_curpos = 0;           }
		if (dlist_curpos < dlist_start) { dlist_start = dlist_curpos; }
	}
	if (key & PSP_CTRL_RIGHT) {
		dlist_curpos += PATHLIST_H;
		if (dlist_curpos >= dlist_num) { dlist_curpos = dlist_num-1; }
		while (dlist_curpos >= (dlist_start+PATHLIST_H)) { dlist_start++; }
	}

	if (key & PSP_CTRL_CIRCLE) {
		return 2;
	}
	if (key & PSP_CTRL_LTRIGGER) {
		return 3;
	}
	if (key & PSP_CTRL_TRIANGLE) {
		return 4;
	}

	return 0;
}

//============================================================
//	メイン
//============================================================
int main(int argc, char *argv[])
{
	int game_index;
	int res = 0;
	char *_argv[5];
	int _argc =0;
	int sv_mode;

	// Initialize
//	pgaInit();
	SetupCallbacks();

	pgcInit();
	pgScreenFrame(2,0);

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

	// カレントパスの取得
	char sPath[40], *pPtr;
	strcpy(sPath, argv[0]);
	pPtr =strrchr(sPath, '/');
	*pPtr = 0;
	chdir(sPath);

	_argv[_argc++] =argv;
	//_argv[_argc++] ="-log";
    sceIoChdir(getCrDir());

	// コンフィグ＆BGのロード
	load_config();
	load_menu_bg();
	bgbright_change();

	if (1 ==setting.rom_verify)
		Verify_Load();

	Get_DriverList(setting.rom_verify);
	dlist_start  = 0;
	dlist_curpos = 0;

	while(1) {
		Draw_All();
		switch(Control()) {
		case 2:
			Draw_Confirm();
			if (Confirm_Control()!=0) {
				pgFillvram(0);
				pgScreenFlipV();
				pgFillvram(0);
				pgScreenFlipV();
				pgScreenFrame(1,0);
				cls_();

				_argv[_argc] =drivers[(int)drv_idx[dlist_curpos]]->name;

				if(setting.cpu_clock==0)
					scePowerSetClockFrequency(222,222,111);
				else if(setting.cpu_clock==1)
					scePowerSetClockFrequency(266,266,133);
				else if(setting.cpu_clock==2)
					scePowerSetClockFrequency(333,333,166);

				if (setting.vsync)
					SetupVblankCallback();

				psp_exit =0;

				res = mame_main(_argc+1, _argv);
				//res = run_game (game_index);

				if (setting.vsync)
					TermVblankCallback();

				scePowerSetClockFrequency(222,222,111);
//				malloc_psp_term();
//				malloc_term();
//				_sbrk_term();

				Confirm_Control();

				pgScreenFrame(2,0);
			}
			break;

		case 3:
			sv_mode =setting.rom_verify;

			psp_menu();

			if (sv_mode !=setting.rom_verify) // 変更
			{
				if (0 ==setting.rom_verify) // ALL
				{
					Get_DriverList(0);
					dlist_start  = 0;
					dlist_curpos = 0;
					break;
				}

				if (2 !=setting.rom_verify) // ALL or 保存
					break;
			} else
				break;

		case 4:
			Verify_Confirm();
			if (Confirm_Control()!=0) {
				dlist_num =Verify_Roms();
				dlist_start  = 0;
				dlist_curpos = 0;
			}
			break;
		}
	}

	return 0;
}

void exit(int i)
{
	pgaTerm();

	pgScreenFlip();
	Confirm_Control();

//	_exit(0);

	sceKernelExitGame();
}

void raise(int i)
{
//	exit(i);
	sceKernelExitGame();
}

int printf2_( const char *format, const char *format2)
{
int rtn;

	rtn =printf2nw_( format, format2);

	Confirm_Control();
	return(rtn);
}

int printf2nw_( const char *format, const char *format2)
{
char buff[1000];

	strcpy(buff, format);
	strcat(buff, ":");
	strcat(buff, format2);

	return(printfnw_(buff));
}

int printf_( const char *format)
{
int rtn;

	rtn =printfnw_(format);

	Confirm_Control();
	return(rtn);
}

static int mcls =0;
int cls_()
{
	mcls =1;
	pgFillvram(0);
}

int printfnw_(const char *format)
{
int rtn;

	rtn =printflow(format, strlen(format), mcls);
//	fflush_();
	mcls =0;
	return rtn;
}

static int printbuflen =0;
int printflow(const char *format, int len, int flush)
{
static int sx =0, sy =0, syy =0;
int i,j,k;
char buf[100];

//	if (!printbuflen) {
//		pgFillvram(0);
//		sx =sy =0;
//	}
	if (flush)
		sx =sy =syy =0;

//	for(i=sy, k=0; i <27 && k <strlen(format) && k <len; i++)
	for(k=0; k <strlen(format) && k <len;)
	{
		for(j=0;(sx+j) <96 && format[k] !='\n' && format[k] !='\r' && k <strlen(format) && k <len; j++, k++)
			buf[j] =format[k];
		buf[j] =0x00;
		mh_print(sx *5, sy*10, buf, RGB(255,255,255));
		sx +=j;
		if (95 <=sx) {
			sx =0;
			sy ++;
			syy ++;
		}
		if ('\n' ==format[k] || '\r' ==format[k]) {
			sx =0;
			sy ++;
			syy ++;
			k ++;
		}

		if (27 ==sy) {
			if (27 ==syy) { // 一画面おきにスクロールを止める
				Confirm_Control();
				syy =0;
			}

			pgWaitV();
			pgBitBlt2(0, 0, LINESIZE, 26*10, pgGetVramAddr(0, 10));
			pgFillBox(0, 26*10, SCREEN_WIDTH-1, 27*10-1, 0);
			pgScreenFlush();

			sy --;
		}

//		printbuflen +=j;
	}

//	if (flush) {
//		fflush_();
//		printbuflen =0;
//		pgScreenFlipV();
//		Confirm_Control();
//	}

	pgWaitV();
	pgScreenFlush();

	return(k);
}

static int fl_mode =1;
int fflushmode_(int fast)
{
	fl_mode =fast;
}

int printflen_(const char *format, int len)
{
	return(printflow(format, len, fl_mode));
}

int fflush_(void)
{
	if (printbuflen) {
		pgScreenFlipV();
		if (0 ==fl_mode)
			Confirm_Control();
	}
	printbuflen =0;

	return(0);
}

//int puts( const char *string )
//{
//	mh_print(0, 0, (unsigned char *)string, RGB(255,255,255),0,0);
//
//	return(1);
//}
//
//int *__errno() {
//	return 0;
//}

int Verify_Roms()
{
char  *paths[] ={ "roms", "ms0:/psp/game/mamepsp/roms", 0 };
int i, j;
int idx =0;
struct stat st;

	for (i =0; drivers[i]; i++) {
		for (j =0; paths[j]; j++) {
			char path[40];
			sprintf(path, "%s/%s.zip", paths[j], drivers[i]->name);
			if (stat(path, &st) == 0) {
				drv_idx[idx ++] =i;
				break;
			}

			sprintf(path, "%s/%s", paths[j], drivers[i]->name);
			if (stat(path, &st) == 0) {
				if (S_ISDIR(st.st_mode)) {
					drv_idx[idx ++] =i;
					break;
				}
			}
		}
	}

	drv_idx[idx] =-1;

	return idx;
}

void Verify_Load(void)
{
char path[40];
char *p;
int fd;

	strcpy(path, getCrDir());
	p = strrchr(path, '/')+1;
	strcpy(p, "PSPMAME.VRF");

	drv_idx[0] =-1;

	fd = sceIoOpen(path, PSP_O_RDONLY, 0777);
	if(fd >= 0) {
		sceIoRead(fd, &drv_idx, sizeof(drv_idx));
		sceIoClose(fd);
	}
}

void Verify_Save(void)
{
char path[40];
char *p;
int fd;

	strcpy(path, getCrDir());
	p = strrchr(path, '/')+1;
	strcpy(p, "PSPMAME.VRF");

	fd = sceIoOpen(path, PSP_O_CREAT | PSP_O_WRONLY | PSP_O_TRUNC, 0777);
	if(fd >= 0) {
		sceIoWrite(fd, &drv_idx, sizeof(drv_idx));
		sceIoClose(fd);
	}
}

unsigned char *getDesc(int idx)
{
	if (0x00 !=drivers_descriptionj[0] && 0 <strlen(drivers_descriptionj[idx]))
		return(drivers_descriptionj[idx]);
	else
		return(drivers[idx]->description);

}
