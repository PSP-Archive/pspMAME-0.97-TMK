// primitive graphics for Hello World PSP

//#include "syscall.h"

#define RGB(r,g,b) ((((b>>3) & 0x1F)<<10)|(((g>>3) & 0x1F)<<5)|(((r>>3) & 0x1F)<<0)|0x8000)
#define RGB32(r,g,b) (((b & 0xFF)<<16)|((g & 0xFF)<<8)|((r & 0xFF)<<0)|0xFF000000)
#define COL32(col) ((unsigned int)RGB32((((col >>0) & 0x1F) <<3),(((col >>5) & 0x1F) <<3),(((col >>10) & 0x1F) <<3)))

#define SCREEN_WIDTH  480
#define SCREEN_HEIGHT 272

//#define PIXELSIZE	4					//in short
#define PIXELSIZE	2					//in short
#define LINESIZE	512					//in short
#define FRAMESIZE	(LINESIZE *SCREEN_HEIGHT *PIXELSIZE)	//in byte
//#define PIXELMODE	3					// 0:565 1:5551 2:4444 3:8888
#define PIXELMODE	1					// 0:565 1:5551 2:4444 3:8888


#define MAX_PATH 512		//temp, not confirmed

//480*272 = 60*38
#define CMAX_X 60
#define CMAX_Y 34
#define CMAX2_X 30
#define CMAX2_Y 17
#define CMAX4_X 15
#define CMAX4_Y 8

char *pgGetVramAddr(unsigned long x,unsigned long y);
void pgInit(void);
void pgWaitV(void);
void pgWaitVn(unsigned long count);
void pgScreenFrame(long mode,long frame);
void pgScreenFlip(void);
void pgScreenFlipV(void);
void pgScreenFlush(void);
void pgPrint(unsigned long x,unsigned long y,unsigned long color,const char *str);
void pgPrint2(unsigned long x,unsigned long y,unsigned long color,const char *str);
void pgPrint4(unsigned long x,unsigned long y,unsigned long color,const char *str);
void pgFillvram(unsigned long color);

void pgBitBlt(unsigned long x,unsigned long y,unsigned long w,unsigned long h,unsigned long mag,const unsigned short *d);
void pgBitBlt2(unsigned long x,unsigned long y,unsigned long w,unsigned long h,const unsigned short *d);

void pgPutChar(unsigned long x,unsigned long y,unsigned long color,unsigned long bgcolor,unsigned char ch,char drawfg,char drawbg,char mag);
void pgDrawFrame(unsigned long x1, unsigned long y1, unsigned long x2, unsigned long y2, unsigned long color);
void pgFillBox(unsigned long x1, unsigned long y1, unsigned long x2, unsigned long y2, unsigned long color);
void mh_print(int x,int y,const unsigned char *str,int col);

void pgcInit(void);
void pgcLocate(unsigned long x, unsigned long y);
void pgcColor(unsigned long fg, unsigned long bg);
void pgcDraw(char drawfg, char drawbg);
void pgcSetmag(char mag);
void pgcCls();
void pgcPutchar_nocontrol(const char ch);
void pgcPutchar(const char ch);
void pgcPuthex2(const unsigned long s);
void pgcPuthex8(const unsigned long s);


//static int pga_channel_thread(int args, void *argp);
void pga_channel_thread_callback(int channel, void *buf, unsigned long reqn);
void pgaSetChannelCallback(int channel, void *callback);
int pgaInit(void);
void pgaTermPre(void);
void pgaTerm(void);
int pgaOutBlocking(unsigned long channel,unsigned long vol1,unsigned long vol2,void *buf);


//long�z����R�s�[�B�z�񋫊E��4�o�C�g�A���C������Ă���K�v����
//s,d�͎Q�Ɠn�������ɂȂ�̂ŁA���^�[����͕ύX����Ă���ƍl�����ق����ǂ�
//�R���p�C���̍œK���ɂ���ė\�����Ȃ��R�[�h����������邽�߁A�\���ɒ��ӂ̂��ƁB__memcpy4�̂ق������S�B
//�Ƃ����܂���c�ŏ����Ă��S�R�ς��Ȃ��悤�ȁB��ݶޯ��̂ɁB
static inline void __memcpy4a(unsigned long *d, unsigned long *s, unsigned long c);

static inline void __memcpy4a(unsigned long *d, unsigned long *s, unsigned long c)
{
	unsigned long wk,counter;

	asm volatile (
		"		.set	push"				"\n"
		"		.set	noreorder"			"\n"

		"		move	%1,%4 "				"\n"
		"1:		lw		%0,0(%3) "			"\n"
		"		addiu	%1,%1,-1 "			"\n"
		"		addiu	%3,%3,4 "			"\n"
		"		sw		%0,0(%2) "			"\n"
		"		bnez	%1,1b "				"\n"
		"		addiu	%2,%2,4 "			"\n"

		"		.set	pop"				"\n"

			:	"=&r" (wk),		// %0
				"=&r" (counter)	// %1
			:	"r" (d),		// %2
				"r" (s),		// %3
				"r" (c)			// %4
	);
}
