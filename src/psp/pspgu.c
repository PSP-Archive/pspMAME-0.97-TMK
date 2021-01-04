#include <pspgu.h>

//#include "syscall.h"

//static unsigned int __attribute__((aligned(16))) list[262144];

/*struct Vertex
{
	float u,v;
	float x,y,z;
};*/
struct Vertex
{
	unsigned short u, v;
//	unsigned short color;
	short x, y, z;
};

#define VRAM_TOP (0x04000000)
#define VRAM_SIZE (0x00200000)
#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
//#define PIXEL_SIZE (4) /* change this if you change to another screenmode */
#define PIXEL_SIZE (2) /* change this if you change to another screenmode */
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define CLUT_SIZE  (65536 *PIXEL_SIZE)
#define LIST_SIZE  (256 *4)

#define SLICE_SIZE 128

static unsigned int *list =(VRAM_TOP +VRAM_SIZE) -CLUT_SIZE -LIST_SIZE;
unsigned short int *clut16 =(VRAM_TOP +VRAM_SIZE) -CLUT_SIZE;

//unsigned int __attribute__((aligned(16))) clut16[65536];
//unsigned short int __attribute__((aligned(16))) clut16[65536];
extern unsigned int __attribute__((aligned(16))) blit_lookup_low[ 65536 ];

extern int video_flipx;
extern int video_flipy;
extern int video_swapxy;

static int mvidx, msx, msy, msw, msh;
struct Vertex mvertices[16];

// Vertex設定
int psp_gu_setup_vertices(int sx, int sy, int sw, int sh, int dx, int dy, float zx, float zy)
{
	int j;

	msx =sx; msy =sy; msw =sw; msh =sh;

	mvidx =0;
	// xevius normal:video_flipx video_swapxy  rotate:video_flipx video_flipy
	for (j =0; j <sw-SLICE_SIZE; j +=SLICE_SIZE)
	{
		struct Vertex* vertices = &mvertices[mvidx];
		mvidx+=2;
		
		if( video_flipx || video_swapxy) {
			vertices[0].u = sx+j+SLICE_SIZE;
			vertices[1].u = sx+j;
		} else {
			vertices[0].u = sx+j;
			vertices[1].u = sx+j+SLICE_SIZE;
		}
		
		if( video_flipy || video_swapxy) {
			vertices[0].v = sy+sh;
			vertices[1].v = sy;
		} else {
			vertices[0].v = sy;
			vertices[1].v = sy+sh;
		}
		
		if (video_swapxy) {
			if( video_flipx) {
				vertices[0].x = dy; vertices[1].x = dy+sh;
				vertices[0].y = dx+j+SLICE_SIZE; vertices[1].y = dx+j;
			} else if ( video_flipy) {
				vertices[0].x = dy+sh; vertices[1].x = dy;
				vertices[0].y = dx+sw  -j-SLICE_SIZE; vertices[1].y = dx+sw -j;
			}
		} else {
			if( video_flipx) {
				vertices[0].x = dx+sw -j-SLICE_SIZE; vertices[1].x = dx+sw -j;
			}else {
				vertices[0].x = dx+j; vertices[1].x = dx+j+SLICE_SIZE;
			}
			vertices[0].y = dy; vertices[1].y = dy+sh;
		}
		// zoom
		vertices[0].x =vertices[0].x *zx+0.5f; vertices[1].x =zx *vertices[1].x+0.5f;
		vertices[0].y =vertices[0].y *zy+0.5f; vertices[1].y =zy *vertices[1].y+0.5f;
		
		vertices[0].z = 0; vertices[1].z = 0;
	}
	
	if (j <sw) { // 余り
		struct Vertex* vertices = &mvertices[mvidx];
		mvidx+=2;
		
		if( video_flipx || video_swapxy) {
			vertices[0].u = sx+j+(sw-j);
			vertices[1].u = sx+j;
		} else {
			vertices[0].u = sx+j;
			vertices[1].u = sx+j+(sw-j);
		}
		
		if( video_flipy || video_swapxy) {
			vertices[0].v = sy+sh;
			vertices[1].v = sy;
		} else {
			vertices[0].v = sy;
			vertices[1].v = sy+sh;
		}
		
		if (video_swapxy) {
			if( video_flipx) {
				vertices[0].x = dy; vertices[1].x = dy+sh;
				vertices[0].y = dx+j+(sw-j); vertices[1].y = dx+j;
			} else if ( video_flipy) {
				vertices[0].x = dy+sh; vertices[1].x = dy;
//				vertices[0].y = dx+j; vertices[1].y = dx+j+(sw-j);
				vertices[0].y = dx+sw -j-(sw-j); vertices[1].y = dx+sw -j;
			}
		} else {
			if( video_flipx) {
				vertices[0].x = dx+sw -j-(sw-j); vertices[1].x = dx+sw -j;
			}else {
				vertices[0].x = dx+j; vertices[1].x = dx+j+(sw-j);
			}
			vertices[0].y = dy; vertices[1].y = dy+sh;
		}
		
		// zoom
		vertices[0].x =vertices[0].x *zx+0.5f; vertices[1].x =zx *vertices[1].x+0.5f;
		vertices[0].y =vertices[0].y *zy+0.5f; vertices[1].y =zy *vertices[1].y+0.5f;
		
		vertices[0].z = 0; vertices[1].z = 0;
	}
	
	return(1);
}

