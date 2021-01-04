# a tiny compile is without Neogeo games
COREDEFS += -DTINY_COMPILE=1
COREDEFS += -DTINY_NAME="driver_arescue,driver_alien3,driver_arabfgtj,driver_arabfgt,driver_bakubaku,driver_bel,driver_brivalj,driver_brival,driver_colmns97,driver_coolridr,driver_darkedgj,driver_darkedge,driver_daytona,driver_daytonam,driver_daytonat,driver_daytona2,driver_doaa,driver_doa,driver_decathlt,driver_desert,driver_diehard,driver_dirtdvls,driver_dbzvrvs,driver_dynabb,driver_dynamcop,driver_dynmcopb,driver_dnmtdeka,driver_dyndeka2,driver_ejihon,driver_f1en,driver_f1lap,driver_fvipers,driver_finlarch,driver_fhboxers,driver_gaxeduel,driver_ga2j,driver_ga2u,driver_ga2,driver_gunblade,driver_hanagumi,driver_harddunj,driver_harddunk,driver_harley,driver_holo,driver_hotd,driver_indy500,driver_jpark,driver_lastbrnx,driver_lastbrnj,driver_manxtt,driver_maruchan,driver_orunners,driver_radmu,driver_radm,driver_radru,driver_radr,driver_sandor,driver_scud,driver_scuda,driver_bass,driver_srally2,driver_srallyc,driver_stcc,driver_sonicp,driver_sonic,driver_skytargt,driver_schamp,driver_spideyu,driver_spidey,driver_sfish2j,driver_sfish2,driver_scross,driver_swa,driver_swtrilgy,driver_smleague,driver_svf,driver_svs,driver_sassisu,driver_jleague,driver_lostwsga,driver_titlefu,driver_titlef,driver_topskatr,driver_thunt,driver_vcop,driver_vcop2,driver_vf,driver_vf2o,driver_vf2,driver_vf2b,driver_vf3,driver_vf3tb,driver_vfkids,driver_vfremix,driver_vformula,driver_vr,driver_vstriker,driver_vstrikra,driver_vs215,driver_vs2,driver_vs29815,driver_vs298,driver_vs299,driver_vs2v991,driver_von2,driver_von254g,driver_von,driver_vonusa,driver_wingwara,driver_wingwar,driver_winterht,driver_znpwfv"

COREDEFS += -DTINY_POINTER="&driver_arescue,&driver_alien3,&driver_arabfgtj,&driver_arabfgt,&driver_bakubaku,&driver_bel,&driver_brivalj,&driver_brival,&driver_colmns97,&driver_coolridr,&driver_darkedgj,&driver_darkedge,&driver_daytona,&driver_daytonam,&driver_daytonat,&driver_daytona2,&driver_doaa,&driver_doa,&driver_decathlt,&driver_desert,&driver_diehard,&driver_dirtdvls,&driver_dbzvrvs,&driver_dynabb,&driver_dynamcop,&driver_dynmcopb,&driver_dnmtdeka,&driver_dyndeka2,&driver_ejihon,&driver_f1en,&driver_f1lap,&driver_fvipers,&driver_finlarch,&driver_fhboxers,&driver_gaxeduel,&driver_ga2j,&driver_ga2u,&driver_ga2,&driver_gunblade,&driver_hanagumi,&driver_harddunj,&driver_harddunk,&driver_harley,&driver_holo,&driver_hotd,&driver_indy500,&driver_jpark,&driver_lastbrnx,&driver_lastbrnj,&driver_manxtt,&driver_maruchan,&driver_orunners,&driver_radmu,&driver_radm,&driver_radru,&driver_radr,&driver_sandor,&driver_scud,&driver_scuda,&driver_bass,&driver_srally2,&driver_srallyc,&driver_stcc,&driver_sonicp,&driver_sonic,&driver_skytargt,&driver_schamp,&driver_spideyu,&driver_spidey,&driver_sfish2j,&driver_sfish2,&driver_scross,&driver_swa,&driver_swtrilgy,&driver_smleague,&driver_svf,&driver_svs,&driver_sassisu,&driver_jleague,&driver_lostwsga,&driver_titlefu,&driver_titlef,&driver_topskatr,&driver_thunt,&driver_vcop,&driver_vcop2,&driver_vf,&driver_vf2o,&driver_vf2,&driver_vf2b,&driver_vf3,&driver_vf3tb,&driver_vfkids,&driver_vfremix,&driver_vformula,&driver_vr,&driver_vstriker,&driver_vstrikra,&driver_vs215,&driver_vs2,&driver_vs29815,&driver_vs298,&driver_vs299,&driver_vs2v991,&driver_von2,&driver_von254g,&driver_von,&driver_vonusa,&driver_wingwara,&driver_wingwar,&driver_winterht,&driver_znpwfv"


