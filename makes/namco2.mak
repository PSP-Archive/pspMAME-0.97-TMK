# a tiny compile is without Neogeo games
COREDEFS += -DTINY_COMPILE=1
COREDEFS += -DTINY_NAME="driver_bkrtmaq,driver_cgangpzj,driver_cgangpzl,driver_emeralda,driver_emerldaa,driver_exvania,driver_fa,driver_fghtatck,driver_finalapr,driver_gslugrsj,driver_gslgr94u,driver_gunbulet,driver_vshoot,driver_knckhedj,driver_knckhead,driver_myangel,driver_myangel2,driver_liblrabl,driver_machbrkr,driver_ncv1,driver_ncv1j,driver_ncv1j2,driver_ncv2,driver_ncv2j,driver_nebulryj,driver_nebulray,driver_quiztou,driver_numanatj,driver_numanath,driver_outfxies,driver_outfxesj,driver_ptblank,driver_speedrcr,driver_swcourt,driver_sws95,driver_sws96,driver_sws97,driver_tceptor,driver_tceptor2,driver_tinklpit,driver_toypop,driver_xday2"

COREDEFS += -DTINY_POINTER="&driver_bkrtmaq,&driver_cgangpzj,&driver_cgangpzl,&driver_emeralda,&driver_emerldaa,&driver_exvania,&driver_fa,&driver_fghtatck,&driver_finalapr,&driver_gslugrsj,&driver_gslgr94u,&driver_gunbulet,&driver_vshoot,&driver_knckhedj,&driver_knckhead,&driver_myangel,&driver_myangel2,&driver_liblrabl,&driver_machbrkr,&driver_ncv1,&driver_ncv1j,&driver_ncv1j2,&driver_ncv2,&driver_ncv2j,&driver_nebulryj,&driver_nebulray,&driver_quiztou,&driver_numanatj,&driver_numanath,&driver_outfxies,&driver_outfxesj,&driver_ptblank,&driver_speedrcr,&driver_swcourt,&driver_sws95,&driver_sws96,&driver_sws97,&driver_tceptor,&driver_tceptor2,&driver_tinklpit,&driver_toypop,&driver_xday2"

# uses these CPUs
CPUS+=M68000@
CPUS+=M68EC020@
CPUS+=H83002@
CPUS+=HD63701@
CPUS+=I960@
CPUS+=M65C02@
CPUS+=M6809@

CPUS+=M6803@

#CPUS+=8080@
#CPUS+=M6502@
#CPUS+=N2A03@
#CPUS+=Z80@
#CPUS+=Z8000@
#CPUS+=S2650@
#CPUS+=8085A@
#CPUS+=I8035@


# uses these SOUNDs
SOUNDS+=C352@
SOUNDS+=DAC@
SOUNDS+=NAMCO_15XX@
SOUNDS+=NAMCO_CUS30@
SOUNDS+=NAMCONA@
SOUNDS+=X1_010@
SOUNDS+=YM2151@

SOUNDS+=NAMCO_52XX@
SOUNDS+=NAMCO_54XX@
SOUNDS+=SAMPLES@


#SOUNDS+=CUSTOM@
#SOUNDS+=NAMCO@
#SOUNDS+=NAMCO_52XX@
#SOUNDS+=NAMCO_54XX@
#SOUNDS+=NAMCO_63701X@
#SOUNDS+=NES@
#SOUNDS+=AY8910@
#SOUNDS+=DISCRETE@
#SOUNDS+=SN76496@
#SOUNDS+=TMS36XX@
#SOUNDS+=TMS5110@




DRVLIBS = \
	obj/drivers/pacman.a obj/drivers/epos.a obj/drivers/nichibut.a \
	obj/drivers/phoenix.a obj/drivers/namco.a obj/drivers/univers.a obj/drivers/nintendo.a \
	obj/drivers/midw8080.a obj/drivers/meadows.a obj/drivers/cvs.a obj/drivers/midway.a \
	obj/drivers/irem.a obj/drivers/gottlieb.a obj/drivers/taito.a obj/drivers/toaplan.a obj/drivers/cave.a \
	obj/drivers/kyugo.a obj/drivers/williams.a obj/drivers/gremlin.a obj/drivers/vicdual.a \
	obj/drivers/capcom.a obj/drivers/itech.a obj/drivers/leland.a obj/drivers/sega.a \
	obj/drivers/dataeast.a obj/drivers/tehkan.a obj/drivers/konami.a \
	obj/drivers/exidy.a obj/drivers/atari.a obj/drivers/snk.a obj/drivers/alpha.a obj/drivers/technos.a \
	obj/drivers/stern.a obj/drivers/gameplan.a obj/drivers/zaccaria.a \
	obj/drivers/upl.a obj/drivers/nmk.a obj/drivers/cinemar.a obj/drivers/cinemav.a \
	obj/drivers/thepit.a obj/drivers/valadon.a obj/drivers/seibu.a obj/drivers/tad.a obj/drivers/jaleco.a \
	obj/drivers/vsystem.a obj/drivers/psikyo.a obj/drivers/orca.a obj/drivers/gaelco.a \
	obj/drivers/kaneko.a obj/drivers/seta.a obj/drivers/atlus.a \
	obj/drivers/sun.a obj/drivers/suna.a obj/drivers/dooyong.a obj/drivers/tong.a \
	obj/drivers/comad.a obj/drivers/playmark.a obj/drivers/pacific.a obj/drivers/tecfri.a \
	obj/drivers/metro.a obj/drivers/venture.a obj/drivers/yunsung.a obj/drivers/zilec.a \
	obj/drivers/fuuki.a obj/drivers/unico.a obj/drivers/dynax.a \
	obj/drivers/sigma.a obj/drivers/igs.a obj/drivers/ramtek.a obj/drivers/omori.a obj/drivers/tch.a \
	obj/drivers/usgames.a obj/drivers/sanritsu.a obj/drivers/rare.a \
	obj/drivers/alba.a obj/drivers/homedata.a obj/drivers/artmagic.a \
	obj/drivers/taiyo.a obj/drivers/edevices.a obj/drivers/other.a obj/drivers/excelent.a obj/drivers/nix.a \
	obj/drivers/arcadia.a obj/drivers/othertrv.a obj/drivers/other68k.a obj/drivers/otherz80.a \
	obj/drivers/neogeo.a $(OBJ)/shared.a \

$(OBJ)/shared.a: \
	$(OBJ)/machine/segacrpt.o \
	$(OBJ)/machine/tmp68301.o \
	$(OBJ)/machine/6532riot.o \
	$(OBJ)/machine/z80fmly.o \
	$(OBJ)/machine/6821pia.o \
	$(OBJ)/machine/8255ppi.o \
	$(OBJ)/machine/6522via.o \
	$(OBJ)/machine/7474.o \
	$(OBJ)/machine/idectrl.o \
	$(OBJ)/machine/ticket.o \
	$(OBJ)/machine/random.o \
	$(OBJ)/machine/adc083x.o \
	$(OBJ)/vidhrdw/crtc6845.o \
	$(OBJ)/vidhrdw/avgdvg.o \
	$(OBJ)/vidhrdw/poly.o \
	$(OBJ)/vidhrdw/tlc34076.o \
	$(OBJ)/vidhrdw/res_net.o \

# MAME specific core objs
COREOBJS += $(OBJ)/tiny.o $(OBJ)/cheat.o