// 描画用Vertexの設定(full fit)
int psp_gu_setup_full_fit(int sx, int sy, int sw, int sh)
{
	int j;
	int dx, dy;
	float zx, zy;
	
	if(video_swapxy) {
		dx =0;
		dy =0;
		zx =(float)SCR_HEIGHT /sh;
		zy =(float)SCR_WIDTH /sw;
	} else {
		dx =0;
		dy =0;
		zx =(float)SCR_WIDTH /sw;
		zy =(float)SCR_HEIGHT /sh;
	}
	
	return(psp_gu_setup_vertices(sx, sy, sw, sh, dx, dy, zx, zy));
}

// 描画用Vertexの設定(fit)
int psp_gu_setup_fit(int sx, int sy, int sw, int sh)
{
	int j;
	int dx, dy;
	float zoom;
	
	if(video_swapxy) {
		dx =SCR_HEIGHT -sw;
		dy =SCR_WIDTH -sh;
		if (dx <dy) {
			zoom =(float)SCR_HEIGHT /sw;
			dx =0;
			dy =(SCR_WIDTH -sh*zoom) /2;
		} else {
			zoom =(float)SCR_WIDTH /sh;
			dx =(SCR_HEIGHT -sw*zoom) /2;
			dy =0;
		}
		
	} else {
		dx =SCR_WIDTH -sw;
		dy =SCR_HEIGHT -sh;
		if (dx <dy) {
			zoom =(float)SCR_WIDTH /sw;
			dx =0;
			dy =(SCR_HEIGHT -sh*zoom) /2;
		} else {
			zoom =(float)SCR_HEIGHT /sh;
			dx =(SCR_WIDTH -sw*zoom) /2;
			dy =0;
		}
	}
	
	return(psp_gu_setup_vertices(sx, sy, sw, sh, dx, dy, zoom, zoom));
}

// 描画用Vertexの設定(zoom)
int psp_gu_setup_zoom(int sx, int sy, int sw, int sh)
{
	int j;
	int dx, dy;
	float zoom;
	
	if(video_swapxy) {
		if (sw >SCR_HEIGHT || sh >SCR_WIDTH) // ソースがサイズオーバーの場合、ノーマルに
			return(psp_gu_setup(sx, sy, sw, sh));
		
		dx =SCR_HEIGHT -sw;
		dy =SCR_WIDTH -sh;
		if (dx <dy) {
			zoom =(float)SCR_HEIGHT /sw;
			dx =0;
			dy =(SCR_WIDTH -sh*zoom) /2;
		} else {
			zoom =(float)SCR_WIDTH /sh;
			dx =(SCR_HEIGHT -sw*zoom) /2;
			dy =0;
		}
		
	} else {
		if (sw >SCR_WIDTH || sh >SCR_HEIGHT) // ソースがサイズオーバーの場合、ノーマルに
			return(psp_gu_setup(sx, sy, sw, sh));
		
		dx =SCR_WIDTH -sw;
		dy =SCR_HEIGHT -sh;
		if (dx <dy) {
			zoom =(float)SCR_WIDTH /sw;
			dx =0;
			dy =(SCR_HEIGHT -sh*zoom) /2;
		} else {
			zoom =(float)SCR_HEIGHT /sh;
			dx =(SCR_WIDTH -sw*zoom) /2;
			dy =0;
		}
	}
	
	return(psp_gu_setup_vertices(sx, sy, sw, sh, dx, dy, zoom, zoom));
}

