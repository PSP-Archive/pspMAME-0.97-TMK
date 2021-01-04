# a tiny compile is without Neogeo games
COREDEFS += -DTINY_COMPILE=1
COREDEFS += -DTINY_NAME="driver_forgottn,driver_lostwrld,driver_ghouls,driver_ghoulsu,driver_daimakai,driver_strider,driver_stridrua,driver_striderj,driver_stridrja,driver_willow,driver_willowj,driver_willowje,driver_unsquad,driver_area88,driver_ffight,driver_ffightu,driver_ffightj,driver_ffightj1,driver_1941,driver_1941j,driver_mercs,driver_mercsu,driver_mercsua,driver_mercsj,driver_mtwins,driver_chikij,driver_msword,driver_mswordr1,driver_mswordu,driver_mswordj,driver_cawing,driver_cawingu,driver_cawingj,driver_nemo,driver_nemoj,driver_sf2,driver_sf2eb,driver_sf2ua,driver_sf2ub,driver_sf2ud,driver_sf2ue,driver_sf2uf,driver_sf2ui,driver_sf2uk,driver_sf2j,driver_sf2ja,driver_sf2jc,driver_3wonders,driver_3wonderu,driver_wonder3,driver_kod,driver_kodu,driver_kodj,driver_kodb,driver_captcomm,driver_captcomu,driver_captcomj,driver_knights,driver_knightsu,driver_knightsj,driver_sf2ce,driver_sf2ceua,driver_sf2ceub,driver_sf2ceuc,driver_sf2cej,driver_sf2rb,driver_sf2rb2,driver_sf2red,driver_sf2v004,driver_sf2accp2,driver_varth,driver_varthu,driver_varthj,driver_cworld2j,driver_wof,driver_wofa,driver_wofu,driver_wofj,driver_sf2t,driver_sf2tj,driver_dino,driver_dinou,driver_dinoj,driver_punisher,driver_punishru,driver_punishrj,driver_slammast,driver_slammasu,driver_mbomberj,driver_mbombrd,driver_mbombrdj,driver_pnickj,driver_qad,driver_qadj,driver_qtono2,driver_pang3,driver_pang3j,driver_megaman,driver_rockmanj"

COREDEFS += -DTINY_POINTER="&driver_forgottn,&driver_lostwrld,&driver_ghouls,&driver_ghoulsu,&driver_daimakai,&driver_strider,&driver_stridrua,&driver_striderj,&driver_stridrja,&driver_willow,&driver_willowj,&driver_willowje,&driver_unsquad,&driver_area88,&driver_ffight,&driver_ffightu,&driver_ffightj,&driver_ffightj1,&driver_1941,&driver_1941j,&driver_mercs,&driver_mercsu,&driver_mercsua,&driver_mercsj,&driver_mtwins,&driver_chikij,&driver_msword,&driver_mswordr1,&driver_mswordu,&driver_mswordj,&driver_cawing,&driver_cawingu,&driver_cawingj,&driver_nemo,&driver_nemoj,&driver_sf2,&driver_sf2eb,&driver_sf2ua,&driver_sf2ub,&driver_sf2ud,&driver_sf2ue,&driver_sf2uf,&driver_sf2ui,&driver_sf2uk,&driver_sf2j,&driver_sf2ja,&driver_sf2jc,&driver_3wonders,&driver_3wonderu,&driver_wonder3,&driver_kod,&driver_kodu,&driver_kodj,&driver_kodb,&driver_captcomm,&driver_captcomu,&driver_captcomj,&driver_knights,&driver_knightsu,&driver_knightsj,&driver_sf2ce,&driver_sf2ceua,&driver_sf2ceub,&driver_sf2ceuc,&driver_sf2cej,&driver_sf2rb,&driver_sf2rb2,&driver_sf2red,&driver_sf2v004,&driver_sf2accp2,&driver_varth,&driver_varthu,&driver_varthj,&driver_cworld2j,&driver_wof,&driver_wofa,&driver_wofu,&driver_wofj,&driver_sf2t,&driver_sf2tj,&driver_dino,&driver_dinou,&driver_dinoj,&driver_punisher,&driver_punishru,&driver_punishrj,&driver_slammast,&driver_slammasu,&driver_mbomberj,&driver_mbombrd,&driver_mbombrdj,&driver_pnickj,&driver_qad,&driver_qadj,&driver_qtono2,&driver_pang3,&driver_pang3j,&driver_megaman,&driver_rockmanj"


# cpuintrf.c cpuintrf.h cheat.c audit.c memory.c info.c sndintrf.c sndintrf.h usrintrf.c psp/fronthlp.c

# uses these CPUs
CPUS+=M68000@
CPUS+=Z80@

#CPUS+=M6809@
#CPUS+=PSXCPU@


# uses these SOUNDs
SOUNDS+=YM2151@
SOUNDS+=OKIM6295@
SOUNDS+=QSOUND@

#SOUNDS+=AY8910@
#SOUNDS+=MSM5205@
#SOUNDS+=SN76496@
#SOUNDS+=YM2203@
#SOUNDS+=YM2413@
#SOUNDS+=YM2610@


OBJS =	$(OBJ)/vidhrdw/cps1.o $(OBJ)/drivers/cps1.o \
	$(OBJ)/machine/kabuki.o \

#	$(OBJ)/drivers/cps2.o \
#	$(OBJ)/vidhrdw/vulgus.o $(OBJ)/drivers/vulgus.o \
#	$(OBJ)/vidhrdw/sonson.o $(OBJ)/drivers/sonson.o \
#	$(OBJ)/vidhrdw/higemaru.o $(OBJ)/drivers/higemaru.o \
#	$(OBJ)/vidhrdw/1942.o $(OBJ)/drivers/1942.o \
#	$(OBJ)/vidhrdw/exedexes.o $(OBJ)/drivers/exedexes.o \
#	$(OBJ)/vidhrdw/commando.o $(OBJ)/drivers/commando.o \
#	$(OBJ)/vidhrdw/gng.o $(OBJ)/drivers/gng.o \
#	$(OBJ)/vidhrdw/gunsmoke.o $(OBJ)/drivers/gunsmoke.o \
#	$(OBJ)/vidhrdw/srumbler.o $(OBJ)/drivers/srumbler.o \
#	$(OBJ)/vidhrdw/lwings.o $(OBJ)/drivers/lwings.o \
#	$(OBJ)/vidhrdw/sidearms.o $(OBJ)/drivers/sidearms.o \
#	$(OBJ)/vidhrdw/bionicc.o $(OBJ)/drivers/bionicc.o \
#	$(OBJ)/vidhrdw/1943.o $(OBJ)/drivers/1943.o \
#	$(OBJ)/vidhrdw/blktiger.o $(OBJ)/drivers/blktiger.o \
#	$(OBJ)/vidhrdw/tigeroad.o $(OBJ)/drivers/tigeroad.o \
#	$(OBJ)/vidhrdw/lastduel.o $(OBJ)/drivers/lastduel.o \
#	$(OBJ)/vidhrdw/sf1.o $(OBJ)/drivers/sf1.o \
#	$(OBJ)/vidhrdw/mitchell.o $(OBJ)/drivers/mitchell.o \
#	$(OBJ)/vidhrdw/cbasebal.o $(OBJ)/drivers/cbasebal.o \
#	$(OBJ)/drivers/zn.o \
#	$(OBJ)/sndhrdw/taitosnd.o \
#	$(OBJ)/machine/psx.o $(OBJ)/vidhrdw/psx.o

# MAME specific core objs
COREOBJS += $(OBJ)/tiny.o $(OBJ)/cheat.o
