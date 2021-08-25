# a tiny compile is without Neogeo games
COREDEFS += -DTINY_COMPILE=1
COREDEFS += -DTINY_NAME="driver_yard,driver_airduel,driver_andromed,driver_atomboy,driver_atompunk,driver_bchopper,driver_bmaster,driver_bombrman,driver_bbmanwj,driver_bbmanw,driver_cosmccop,driver_dkgensan,driver_dkgenm72,driver_demoneye,driver_dbreed,driver_dsoccr94,driver_dsccr94j,driver_dynablst,driver_firebarr,driver_gallop,driver_geostorm,driver_gteikoku,driver_greenber,driver_gunhohki,driver_gunforcj,driver_gunforcu,driver_gunforce,driver_gunforc2,driver_gussun,driver_hharryu,driver_hharry,driver_hasamu,driver_headoni,driver_hookj,driver_hooku,driver_hook,driver_horizon,driver_imgfight,driver_inthuntu,driver_inthunt,driver_ipminvad,driver_yanchamr,driver_kaiteids,driver_kengo,driver_kidniki,driver_pc_kngfu,driver_kungfum,driver_kungfud,driver_loht,driver_lethalth,driver_ldrun,driver_ldruna,driver_ldrun2,driver_ldrun3jp,driver_ldrun3,driver_ldrun4,driver_lotlot,driver_majtitle,driver_majtitl2,driver_kikcubic,driver_mpatrol,driver_mpatrolw,driver_motorace,driver_mrheli,driver_mysticri,driver_newapunk,driver_nbbatman,driver_nspirit,driver_olibochu,driver_psoldier,driver_poundfou,driver_poundfor,driver_quizf1,driver_redalert,driver_riskchal,driver_rtypepj,driver_rtype,driver_rtypeu,driver_rtype2,driver_rtype2j,driver_rtypelej,driver_rtypeleo,driver_nspiritj,driver_nss_skin,driver_skychut,driver_spacbeam,driver_spartanx,driver_spelunkr,driver_spelnkrj,driver_spelunk2,driver_ssoldier,driver_battroad,driver_skingame,driver_skingam2,driver_thndblst,driver_travrusa,driver_troangel,driver_uccopsj,driver_uccops,driver_uniwars,driver_vigilntj,driver_vigilntu,driver_vigilant,driver_vsyard2,driver_vsyard,driver_wilytowr,driver_xmultipl,driver_leaguemn,driver_youjyudn"

COREDEFS += -DTINY_POINTER="&driver_yard,&driver_airduel,&driver_andromed,&driver_atomboy,&driver_atompunk,&driver_bchopper,&driver_bmaster,&driver_bombrman,&driver_bbmanwj,&driver_bbmanw,&driver_cosmccop,&driver_dkgensan,&driver_dkgenm72,&driver_demoneye,&driver_dbreed,&driver_dsoccr94,&driver_dsccr94j,&driver_dynablst,&driver_firebarr,&driver_gallop,&driver_geostorm,&driver_gteikoku,&driver_greenber,&driver_gunhohki,&driver_gunforcj,&driver_gunforcu,&driver_gunforce,&driver_gunforc2,&driver_gussun,&driver_hharryu,&driver_hharry,&driver_hasamu,&driver_headoni,&driver_hookj,&driver_hooku,&driver_hook,&driver_horizon,&driver_imgfight,&driver_inthuntu,&driver_inthunt,&driver_ipminvad,&driver_yanchamr,&driver_kaiteids,&driver_kengo,&driver_kidniki,&driver_pc_kngfu,&driver_kungfum,&driver_kungfud,&driver_loht,&driver_lethalth,&driver_ldrun,&driver_ldruna,&driver_ldrun2,&driver_ldrun3jp,&driver_ldrun3,&driver_ldrun4,&driver_lotlot,&driver_majtitle,&driver_majtitl2,&driver_kikcubic,&driver_mpatrol,&driver_mpatrolw,&driver_motorace,&driver_mrheli,&driver_mysticri,&driver_newapunk,&driver_nbbatman,&driver_nspirit,&driver_olibochu,&driver_psoldier,&driver_poundfou,&driver_poundfor,&driver_quizf1,&driver_redalert,&driver_riskchal,&driver_rtypepj,&driver_rtype,&driver_rtypeu,&driver_rtype2,&driver_rtype2j,&driver_rtypelej,&driver_rtypeleo,&driver_nspiritj,&driver_nss_skin,&driver_skychut,&driver_spacbeam,&driver_spartanx,&driver_spelunkr,&driver_spelnkrj,&driver_spelunk2,&driver_ssoldier,&driver_battroad,&driver_skingame,&driver_skingam2,&driver_thndblst,&driver_travrusa,&driver_troangel,&driver_uccopsj,&driver_uccops,&driver_uniwars,&driver_vigilntj,&driver_vigilntu,&driver_vigilant,&driver_vsyard2,&driver_vsyard,&driver_wilytowr,&driver_xmultipl,&driver_leaguemn,&driver_youjyudn"


# uses these CPUs
CPUS+=8085A@

CPUS+=I8039@
CPUS+=M6502@
CPUS+=M6802@
CPUS+=M6803@
CPUS+=N2A03@
CPUS+=SPC700@
CPUS+=V30@
CPUS+=V33@
CPUS+=Z80@

CPUS+=G65816@

# uses these SOUNDs
SOUNDS+=AY8910@
SOUNDS+=CUSTOM@
SOUNDS+=DAC@
SOUNDS+=IREMGA20@
SOUNDS+=MSM5205@
SOUNDS+=NES@
SOUNDS+=SAMPLES@
SOUNDS+=YM2151@

SOUNDS+=SN76496@
SOUNDS+=TMS5110@
SOUNDS+=YM2203@

SOUNDS+=DISCRETE@
SOUNDS+=TMS36XX@
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
