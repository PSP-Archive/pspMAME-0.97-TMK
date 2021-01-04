#include <sys/types.h>
#include "syscall.h"

#define SBRK_API	1			// API�𗘗p����
//#define SBRK_VRAM	1			// VRAM�𗘗p����

#define USERMEMORY	0x08800000		// ���[�U�������擪�A�h���X
//#define MEMORYSIZE	0x01C00000		// ���[�U�������T�C�Y
#define MEMORYSIZE	0x01800000		// ���[�U�������T�C�Y

#define MEM_USED	0x01010101
#define MEM_FREE	0x0F0F0F0F

#define ISMEMUSED(x)	(MEM_USED ==x->is_available)
#define ISMEMFREE(x)	(MEM_FREE ==x->is_available)
//#define ISUSERMEM(x)	((int)x >=USERMEMORY && (int)x <(USERMEMORY +MEMORYSIZE))
#define ISUSERMEM(x)	((int)x >=(int)alloc_buffer && (int)x <(int)heap_end)

static int has_initialized =0;

struct mem_control_block {
   int is_available;
   int size;
};

#define MCBSZ	sizeof(struct mem_control_block)

#ifdef SBRK_API
static char	*alloc_buffer;
#else
static char	alloc_buffer[12*1024*1024];	// �{���s���W���[���T�C�Y��19M�ʂ����E
#endif
static int	alloc_handle =0;
static int	allocMemSize;
static char	*heap_end;
static int	total =0;

caddr_t _sbrk_psp(int incr);
caddr_t sbrk_psp(int incr);
void malloc_psp_init();
void malloc_psp_term();
void free(void *firstbyte);
void *malloc(size_t numbytes);
void *realloc(void *ptr, size_t size);
void *calloc(size_t __nmemb, size_t __size);
static int getmemsize(void *ptr);

#ifdef SBRK_VRAM
void malloc_vram_init();
void malloc_vram_term();
void free_vram(void *firstbyte);
void *malloc_vram(size_t numbytes);
void *realloc_vram(void *ptr, size_t size);
void *calloc_vram(size_t __nmemb, size_t __size);
int getmemsize_vram(void *ptr);
#endif

caddr_t _sbrk_psp(int incr)
{
char	*prev_heap_end;

	prev_heap_end = heap_end;
//#ifdef SBRK_API
//	if (heap_end + incr >= (USERMEMORY +MEMORYSIZE))
//#else
	if ((total +incr) > allocMemSize)
//#endif
	{
//#ifndef SBRK_VRAM
		printf_("_sbrk_psp:overfllow!!");
//#endif
//		exit(-1);
		return 0;
	}

	heap_end += incr;
	total += incr;

	return (caddr_t) prev_heap_end;
}


caddr_t sbrk_psp(int incr) { return _sbrk_psp(incr); }


void malloc_psp_init()
{
#ifdef SBRK_API
	// �ő�󂫘A���������e�ʂ̎擾
	allocMemSize =sceKernelMaxFreeMemSize();
	allocMemSize =(allocMemSize /(1024 *1024 /8)) *(1024 *1024 /8); //�؂�̂����T�C�Y
	//// �󂫃������̐擪�A�h���X���擾����������
	//allocMemSize =(1024 *1024 *2);
	while(0 >=(alloc_handle =sceKernelAllocPartitionMemory(2, "UserBlock", 0, allocMemSize, 0))
		&& allocMemSize >(1024 *1024 *8)) {
		allocMemSize -=(1024 *1024 /8);
	}
	
	//if (0 <(alloc_handle =sceKernelAllocPartitionMemory(2, "UserBlock", 0, allocMemSize, 0))) {
	if (0 <alloc_handle) {
		alloc_buffer =sceKernelGetBlockHeadAddr(alloc_handle);
		//sceKernelFreePartitionMemory(alloc_handle);
	} else {
		printf_("malloc_psp_init:sceKernelAllocPartitionMemory err!!");
		exit(-1);
	}
	//alloc_handle =0;
	//allocMemSize =MEMORYSIZE -((int)alloc_buffer -USERMEMORY);
#else
	allocMemSize =sizeof(alloc_buffer);
#endif
	heap_end =alloc_buffer;
	total =0;
	
	has_initialized = 1;

#ifdef SBRK_VRAM
	malloc_vram_init();
#endif

}

void malloc_psp_term()
{
	if (alloc_handle)
		sceKernelFreePartitionMemory(alloc_handle);

	alloc_handle =0;
	has_initialized = 0;

#ifdef SBRK_VRAM
	malloc_vram_term();
#endif
}

