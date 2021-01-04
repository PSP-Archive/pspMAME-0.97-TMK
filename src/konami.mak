# a tiny compile is without Neogeo games
COREDEFS += -DTINY_COMPILE=1
COREDEFS += -DTINY_NAME="driver_600,driver_amidar,driver_amidaro,driver_amidars,driver_amidaru,driver_battlnts,driver_battlntj,driver_bladstle,driver_bladestl,driver_bootcamp,driver_bottom9n,driver_bottom9,driver_pc_cvnia,driver_circusc,driver_circuscc,driver_circusce,driver_circusc2,driver_combascj,driver_combasc,driver_combasct,driver_contraj,driver_pc_cntra,driver_contra,driver_nss_con3,driver_dairesya,driver_devstor3,driver_devstor2,driver_devstors,driver_ddribble,driver_pc_dbldr,driver_fastlane,driver_finalizr,driver_flkatck,driver_frogger,driver_frogseg1,driver_frogseg2,driver_garuka,driver_pc_grdus,driver_pc_grdue,driver_gberet,driver_gryzor,driver_gutangtn,driver_gyrussce,driver_gyruss,driver_hexion,driver_hyprolym,driver_hpolym84,driver_hyperspt,driver_ironhors,driver_jackal,driver_jailbrek,driver_jungler,driver_junglers,driver_junofrst,driver_junofstg,driver_kicker,driver_rockragj,driver_labyrunr,driver_labyrunk,driver_lethalej,driver_lethalen,driver_locomotn,driver_mstadium,driver_manhatan,driver_megaznik,driver_megazone,driver_megazona,driver_megazonb,driver_megazonc,driver_mikie,driver_mikiehs,driver_mogura,driver_mrgoemon,driver_mx5000,driver_pandoras,driver_pingpong,driver_pooyan,driver_pooyans,driver_rackemup,driver_ringohja,driver_roadf,driver_roadf2,driver_rockraga,driver_rockrage,driver_rocnrope,driver_rocnropk,driver_pc_rnatk,driver_rushatck,driver_spyu,driver_spy,driver_scotrsht,driver_scramble,driver_scrambls,driver_shaolins,driver_mikiej,driver_spcking2,driver_stratgyx,driver_stratgys,driver_sbasketu,driver_sbasketo,driver_sbasketb,driver_pc_suprc,driver_scobra,driver_scobrase,driver_scobras,driver_tactcian,driver_tactcan2,driver_pc_tmnt,driver_pc_tmnt2,driver_theend,driver_theends,driver_pc_goons,driver_thehustj,driver_thehustl,driver_mainev2p,driver_mainevto,driver_mainevt,driver_timeplt,driver_timeplta,driver_timepltc,driver_tp84,driver_tp84a,driver_jackalj,driver_topgunr,driver_trackfld,driver_trackflc,driver_pc_tkfld,driver_tricktrp,driver_turpin,driver_turtles,driver_tutankhm,driver_tutankst,driver_hustler,driver_cstlevna,driver_vsgradus,driver_goonies,driver_topgun,driver_wizzquiz,driver_yiear,driver_yiear2"

COREDEFS += -DTINY_POINTER="&driver_600,&driver_amidar,&driver_amidaro,&driver_amidars,&driver_amidaru,&driver_battlnts,&driver_battlntj,&driver_bladstle,&driver_bladestl,&driver_bootcamp,&driver_bottom9n,&driver_bottom9,&driver_pc_cvnia,&driver_circusc,&driver_circuscc,&driver_circusce,&driver_circusc2,&driver_combascj,&driver_combasc,&driver_combasct,&driver_contraj,&driver_pc_cntra,&driver_contra,&driver_nss_con3,&driver_dairesya,&driver_devstor3,&driver_devstor2,&driver_devstors,&driver_ddribble,&driver_pc_dbldr,&driver_fastlane,&driver_finalizr,&driver_flkatck,&driver_frogger,&driver_frogseg1,&driver_frogseg2,&driver_garuka,&driver_pc_grdus,&driver_pc_grdue,&driver_gberet,&driver_gryzor,&driver_gutangtn,&driver_gyrussce,&driver_gyruss,&driver_hexion,&driver_hyprolym,&driver_hpolym84,&driver_hyperspt,&driver_ironhors,&driver_jackal,&driver_jailbrek,&driver_jungler,&driver_junglers,&driver_junofrst,&driver_junofstg,&driver_kicker,&driver_rockragj,&driver_labyrunr,&driver_labyrunk,&driver_lethalej,&driver_lethalen,&driver_locomotn,&driver_mstadium,&driver_manhatan,&driver_megaznik,&driver_megazone,&driver_megazona,&driver_megazonb,&driver_megazonc,&driver_mikie,&driver_mikiehs,&driver_mogura,&driver_mrgoemon,&driver_mx5000,&driver_pandoras,&driver_pingpong,&driver_pooyan,&driver_pooyans,&driver_rackemup,&driver_ringohja,&driver_roadf,&driver_roadf2,&driver_rockraga,&driver_rockrage,&driver_rocnrope,&driver_rocnropk,&driver_pc_rnatk,&driver_rushatck,&driver_spyu,&driver_spy,&driver_scotrsht,&driver_scramble,&driver_scrambls,&driver_shaolins,&driver_mikiej,&driver_spcking2,&driver_stratgyx,&driver_stratgys,&driver_sbasketu,&driver_sbasketo,&driver_sbasketb,&driver_pc_suprc,&driver_scobra,&driver_scobrase,&driver_scobras,&driver_tactcian,&driver_tactcan2,&driver_pc_tmnt,&driver_pc_tmnt2,&driver_theend,&driver_theends,&driver_pc_goons,&driver_thehustj,&driver_thehustl,&driver_mainev2p,&driver_mainevto,&driver_mainevt,&driver_timeplt,&driver_timeplta,&driver_timepltc,&driver_tp84,&driver_tp84a,&driver_jackalj,&driver_topgunr,&driver_trackfld,&driver_trackflc,&driver_pc_tkfld,&driver_tricktrp,&driver_turpin,&driver_turtles,&driver_tutankhm,&driver_tutankst,&driver_hustler,&driver_cstlevna,&driver_vsgradus,&driver_goonies,&driver_topgun,&driver_wizzquiz,&driver_yiear,&driver_yiear2"

# uses these CPUs
CPUS+=G65816@
CPUS+=HD6309@
CPUS+=I8039@
CPUS+=M6800@
CPUS+=M6809@
CPUS+=N2A03@
CPUS+=SPC700@
CPUS+=Z80@


# uses these SOUNDs
SOUNDS+=AY8910@
SOUNDS+=CUSTOM@
SOUNDS+=DAC@
SOUNDS+=K007232@
SOUNDS+=K051649@
SOUNDS+=K054539@
SOUNDS+=NES@
SOUNDS+=OKIM6295@
SOUNDS+=SAMPLES@
SOUNDS+=SN76496@
SOUNDS+=UPD7759@
SOUNDS+=VLM5030@
SOUNDS+=YM2151@
SOUNDS+=YM2203@
SOUNDS+=YM3812@

SOUNDS+=TMS5110@
SOUNDS+=TMS36XX@
SOUNDS+=DISCRETE@
SOUNDS+=NAMCO@

#SOUNDS+=K053260@
#SOUNDS+=MSM5205@


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
