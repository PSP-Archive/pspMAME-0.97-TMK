# a tiny compile is without Neogeo games

COREDEFS += -DTINY_COMPILE=1
COREDEFS += -DTINY_NAME="driver_capitol,driver_cheekyms,driver_cosmica,driver_cosmica2,driver_cavenger,driver_cosmicg,driver_cosmicmo,driver_cosmicm2,driver_devzone,driver_devzone2,driver_dorunruc,driver_dorunrun,driver_dorunru2,driver_galxwars,driver_galxwar2,driver_idsoccer,driver_jjack,driver_kickridr,driver_ladybug,driver_magspot,driver_magspot2,driver_mimonkey,driver_douni,driver_mrdo,driver_mrdofix,driver_mrdoy,driver_mrdot,driver_docastlo,driver_docastle,driver_docastl2,driver_dowild,driver_nomnlnd,driver_nomnlndg,driver_snapjack,driver_panicger,driver_panich,driver_panic2,driver_panic3,driver_panic,driver_sraider,driver_spiero,driver_zerohour"

COREDEFS += -DTINY_POINTER="&driver_capitol,&driver_cheekyms,&driver_cosmica,&driver_cosmica2,&driver_cavenger,&driver_cosmicg,&driver_cosmicmo,&driver_cosmicm2,&driver_devzone,&driver_devzone2,&driver_dorunruc,&driver_dorunrun,&driver_dorunru2,&driver_galxwars,&driver_galxwar2,&driver_idsoccer,&driver_jjack,&driver_kickridr,&driver_ladybug,&driver_magspot,&driver_magspot2,&driver_mimonkey,&driver_douni,&driver_mrdo,&driver_mrdofix,&driver_mrdoy,&driver_mrdot,&driver_docastlo,&driver_docastle,&driver_docastl2,&driver_dowild,&driver_nomnlnd,&driver_nomnlndg,&driver_snapjack,&driver_panicger,&driver_panich,&driver_panic2,&driver_panic3,&driver_panic,&driver_sraider,&driver_spiero,&driver_zerohour"

# uses these CPUs
CPUS+=8080@
CPUS+=8085A@
CPUS+=TMS9980@
CPUS+=Z80@
CPUS+=N2A03@


# uses these SOUNDs
SOUNDS+=AY8910@
SOUNDS+=CUSTOM@
SOUNDS+=DAC@
SOUNDS+=DISCRETE@
SOUNDS+=MSM5205@
SOUNDS+=SAMPLES@
SOUNDS+=SN76477@
SOUNDS+=SN76496@
SOUNDS+=TMS36XX@

SOUNDS+=TMS5110@
SOUNDS+=NES@
SOUNDS+=NAMCO@


OBJS=	$(OBJ)/machine/scramble.o $(OBJ)/sndhrdw/scramble.o $(OBJ)/drivers/scramble.o \
		$(OBJ)/drivers/amidar.o \
		$(OBJ)/drivers/frogger.o \
		$(OBJ)/drivers/scobra.o \
		$(OBJ)/vidhrdw/galaxian.o $(OBJ)/sndhrdw/galaxian.o $(OBJ)/drivers/galaxian.o \
			$(OBJ)/vidhrdw/bagman.o $(OBJ)/machine/bagman.o $(OBJ)/drivers/bagman.o \
			$(OBJ)/vidhrdw/pacman.o $(OBJ)/drivers/pacman.o \
				$(OBJ)/vidhrdw/epos.o $(OBJ)/drivers/epos.o \
				$(OBJ)/machine/mspacman.o $(OBJ)/machine/pacplus.o \
				$(OBJ)/machine/jumpshot.o $(OBJ)/machine/theglobp.o \
				$(OBJ)/machine/acitya.o \
			$(OBJ)/vidhrdw/phoenix.o $(OBJ)/sndhrdw/phoenix.o $(OBJ)/drivers/phoenix.o \
				$(OBJ)/sndhrdw/pleiads.o \
			$(OBJ)/vidhrdw/cclimber.o $(OBJ)/sndhrdw/cclimber.o $(OBJ)/drivers/cclimber.o \
			$(OBJ)/vidhrdw/ladybug.o $(OBJ)/drivers/ladybug.o \


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
