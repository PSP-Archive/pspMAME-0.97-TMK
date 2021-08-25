# a tiny compile is without Neogeo games
COREDEFS += -DTINY_COMPILE=1
COREDEFS += -DTINY_NAME="driver_pc_1942,driver_1942,driver_1942a,driver_1942b,driver_1943kai,driver_1943j,driver_1943,driver_hatena,driver_lwingsjp,driver_avengers,driver_avenger2,driver_bionicc,driver_bionicc2,driver_blkdrgon,driver_blktiger,driver_blockj,driver_blocka,driver_block,driver_bbros,driver_cbasebal,driver_cworld,driver_pc_rrngr,driver_commandu,driver_commando,driver_dokaben,driver_exedexes,driver_f1dream,driver_gngt,driver_gng,driver_gnga,driver_mt_gng,driver_gunsmokj,driver_gunsmoku,driver_gunsmoka,driver_gunsmoke,driver_buraiken,driver_lastduel,driver_lstduela,driver_ledstorm,driver_lwings,driver_lwings2,driver_madgearj,driver_madgear,driver_makaimuc,driver_makaimug,driver_makaimur,driver_pc_mman3,driver_higemaru,driver_qsangoku,driver_qtono1,driver_rushcrsh,driver_savgbees,driver_sectionz,driver_sctionza,driver_commandj,driver_sidearjp,driver_sidearmr,driver_sidearms,driver_slipstrm,driver_sonson,driver_sonsonj,driver_sinvasn,driver_sfjp,driver_sfp,driver_sfus,driver_sf,driver_sftm110,driver_sftm111,driver_sftm,driver_sftmj,driver_trojanj,driver_srumbler,driver_srumblr2,driver_tigeroad,driver_topsecrt,driver_toramich,driver_pc_trjan,driver_trojanr,driver_trojan,driver_vulgusj,driver_vulgus,driver_vulgus2,driver_pc_ynoid"

COREDEFS += -DTINY_POINTER="&driver_pc_1942,&driver_1942,&driver_1942a,&driver_1942b,&driver_1943kai,&driver_1943j,&driver_1943,&driver_hatena,&driver_lwingsjp,&driver_avengers,&driver_avenger2,&driver_bionicc,&driver_bionicc2,&driver_blkdrgon,&driver_blktiger,&driver_blockj,&driver_blocka,&driver_block,&driver_bbros,&driver_cbasebal,&driver_cworld,&driver_pc_rrngr,&driver_commandu,&driver_commando,&driver_dokaben,&driver_exedexes,&driver_f1dream,&driver_gngt,&driver_gng,&driver_gnga,&driver_mt_gng,&driver_gunsmokj,&driver_gunsmoku,&driver_gunsmoka,&driver_gunsmoke,&driver_buraiken,&driver_lastduel,&driver_lstduela,&driver_ledstorm,&driver_lwings,&driver_lwings2,&driver_madgearj,&driver_madgear,&driver_makaimuc,&driver_makaimug,&driver_makaimur,&driver_pc_mman3,&driver_higemaru,&driver_qsangoku,&driver_qtono1,&driver_rushcrsh,&driver_savgbees,&driver_sectionz,&driver_sctionza,&driver_commandj,&driver_sidearjp,&driver_sidearmr,&driver_sidearms,&driver_slipstrm,&driver_sonson,&driver_sonsonj,&driver_sinvasn,&driver_sfjp,&driver_sfp,&driver_sfus,&driver_sf,&driver_sftm110,&driver_sftm111,&driver_sftm,&driver_sftmj,&driver_trojanj,&driver_srumbler,&driver_srumblr2,&driver_tigeroad,&driver_topsecrt,&driver_toramich,&driver_pc_trjan,&driver_trojanr,&driver_trojan,&driver_vulgusj,&driver_vulgus,&driver_vulgus2,&driver_pc_ynoid"

# cpuintrf.c cpuintrf.h cheat.c audit.c memory.c info.c sndintrf.c sndintrf.h usrintrf.c psp/fronthlp.c

# uses these CPUs
CPUS+=M68000@
CPUS+=M68EC020@
CPUS+=M6809@
CPUS+=N2A03@
CPUS+=V60@
CPUS+=Z80@


# uses these SOUNDs
SOUNDS+=AY8910@
SOUNDS+=DAC@
SOUNDS+=ES5506@
SOUNDS+=MSM5205@
SOUNDS+=NES@
SOUNDS+=OKIM6295@
SOUNDS+=RF5C68@
SOUNDS+=SN76496@
SOUNDS+=YM2151@
SOUNDS+=YM2203@
SOUNDS+=YM2413@
SOUNDS+=YM3438@

SOUNDS+=UPD7759@
SOUNDS+=MULTIPCM@

#SOUNDS+=CUSTOM@
#SOUNDS+=DISCRETE@
#SOUNDS+=NAMCO@
#SOUNDS+=NAMCO_15XX@
#SOUNDS+=NAMCO_52XX@
#SOUNDS+=NAMCO_54XX@
#SOUNDS+=NAMCO_CUS30@
#SOUNDS+=POKEY@
#SOUNDS+=SAMPLES@
#SOUNDS+=SN76477@
#SOUNDS+=VLM5030@
#SOUNDS+=YM3526@
#SOUNDS+=YM3812@



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
