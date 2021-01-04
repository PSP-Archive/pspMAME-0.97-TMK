#ifndef SETING_H
#define SETING_H

typedef struct
{
	char vercnf[16];
	int screensize;
	int rotate;
	int frameskip;
	int vsync;
	int sound;
	int sound_rate;
	unsigned long color[4];
	int bgbright;
	int analog2dpad;
	int cpu_clock;
	int rom_verify;
} SETTING;

enum{
	SCR_X1,
	SCR_STRETCH,
	SCR_STRETCH_ACPECT,
	SCR_GE_X1,
	SCR_GE_ZOOM,
	SCR_GE_FIT,
	SCR_GE_FULL_FIT,
	SCR_END,
};

#define CONFIG_VER	"PSPMAMEr0.5"
#define APP_TITLE	"PSPMAME r0.5 (M.A.M.E. v0.97 for PSP)"

#endif
