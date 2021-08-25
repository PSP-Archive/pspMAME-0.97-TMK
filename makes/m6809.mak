# a tiny compile is without Neogeo games
COREDEFS += -DTINY_COMPILE=1
COREDEFS += -DTINY_NAME="driver_aeroboto,driver_arlingtn,driver_battlan2,driver_battlan3,driver_battlane,driver_beezer,driver_beezer1,driver_brkthru,driver_brkthruj,driver_catch22,driver_cheyenne,driver_chiller,driver_citycon,driver_citycona,driver_claypign,driver_cntsteer,driver_combat,driver_compglfo,driver_compgolf,driver_contra,driver_contraj,driver_cracksht,driver_crossbow,driver_cruisin,driver_darwin,driver_ddribble,driver_digdug2,driver_digdug2o,driver_esb,driver_formatz,driver_galaga3,driver_galaga3a,driver_galaga3m,driver_gaplus,driver_gaplusa,driver_gapluso,driver_gpgolf,driver_gridlee,driver_grobda,driver_grobda2,driver_grobda3,driver_gryzor,driver_gtg,driver_gtg2,driver_gtg2j,driver_gtg2t,driver_gtgt,driver_hitnmis2,driver_hitnmiss,driver_hstenn10,driver_hstennis,driver_irobot,driver_jackal,driver_jackalj,driver_jailbrek,driver_kicker,driver_manhatan,driver_mappy,driver_mappyj,driver_metlclsh,driver_motos,driver_neckneck,driver_pacnchmp,driver_pacnpal,driver_pacnpal2,driver_peggle,driver_pegglet,driver_phozon,driver_pokrdice,driver_rimrck12,driver_rimrck16,driver_rimrck20,driver_rimrockn,driver_shaolins,driver_showdown,driver_slither,driver_slithera,driver_solarwar,driver_sonson,driver_sonsonj,driver_starwar1,driver_starwars,driver_stoffy,driver_stratab,driver_stratab1,driver_superpac,driver_superpcm,driver_todruaga,driver_todruago,driver_toffy,driver_topgunr,driver_topsecex,driver_truco,driver_turbosub,driver_usg185,driver_usg252,driver_usg32,driver_usg82,driver_usg83,driver_usg83x,driver_wfortuna,driver_wfortune,driver_whodunit,driver_xsleena,driver_yiear,driver_yiear2"
COREDEFS += -DTINY_POINTER="&driver_aeroboto,&driver_arlingtn,&driver_battlan2,&driver_battlan3,&driver_battlane,&driver_beezer,&driver_beezer1,&driver_brkthru,&driver_brkthruj,&driver_catch22,&driver_cheyenne,&driver_chiller,&driver_citycon,&driver_citycona,&driver_claypign,&driver_cntsteer,&driver_combat,&driver_compglfo,&driver_compgolf,&driver_contra,&driver_contraj,&driver_cracksht,&driver_crossbow,&driver_cruisin,&driver_darwin,&driver_ddribble,&driver_digdug2,&driver_digdug2o,&driver_esb,&driver_formatz,&driver_galaga3,&driver_galaga3a,&driver_galaga3m,&driver_gaplus,&driver_gaplusa,&driver_gapluso,&driver_gpgolf,&driver_gridlee,&driver_grobda,&driver_grobda2,&driver_grobda3,&driver_gryzor,&driver_gtg,&driver_gtg2,&driver_gtg2j,&driver_gtg2t,&driver_gtgt,&driver_hitnmis2,&driver_hitnmiss,&driver_hstenn10,&driver_hstennis,&driver_irobot,&driver_jackal,&driver_jackalj,&driver_jailbrek,&driver_kicker,&driver_manhatan,&driver_mappy,&driver_mappyj,&driver_metlclsh,&driver_motos,&driver_neckneck,&driver_pacnchmp,&driver_pacnpal,&driver_pacnpal2,&driver_peggle,&driver_pegglet,&driver_phozon,&driver_pokrdice,&driver_rimrck12,&driver_rimrck16,&driver_rimrck20,&driver_rimrockn,&driver_shaolins,&driver_showdown,&driver_slither,&driver_slithera,&driver_solarwar,&driver_sonson,&driver_sonsonj,&driver_starwar1,&driver_starwars,&driver_stoffy,&driver_stratab,&driver_stratab1,&driver_superpac,&driver_superpcm,&driver_todruaga,&driver_todruago,&driver_toffy,&driver_topgunr,&driver_topsecex,&driver_truco,&driver_turbosub,&driver_usg185,&driver_usg252,&driver_usg32,&driver_usg82,&driver_usg83,&driver_usg83x,&driver_wfortuna,&driver_wfortune,&driver_whodunit,&driver_xsleena,&driver_yiear,&driver_yiear2"

# uses these CPUs
CPUS+=M6809@

# uses these SOUNDs
SOUNDS+=AY8910@
SOUNDS+=YM2413@
SOUNDS+=MSM5205@
SOUNDS+=CUSTOM@
SOUNDS+=SAMPLES@
SOUNDS+=DAC@
SOUNDS+=DISCRETE@
SOUNDS+=YM2151@
SOUNDS+=OKIM6295@
SOUNDS+=YM2203@
SOUNDS+=YMZ280B@
SOUNDS+=TMS5220@
SOUNDS+=VLM5030@
SOUNDS+=ADPCM@
SOUNDS+=YM3812@
SOUNDS+=YM3526@
SOUNDS+=SN76496@
SOUNDS+=POKEY@
SOUNDS+=NAMCO_15XX@
SOUNDS+=NAMCO_52XX@
SOUNDS+=NAMCO_54XX@

OBJS=	$(OBJ)/sndhrdw/seibu.o


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
DESCJ =$(OBJ)/m6809_descj.o
COREOBJS += $(OBJ)/tiny.o $(OBJ)/cheat.o $(DESCJ)
