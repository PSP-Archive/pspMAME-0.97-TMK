/* blit.h */

void bitblit_psp( struct mame_bitmap *bitmap, int sx, int sy, int sw, int sh, int dx, int dy );
void bitblit_psp_dma( struct mame_bitmap *bitmap, int sx, int sy, int sw, int sh, int dx, int dy );
void bitblit_psp_mov( struct mame_bitmap *bitmap, int sx, int sy, int sw, int sh, int dx, int dy );
void bitblit_psp_direct( struct mame_bitmap *bitmap, int sx, int sy, int sw, int sh, int dx, int dy );
void bitblit_psp_gu( struct mame_bitmap *bitmap, int sx, int sy, int sw, int sh, int dx, int dy );
void bitblit_psp_clut( struct mame_bitmap *bitmap, int sx, int sy, int sw, int sh, int dx, int dy );
//void bitblit_vga( struct mame_bitmap *bitmap, int sx, int sy, int sw, int sh, int dx, int dy );
//void bitblit_unchained_vga( struct mame_bitmap *bitmap, int sx, int sy, int sw, int sh, int dx, int dy );
//void bitblit_vesa( struct mame_bitmap *bitmap, int sx, int sy, int sw, int sh, int dx, int dy );
unsigned long blit_setup( int dw, int dh, int sbpp, int dbpp, int video_attributes, int xmultiply, int ymultiply, int xdivide, int ydivide,
	int vscanlines, int hscanlines, int flipx, int flipy, int swapxy );
void blit_set_buffers( int pages, int page_size );

#define MAX_X_MULTIPLY 4
#define MAX_Y_MULTIPLY 4

extern UINT32 __attribute__((aligned(16))) blit_lookup_low[ 65536 ];
extern UINT32 blit_lookup_high[ 65536 ];
//extern UINT32 *blit_lookup_low;
//extern UINT32 *blit_lookup_high;
//extern unsigned short int __attribute__((aligned(16))) clut16[65536];
//extern unsigned short __attribute__((aligned(16))) clut16[65536];
extern unsigned short *clut16;
