# a tiny compile is without Neogeo games
COREDEFS += -DTINY_COMPILE=1
COREDEFS += -DTINY_NAME="driver_assault,driver_assaultj,driver_assaultp,driver_bakutotu,driver_berabohm,driver_beraboho,driver_blastoff,driver_blazer,driver_boxyboy,driver_burnforc,driver_cosmogng,driver_cosmognj,driver_dangseed,driver_dirtfoxj,driver_dsaber,driver_dsaberj,driver_dspirit,driver_dspirito,driver_faceoff,driver_finalap2,driver_finalap3,driver_finalapc,driver_finalapd,driver_finallap,driver_finalp2j,driver_finalp3a,driver_finehour,driver_finlapjb,driver_finlapjc,driver_fourtrax,driver_galag88j,driver_galaga88,driver_gollygho,driver_kyukaidk,driver_kyukaido,driver_luckywld,driver_marvland,driver_marvlanj,driver_metlhawk,driver_mirninja,driver_mmaze,driver_ordyne,driver_pacmania,driver_pacmanij,driver_phelios,driver_pistoldm,driver_puzlclub,driver_quester,driver_rompers,driver_romperso,driver_rthun2,driver_rthun2j,driver_sgunner,driver_sgunner2,driver_sgunnr2j,driver_shadowld,driver_soukobdx,driver_splatter,driver_suzuk8h2,driver_suzuka8h,driver_sws92,driver_sws92g,driver_sws93,driver_tankfrce,driver_tankfrcj,driver_valkyrie,driver_wldcourt,driver_ws,driver_ws89,driver_ws90,driver_yokaidko,driver_youkaidk"

COREDEFS += -DTINY_POINTER="&driver_assault,&driver_assaultj,&driver_assaultp,&driver_bakutotu,&driver_berabohm,&driver_beraboho,&driver_blastoff,&driver_blazer,&driver_boxyboy,&driver_burnforc,&driver_cosmogng,&driver_cosmognj,&driver_dangseed,&driver_dirtfoxj,&driver_dsaber,&driver_dsaberj,&driver_dspirit,&driver_dspirito,&driver_faceoff,&driver_finalap2,&driver_finalap3,&driver_finalapc,&driver_finalapd,&driver_finallap,&driver_finalp2j,&driver_finalp3a,&driver_finehour,&driver_finlapjb,&driver_finlapjc,&driver_fourtrax,&driver_galag88j,&driver_galaga88,&driver_gollygho,&driver_kyukaidk,&driver_kyukaido,&driver_luckywld,&driver_marvland,&driver_marvlanj,&driver_metlhawk,&driver_mirninja,&driver_mmaze,&driver_ordyne,&driver_pacmania,&driver_pacmanij,&driver_phelios,&driver_pistoldm,&driver_puzlclub,&driver_quester,&driver_rompers,&driver_romperso,&driver_rthun2,&driver_rthun2j,&driver_sgunner,&driver_sgunner2,&driver_sgunnr2j,&driver_shadowld,&driver_soukobdx,&driver_splatter,&driver_suzuk8h2,&driver_suzuka8h,&driver_sws92,&driver_sws92g,&driver_sws93,&driver_tankfrce,&driver_tankfrcj,&driver_valkyrie,&driver_wldcourt,&driver_ws,&driver_ws89,&driver_ws90,&driver_yokaidko,&driver_youkaidk"

# cpuintrf.c cpuintrf.h cheat.c audit.c memory.c info.c sndintrf.c sndintrf.h usrintrf.c psp/fronthlp.c

# uses these CPUs
CPUS+=HD63705@
CPUS+=M68000@
CPUS+=M6809@
CPUS+=HD63701@

CPUS+=M6803@


#CPUS+=8080@
#CPUS+=M6502@
#CPUS+=M68020@
#CPUS+=M68EC020@
#CPUS+=PSXCPU@
#CPUS+=Z80@
#CPUS+=Z8000@
#CPUS+=I8035@
#CPUS+=S2650@
#CPUS+=N2A03@
#CPUS+=8085A@



# uses these SOUNDs
SOUNDS+=C140@
SOUNDS+=DAC@
SOUNDS+=NAMCO@
SOUNDS+=YM2151@


#SOUNDS+=AY8910@
#SOUNDS+=CUSTOM@
#SOUNDS+=NAMCONA@
#SOUNDS+=SAMPLES@
#SOUNDS+=NES@
#SOUNDS+=TMS5110@
#SOUNDS+=SN76496@
#SOUNDS+=TMS36XX@


OBJS =	$(OBJ)/machine/namcos1.o $(OBJ)/vidhrdw/namcos1.o $(OBJ)/drivers/namcos1.o \
	$(OBJ)/machine/namcos2.o $(OBJ)/vidhrdw/namcos2.o $(OBJ)/drivers/namcos2.o \
	$(OBJ)/drivers/namcoic.o \
	\
	$(OBJ)/machine/random.o \

# MAME specific core objs
COREOBJS += $(OBJ)/tiny.o $(OBJ)/cheat.o
