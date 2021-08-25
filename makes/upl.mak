# a tiny compile is without Neogeo games
COREDEFS += -DTINY_COMPILE=1
COREDEFS += -DTINY_NAME="driver_acrobatm,driver_arkarea,driver_robokid,driver_robokidj,driver_bioship,driver_blkheart,driver_blkhearj,driver_strahl,driver_strahla,driver_mouser,driver_mouserc,driver_mnight,driver_ninjakd2,driver_ninjak2a,driver_ninjak2b,driver_ninjakun,driver_nova2001,driver_nov2001u,driver_omegaf,driver_omegafs,driver_pkunwarj,driver_pkunwar,driver_rdaction,driver_raiders5,driver_raidrs5t,driver_tharrier,driver_tharierj,driver_urashima,driver_mustang,driver_mustangs,driver_vandyjal,driver_vandyke,driver_xxmissio"

COREDEFS += -DTINY_POINTER="&driver_acrobatm,&driver_arkarea,&driver_robokid,&driver_robokidj,&driver_bioship,&driver_blkheart,&driver_blkhearj,&driver_strahl,&driver_strahla,&driver_mouser,&driver_mouserc,&driver_mnight,&driver_ninjakd2,&driver_ninjak2a,&driver_ninjak2b,&driver_ninjakun,&driver_nova2001,&driver_nov2001u,&driver_omegaf,&driver_omegafs,&driver_pkunwarj,&driver_pkunwar,&driver_rdaction,&driver_raiders5,&driver_raidrs5t,&driver_tharrier,&driver_tharierj,&driver_urashima,&driver_mustang,&driver_mustangs,&driver_vandyjal,&driver_vandyke,&driver_xxmissio"


# uses these CPUs
CPUS+=M68000@
CPUS+=Z80@


# uses these SOUNDs
SOUNDS+=AY8910@
SOUNDS+=OKIM6295@
SOUNDS+=SAMPLES@
SOUNDS+=YM2203@

SOUNDS+=YM2151@
SOUNDS+=YM3812@

OBJS=	$(OBJ)/machine/mc8123.o \


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