// 描画用Vertexの設定
int psp_gu_setup(int sx, int sy, int sw, int sh)
{
	int j;
	int dx, dy;

	if(video_swapxy) {
		if (sw >SCR_HEIGHT) {
			sx +=(sw -SCR_HEIGHT) /2;
			sw =SCR_HEIGHT;
			dx =0;
		} else {
			dx =(SCR_HEIGHT -sw) /2;
		}
		if (sh >SCR_WIDTH) {
			sy +=(sh -SCR_WIDTH) /2;
			sh =SCR_WIDTH;
			dy =0;
		} else {
			dy =(SCR_WIDTH -sh) /2;
		}
	} else {
		if (sw >SCR_WIDTH) {
			sx +=(sw -SCR_WIDTH) /2;
			sw =SCR_WIDTH;
			dx =0;
		} else {
			dx =(SCR_WIDTH -sw) /2;
		}
		if (sh >SCR_HEIGHT) {
			sy +=(sh -SCR_HEIGHT) /2;
			sh =SCR_HEIGHT;
			dy =0;
		} else {
			dy =(SCR_HEIGHT -sh) /2;
		}
	}
	
	return(psp_gu_setup_vertices(sx, sy, sw, sh, dx, dy, 1.0f, 1.0f));
}

static int mfirsttime =1;
volatile int gdrawed =0;
int psp_gu_blit_clut(unsigned char *p_src, int bw, int bh)
{
	int j;

	if (0 !=gdrawed)
		return(0);

	bh = (bh +255) & ~255;	// テクスチャの境界調整

//	if (!mfirsttime) {
//		// wait for next frame
//		sceGuSync(0,0);
//		
//		sceGuSwapBuffers();
//	}
	
	sceGuStart(GU_DIRECT,list);
	
	// clear screen
	sceGuClearColor(0xff00ff);
	sceGuClear(GU_COLOR_BUFFER_BIT);
	
	// setup CLUT texture
	sceGuTexMode(GU_PSM_T16, 0, 0, 0); // 16-bit image
	sceGuTexImage(0, bw, bh, bw, p_src);
	sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGB);
	sceGuTexFilter(GU_LINEAR,GU_LINEAR);
	sceGuTexScale(1.0f, 1.0f);
	sceGuTexOffset(0.0f, 0.0f);
	
	sceGuClutMode(GU_PSM_5551, 0, 0xff, 0); // 16-bit palette, shift, mask, offset
	sceGuClutLoad((256/8), clut16); // upload 8192*8 entries (65536)
	
	sceGuAmbientColor(0xffffffff);
	
	// render sprite
	sceGuColor(0xffffffff);
	
/*	for (j =0; j <mvidx; j +=2)
	{
		struct Vertex* vertices = (struct Vertex*)sceGuGetMemory(2 * sizeof(struct Vertex));
		vertices[0] =mvertices[j];
		vertices[1] =mvertices[j+1];
		sceGuDrawArray(GU_SPRITES,GU_TEXTURE_16BIT|GU_VERTEX_16BIT|GU_TRANSFORM_2D,2,0,vertices);
	}*/

	struct Vertex* vertices = (struct Vertex*)sceGuGetMemory(mvidx * sizeof(struct Vertex));
	for (j =0; j <mvidx; j ++)
		vertices[j] =mvertices[j];
	sceGuDrawArrayN(GU_SPRITES,GU_TEXTURE_16BIT|GU_VERTEX_16BIT|GU_TRANSFORM_2D, 2, mvidx/2, 0, vertices);
	
	// wait for next frame
	sceGuFinish();
//	sceGuSync(0,0);
	
//	sceGuSwapBuffers();

	mfirsttime =0;
	gdrawed =1;
}