void free(void *firstbyte)
{
struct	mem_control_block *mcb, *nmcb;
void	*current_location, *next_location;

void	*last_valid_address =sbrk_psp(0);

#ifdef SBRK_VRAM
	free_vram(firstbyte);
#endif
	
	current_location =firstbyte -MCBSZ;
	if (!ISUSERMEM(current_location) || 0 !=((int)current_location % 4)
	  || current_location >=last_valid_address)	// �����ȃA�h���X
		return;
	
	mcb =(struct mem_control_block *)current_location;
	if (ISMEMUSED(mcb)) {
		// �������J��
		mcb->is_available =MEM_FREE;
		next_location =current_location +mcb->size;
		if (last_valid_address ==next_location) // �ŏI�u���b�N�Ȃ�sbrk�J��
			sbrk_psp(-mcb->size);
		else {
			// ���u���b�N���t���[�Ȃ�}�[�W����
			nmcb =(struct mem_control_block *)next_location;
			while(next_location <last_valid_address && ISMEMFREE(nmcb))
			{
				mcb->size +=nmcb->size;
				next_location +=nmcb->size;
				nmcb =(struct mem_control_block *)next_location;
			}
		}
	}
	
	return;
}


void *malloc(size_t numbytes)
{
static void	*managed_memory_start;
void	*current_location, *save_location;
struct	mem_control_block *current_location_mcb;
void	*memory_location;
int	minsize =-1;
void	*last_valid_address;
size_t	size;

	if(! has_initialized) {
		malloc_psp_init();
		managed_memory_start =sbrk_psp(0);
	}
	
	if (0 ==numbytes) return 0;
	
	size =((numbytes +3)&~0x3) +MCBSZ;

	memory_location =save_location =0;
	current_location =managed_memory_start;
	last_valid_address =sbrk_psp(0);
	while(current_location <last_valid_address)
	{
		current_location_mcb =(struct mem_control_block *)current_location;
		
		if(ISMEMFREE(current_location_mcb))
		{
			if(current_location_mcb->size >=size)
			{
				if (-1 ==minsize || minsize >(current_location_mcb->size -size))
				{
					minsize =current_location_mcb->size -size;
					save_location =current_location;
					
					if (current_location_mcb->size ==size)
						break;
				}
			}
		}
		
		current_location +=current_location_mcb->size;
	}
	
	if (save_location)
	{
		current_location_mcb =(struct mem_control_block *)save_location;
		current_location_mcb->is_available =MEM_USED;
		memory_location =save_location +MCBSZ;
		// �]�T������Ε�������
		if (minsize >(MCBSZ*2)) {
			current_location_mcb->size =size;
			void *next_location =save_location +size;
			struct mem_control_block *next_location_mcb =(struct mem_control_block *)next_location;
			next_location_mcb->is_available =MEM_USED;
			next_location_mcb->size =minsize;
			free(next_location +MCBSZ);
		}
		
	} else {
		if (0 !=(memory_location =sbrk_psp(size))) {
			current_location_mcb =memory_location;
			current_location_mcb->is_available =MEM_USED;
			current_location_mcb->size =size;
			
			memory_location +=MCBSZ;
		}

#ifdef SBRK_VRAM
		if (0 ==memory_location)
			memory_location =malloc_vram(numbytes);
#endif
	}
	
	return memory_location;
}


void *realloc(void *ptr, size_t size)
{
char	*newptr;
int	copysize;
	
	if (0 ==ptr)
		return malloc(size);
	
	if (0 ==size) {
		free(ptr);
		return 0;
	}
	
	if (0 ==(newptr =(char *)malloc(size)))
		return 0;

	if (0 !=(copysize =getmemsize(ptr))) {
		copysize =(copysize <size? copysize: size);
		memcpy(newptr, ptr, copysize);
	}

	free(ptr);
	
	return newptr;
}

void *calloc(size_t __nmemb, size_t __size)
{
char	*ptr;
size_t	size =__nmemb *__size;
	
	if (0 ==(ptr =(char *)malloc(size)))
		return 0;
	
	memset(ptr, 0x00, size);
	
	return ptr;
}

static int getmemsize(void *ptr)
{
struct	mem_control_block *mcb;
void	*last_valid_address =sbrk_psp(0);

	mcb =(struct mem_control_block *)(ptr -MCBSZ);
	if (ISUSERMEM(mcb) && 0 ==((int)mcb % 4) && (void *)mcb <last_valid_address) {	// �L���ȃA�h���X
		if (ISMEMUSED(mcb)) {
			return(mcb->size -MCBSZ);
		}
	}

#ifdef SBRK_VRAM
	return(getmemsize_vram(ptr));
#endif

	return(0);
}