# uses these CPUs
CPUS+=M68000@
CPUS+=I960@
CPUS+=PPC603@
CPUS+=SH2@
CPUS+=V20@
CPUS+=V60@
CPUS+=Z80@

#CPUS+=I8751@
#CPUS+=N7751@
#CPUS+=Z80@

#CPUS+=I8752@
#CPUS+=N2A03@


#CPUS+=8080@
#CPUS+=I8035@
#CPUS+=I8039@

#CPUS+=N2A03@

#CPUS+=I8751@
#CPUS+=I8051@
#CPUS+=I8052@


# uses these SOUNDs
SOUNDS+=MULTIPCM@
SOUNDS+=RF5C68@
SOUNDS+=SCSP@
SOUNDS+=YM3438@


#SOUNDS+=DAC@
#SOUNDS+=SEGAPCM@
#SOUNDS+=SN76496@
#SOUNDS+=UPD7759@
#SOUNDS+=YM2151@
#SOUNDS+=YM2203@
#SOUNDS+=YM2610@

#SOUNDS+=YM2610B@
#SOUNDS+=OKIM6295@
#SOUNDS+=YM2413@

#SOUNDS+=TMS5110@
#SOUNDS+=SAMPLES@
#SOUNDS+=NES@

#SOUNDS+=AY8910@
#SOUNDS+=CUSTOM@
#SOUNDS+=MSM5205@
#SOUNDS+=NAMCO@
#SOUNDS+=SP0250@
#SOUNDS+=TMS36XX@
#SOUNDS+=TMS5110@
#SOUNDS+=DISCRETE@
#SOUNDS+=YM3812@
#SOUNDS+=SEGAPCM@
#SOUNDS+=YM2612@

#OBJS=	$(OBJ)/machine/scramble.o $(OBJ)/sndhrdw/scramble.o $(OBJ)/drivers/scramble.o \
#		$(OBJ)/drivers/amidar.o \
#		$(OBJ)/drivers/frogger.o \
#		$(OBJ)/drivers/scobra.o \
#		$(OBJ)/vidhrdw/galaxian.o $(OBJ)/sndhrdw/galaxian.o $(OBJ)/drivers/galaxian.o \
#			$(OBJ)/vidhrdw/bagman.o $(OBJ)/machine/bagman.o $(OBJ)/drivers/bagman.o \
#			$(OBJ)/vidhrdw/pacman.o $(OBJ)/drivers/pacman.o \
#				$(OBJ)/vidhrdw/epos.o $(OBJ)/drivers/epos.o \
#				$(OBJ)/machine/mspacman.o $(OBJ)/machine/pacplus.o \
#				$(OBJ)/machine/jumpshot.o $(OBJ)/machine/theglobp.o \
#				$(OBJ)/machine/acitya.o \
#			$(OBJ)/vidhrdw/phoenix.o $(OBJ)/sndhrdw/phoenix.o $(OBJ)/drivers/phoenix.o \
#				$(OBJ)/sndhrdw/pleiads.o \
#			$(OBJ)/vidhrdw/cclimber.o $(OBJ)/sndhrdw/cclimber.o $(OBJ)/drivers/cclimber.o \
#			$(OBJ)/vidhrdw/ladybug.o $(OBJ)/drivers/ladybug.o \


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