// 16bit Source blit
int psp_gu_blit(unsigned char *p_src, int bw, int bh)
{
int i, j;

	if (0 !=gdrawed)
		return(0);
	
	unsigned short *src =(unsigned short *)((unsigned int)p_src|0x40000000UL);
	
	unsigned short *buf = src +=(msy *bw +msx);
	unsigned int *p_dst = buf;
	for(j =0; j <msh; j ++) {
		for(i =0; i <msw; i +=2) {
			unsigned int n_p1;
			unsigned int n_p2;
			
			n_p1 = blit_lookup_low[ *( buf ) ]; buf ++;
			n_p2 = blit_lookup_low[ *( buf ) ]; buf ++;
			
			*( p_dst ) = ( n_p1 & 0x0000ffff ) | ( n_p2 & 0xffff0000 ); p_dst ++;
		}
		p_dst =buf =src +=bw;
	}
	
	bh = (bh +255) & ~255;	// テクスチャの境界調整
	
//	if (!mfirsttime) {
//		// wait for next frame
//		sceGuSync(0,0);
//		
//		sceGuSwapBuffers();
//	}
	
	sceGuStart(GU_DIRECT,list);
	
	// clear screen
	sceGuClearColor(0xff00ff);
	sceGuClear(GU_COLOR_BUFFER_BIT);
	
	sceGuTexMode(GU_PSM_5551, 0, 0, 0);
	sceGuTexImage(0, bw, bh, bw, p_src);
	sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGB);
	sceGuTexFilter(GU_LINEAR,GU_LINEAR);
	sceGuTexScale(1.0f, 1.0f);
	sceGuTexOffset(0.0f, 0.0f);
	
	sceGuAmbientColor(0xffffffff);
	
	// render sprite
	sceGuColor(0xffffffff);
	
/*	for (j =0; j <mvidx; j +=2)
	{
		struct Vertex* vertices = (struct Vertex*)sceGuGetMemory(2 * sizeof(struct Vertex));
		vertices[0] =mvertices[j];
		vertices[1] =mvertices[j+1];
		sceGuDrawArray(GU_SPRITES,GU_TEXTURE_16BIT|GU_VERTEX_16BIT|GU_TRANSFORM_2D,2,0,vertices);
	} */

	struct Vertex* vertices = (struct Vertex*)sceGuGetMemory(mvidx * sizeof(struct Vertex));
	for (j =0; j <mvidx; j ++)
		vertices[j] =mvertices[j];
	sceGuDrawArrayN(GU_SPRITES,GU_TEXTURE_16BIT|GU_VERTEX_16BIT|GU_TRANSFORM_2D, 2, mvidx/2, 0, vertices);
	
	// wait for next frame
	sceGuFinish();
//	sceGuSync(0,0);
//	
//	sceGuSwapBuffers();
	
	mfirsttime =0;
	gdrawed =1;
}

// 16bit Source Clut blit
int psp_gu_blit_clut_full_fit(unsigned char *p_src, int sx, int sy, int sw, int sh, int bw, int bh, int dx, int dy )
{
	bh = (bh +255) & ~255;	// テクスチャの境界調整

	// sx=64, sy=128, sw=384, sh=512, bw=544, dx=64, dy=8
	sceGuStart(GU_DIRECT,list);
	
	// clear screen
	sceGuClearColor(0xff00ff);
	sceGuClear(GU_COLOR_BUFFER_BIT);
	
	// setup CLUT texture
//	sceGuClutMode(GU_PSM_8888,0,0xff,0); // 32-bit palette
//	sceGuClutLoad((256/8), blit_lookup_low); // upload 8192*8 entries (65536)
//	sceGuClutMode(GU_PSM_5551, 0, 0xff, 0); // 16-bit palette, shift, mask, offset
//	sceGuClutLoad((256/8), clut16); // upload 8192*8 entries (65536)
	sceGuTexMode(GU_PSM_T16, 0, 0, 0); // 16-bit image
	sceGuTexImage(0, bw, bh, bw, p_src);
	sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGB);
	sceGuTexFilter(GU_LINEAR,GU_LINEAR);
	sceGuTexScale(1.0f, 1.0f);
	sceGuTexOffset(0.0f, 0.0f);
	
	sceGuClutMode(GU_PSM_5551, 0, 0xff, 0); // 16-bit palette, shift, mask, offset
	sceGuClutLoad((256/8), clut16); // upload 8192*8 entries (65536)
	
	sceGuAmbientColor(0xffffffff);
	
	// render sprite
	sceGuColor(0xffffffff);
	struct Vertex* vertices = (struct Vertex*)sceGuGetMemory(2 * sizeof(struct Vertex));
