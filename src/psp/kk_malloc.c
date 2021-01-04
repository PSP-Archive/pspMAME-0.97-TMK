#include "syscall.h"

#define HANDLE_MAX	1000

typedef struct _MHDL {
	int Hdl;
	size_t Size;
	void *Ptr;
} mhandle;
static mhandle mHdl[HANDLE_MAX];

void *malloc_kk(size_t __size);
void *calloc_kk(size_t __nmemb, size_t __size);
void *realloc_kk(void *__r, size_t __size);
void free_kk(void *__r);
int getmemsize_kk(void *ptr);
static void p_init(void);
static int getFreeHandle(void);
static int PtrToHandle(void *pPtr);

static int mInit =0;

void * malloc_kk(size_t __size)
{
int hIdx, hBlk;
void *ptr;

	p_init();

	if (0 ==__size) return 0;

	if (-1 ==(hIdx =getFreeHandle()))
		return 0;

//	if (0 >=(hBlk =sceKernelAllocPartitionMemory(2, "UserBlock", 0, __size, 0)))
	if (0 >=(hBlk =sceKernelAllocPartitionMemory(1, "KernelBlock", 0, __size, 0)))
		return 0;

	if (0 ==(ptr =sceKernelGetBlockHeadAddr(hBlk)))
		return 0;

	mHdl[hIdx].Hdl =hBlk;
	mHdl[hIdx].Size =__size;
	mHdl[hIdx].Ptr =ptr;

	return(ptr);
}

void * calloc_kk(size_t __nmemb, size_t __size)
{
char *ptr;
size_t size =__nmemb *__size;

	if (0 ==(ptr =(char *)malloc_kk(size)))
		return 0;

	memset(ptr, 0x00, size);

	return ptr;
}

// �Ċ��蓖�� (����шړ�) ���ꂽ ������ �u���b�N�ւ� void �|�C���^��Ԃ��܂��B
//�T�C�Y�� 0 �ɂ��A�o�b�t�@������ NULL �ȊO�ɂ����ꍇ�A
//�܂��̓������s���̂��߃u���b�N���w�肳�ꂽ�T�C�Y�Ɋg���ł��Ȃ��ꍇ�́A�߂�l�� NULL �ɂȂ�܂��B
//�O�҂̏ꍇ�͌��̃u���b�N��������܂����A��҂̏ꍇ�͌��̃u���b�N��ύX���܂���B

void *realloc_kk(void *__r, size_t __size)
{
char *ptr;
size_t size;

	if (0 ==__r)
		return malloc_kk(size);

	if (0 ==__size) {
		free_kk(__r);
		return 0;
	}

	if (0 ==(ptr =(char *)malloc_kk(__size)))
		return 0;

	if (0 !=(size =getmemsize_kk(__r))) {
		size =size <__size? size: __size;
		memcpy(ptr, __r, size);
	}

	free_kk(__r);

	return(ptr);
}

void free_kk(void *__r)
{
int hIdx;

	if (0 ==__r)
		return;

	if (0 <=(hIdx =PtrToHandle(__r))) {
		sceKernelFreePartitionMemory(mHdl[hIdx].Hdl);

		mHdl[hIdx].Hdl =0;
		mHdl[hIdx].Size =0;
		mHdl[hIdx].Ptr =0;
	}
}

static void p_init(void)
{
	if (1 ==mInit) return;

	for(int i=0; i <HANDLE_MAX; i++) {
		mHdl[i].Hdl =0;
		mHdl[i].Size =0;
		mHdl[i].Ptr =0;
	}

	mInit =1;
}

void malloc_kk_term()
{
	for(int i=0; i <HANDLE_MAX; i++) {
		if (mHdl[i].Hdl)
			free_kk(mHdl[i].Ptr);
}

int getmemsize_kk(void *ptr)
{
int hIdx;

	if (0 <=(hIdx =PtrToHandle(ptr)))
		return(mHdl[hIdx].Size);

	return(0);
}

static int getFreeHandle(void)
{
	for(int i=0; i <HANDLE_MAX; i++)
		if (0 ==mHdl[i].Hdl)
			return i;

	printf_("malloc_kk:getFreeHandle HANDLE_MAX over!!");

	return -1;
}

static int PtrToHandle(void *pPtr)
{
	for(int i=0; i <HANDLE_MAX; i++)
		if (pPtr ==mHdl[i].Ptr && 0 !=mHdl[i].Hdl)
			return i;

	return -1;
}