//	vertices[0].u = sx; vertices[0].v = sy;
//	vertices[0].x = dx; vertices[0].y = dy; vertices[0].z = 0;
//	vertices[0].color =0xffff;
//	vertices[1].u = sx +sw; vertices[1].v = sy +sh;
//	vertices[1].x = dx +sw; vertices[1].y = dy +sh; vertices[1].z = 0;
//	vertices[1].color =0xffff;

//	vertices[0].u =  sx; vertices[0].v =  sy;
//	vertices[0].x =   0; vertices[0].y =   0; vertices[0].z = 0;
//	vertices[1].u =  sx+sw; vertices[1].v =  sy+sh;
//	vertices[1].x = 480; vertices[1].y = 272; vertices[1].z = 0;
	
	// xevius normal:video_flipx video_swapxy  rotate:video_flipx video_flipy
	
	if( video_flipx || video_swapxy) {
		vertices[0].u = sx+sw;
		vertices[1].u = sx;
	} else {
		vertices[0].u = sx;
		vertices[1].u = sx+sw;
	}
	
	if( video_flipy || video_swapxy) {
		vertices[0].v = sy+sh;
		vertices[1].v = sy;
	} else {
		vertices[0].v = sy;
		vertices[1].v = sy+sh;
	}
	
	if (video_swapxy) {
		if( video_flipx) {
			vertices[0].x = 0; vertices[1].x = 480;
			vertices[0].y = 272; vertices[1].y = 0;
		} else if ( video_flipy) {
			vertices[0].x = 480; vertices[1].x = 0;
			vertices[0].y = 0; vertices[1].y = 272;
		}
	} else {
		vertices[0].x = 0; vertices[1].x = 480;
		vertices[0].y = 0; vertices[1].y = 272;
	}
	
	vertices[0].z = 0; vertices[1].z = 0;
	
//	sceGuDrawArray(GU_SPRITES,GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_2D,2,0,vertices);
	sceGuDrawArray(GU_SPRITES,GU_TEXTURE_16BIT|GU_VERTEX_16BIT|GU_TRANSFORM_2D,2,0,vertices);
	
	// wait for next frame
	sceGuFinish();
	sceGuSync(0,0);
	
//	sceDisplayWaitVblankStart();
	sceGuSwapBuffers();
}

// 16bit Source blit
int psp_gu_blit_full_fit(unsigned char *p_src, int sx, int sy, int sw, int sh, int bw, int bh, int dx, int dy )
{
int i, j;

	unsigned short *src =(unsigned short *)((unsigned int)p_src|0x40000000UL);
	
	unsigned short *buf = src +=(sy *bw +sx);
	unsigned int *p_dst = buf;
	for(j =0; j <sh; j ++) {
		for(i =0; i <sw; i +=2) {
			unsigned int n_p1;
			unsigned int n_p2;
			
			n_p1 = blit_lookup_low[ *( buf ) ]; buf ++;
			n_p2 = blit_lookup_low[ *( buf ) ]; buf ++;
			
			*( p_dst ) = ( n_p1 & 0x0000ffff ) | ( n_p2 & 0xffff0000 ); p_dst ++;

//			*buf =clut16[*buf];
//			buf ++;
		}
		p_dst =buf =src +=bw;
	}
	
	bh = (bh +255) & ~255;	// テクスチャの境界調整
	
	sceGuStart(GU_DIRECT,list);
	
	// clear screen
	sceGuClearColor(0xff00ff);
	sceGuClear(GU_COLOR_BUFFER_BIT);
	
	sceGuTexMode(GU_PSM_5551, 0, 0, 0);
	sceGuTexImage(0, bw, bh, bw, p_src);
	sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGB);
	sceGuTexFilter(GU_LINEAR,GU_LINEAR);
	sceGuTexScale(1.0f, 1.0f);
	sceGuTexOffset(0.0f, 0.0f);
	
	sceGuAmbientColor(0xffffffff);
	
	// render sprite
	sceGuColor(0xffffffff);

	struct Vertex* vertices = (struct Vertex*)sceGuGetMemory(2 * sizeof(struct Vertex));
	
	if( video_flipx || video_swapxy ) {
		vertices[0].u = sx+sw;
		vertices[1].u = sx;
	} else {
		vertices[0].u = sx;
		vertices[1].u = sx+sw;
	}
	
	if( video_flipy || video_swapxy) {
		vertices[0].v = sy+sh;
		vertices[1].v = sy;
	} else {
		vertices[0].v = sy;
		vertices[1].v = sy+sh;
	}
	
	if (video_swapxy) {
		if( video_flipx) {
			vertices[0].x = 0; vertices[1].x = 480;
			vertices[0].y = 272; vertices[1].y = 0;
		} else if ( video_flipy) {
			vertices[0].x = 480; vertices[1].x = 0;
			vertices[0].y = 0; vertices[1].y = 272;
		}
	} else {
		vertices[0].x = 0; vertices[1].x = 480;
		vertices[0].y = 0; vertices[1].y = 272;
	}
	
	vertices[0].z = 0; vertices[1].z = 0;
	
//	sceGuDrawArray(GU_SPRITES,GU_TEXTURE_16BIT|GU_COLOR_5551|GU_VERTEX_16BIT|GU_TRANSFORM_2D,2,0,vertices);
	sceGuDrawArray(GU_SPRITES,GU_TEXTURE_16BIT|GU_VERTEX_16BIT|GU_TRANSFORM_2D,2,0,vertices);
	
	// wait for next frame
	sceGuFinish();
	sceGuSync(0,0);
	
	sceGuSwapBuffers();
}

void psp_gu_callback(int p);
int psp_gu_init()
{
	mfirsttime =1;
	gdrawed =0;
	
	sceKernelDcacheWritebackAll();
	
	sceGuInit();
	sceGuSetCallback(4, psp_gu_callback);
	sceGuStart(GU_DIRECT,list);
	
//	sceGuDrawBuffer(GU_PSM_8888,(void*)0,BUF_WIDTH);
	sceGuDrawBuffer(GU_PSM_5551, (void*)0, BUF_WIDTH);	// 描画バッファ
	sceGuDispBuffer(SCR_WIDTH, SCR_HEIGHT, (void*)FRAME_SIZE, BUF_WIDTH);	// 表示バッファ
//	sceGuDepthBuffer((void*)(FRAME_SIZE *2), BUF_WIDTH);
	sceGuOffset(2048 - (SCR_WIDTH /2), 2048 - (SCR_HEIGHT /2));
	sceGuViewport(2048, 2048, SCR_WIDTH, SCR_HEIGHT);
//	sceGuDepthRange(0xc350, 0x2710);
	sceGuScissor(0, 0, SCR_WIDTH, SCR_HEIGHT);
	sceGuEnable(GU_SCISSOR_TEST);
	sceGuFrontFace(GU_CW);
	sceGuEnable(GU_TEXTURE_2D);
	sceGuClear(GU_COLOR_BUFFER_BIT /* | GU_DEPTH_BUFFER_BIT */);
	sceGuFinish();
	sceGuSync(0, 0);
	
	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);
}

int psp_gu_term()
{
	sceGuTerm();
	
	pgScreenFrame(1,0);
	cls_();

	gdrawed =0;
}

extern int wait_vsync;
void psp_gu_callback(int p)
{
	if (1 ==gdrawed)
	{
		if (sceDisplayIsVblank() || !wait_vsync) {
			sceGuSwapBuffers();
			
			gdrawed =0;
		} else if (wait_vsync) {
			gdrawed =2;
		}
	}
}

int psp_gu_drawsync()
{
	while(0 !=gdrawed)
	{
		sceDisplayWaitVblankStartCB();
	}
}

void *psp_gu_bmp()
{
	unsigned char *ptr =(unsigned int *)sceGeEdramGetAddr();
	return ((void *)(((unsigned int)(ptr +FRAME_SIZE *2))|0x40000000UL));
}
