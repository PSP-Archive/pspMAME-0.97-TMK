# a tiny compile is without Neogeo games
COREDEFS += -DTINY_COMPILE=1
COREDEFS += -DTINY_NAME="driver_pc_1942,driver_nss_actr,driver_pc_bfght,driver_pc_bball,driver_pc_bstar,driver_pc_cshwk,driver_pc_cvnia,driver_pc_rrngr,driver_pc_cntra,driver_nss_con3,driver_nss_aten,driver_pc_ddrgn,driver_pc_dbldr,driver_pc_drmro,driver_pc_duckh,driver_pc_ebike,driver_nss_fzer,driver_pc_gntlt,driver_pc_golf,driver_pc_grdus,driver_pc_grdue,driver_pc_hgaly,driver_pc_kngfu,driver_nss_lwep,driver_pc_mario,driver_pc_moglf,driver_pc_mman3,driver_pc_mtoid,driver_pc_miket,driver_nss_ncaa,driver_pc_ngaid,driver_pc_ngai2,driver_pc_ngai3,driver_pc_wcup,driver_pc_pinbt,driver_pc_pwbld,driver_pc_pwrst,driver_pc_rcpam,driver_pc_radrc,driver_pc_radr2,driver_nss_rob3,driver_pc_rkats,driver_pc_rnatk,driver_pc_rygar,driver_nss_skin,driver_pc_sjetm,driver_pc_suprc,driver_pc_smb,driver_pc_smb2,driver_pc_smb3,driver_nss_smw,driver_nss_ssoc,driver_nss_sten,driver_pc_tbowl,driver_pc_tmnt,driver_pc_tmnt2,driver_pc_tenis,driver_nss_adam,driver_pc_goons,driver_pc_tkfld,driver_pc_trjan,driver_pc_ftqst,driver_pc_vball,driver_rbibb,driver_rbibba,driver_balonfgt,driver_vsbball,driver_vsbballj,driver_vsbbalja,driver_vsbbaljb,driver_btlecity,driver_cstlevna,driver_cluclu,driver_drmario,driver_duckhunt,driver_excitebk,driver_excitbkj,driver_vsfdf,driver_vsgradus,driver_vsgshoe,driver_hogalley,driver_iceclimb,driver_iceclmbj,driver_iceclmrj,driver_machridr,driver_machridj,driver_vsmahjng,driver_mightybj,driver_jajamaru,driver_vspinbal,driver_vspinblj,driver_platoon,driver_bnglngby,driver_vsslalom,driver_vssoccer,driver_starlstr,driver_ladygolf,driver_smgolfb,driver_smgolf,driver_smgolfj,driver_suprmrio,driver_vsskykid,driver_supxevs,driver_vstennis,driver_vstennij,driver_vstetris,driver_goonies,driver_tkoboxng,driver_topgun,driver_wrecking,driver_pc_wgnmn,driver_pc_ynoid"

COREDEFS += -DTINY_POINTER="&driver_pc_1942,&driver_nss_actr,&driver_pc_bfght,&driver_pc_bball,&driver_pc_bstar,&driver_pc_cshwk,&driver_pc_cvnia,&driver_pc_rrngr,&driver_pc_cntra,&driver_nss_con3,&driver_nss_aten,&driver_pc_ddrgn,&driver_pc_dbldr,&driver_pc_drmro,&driver_pc_duckh,&driver_pc_ebike,&driver_nss_fzer,&driver_pc_gntlt,&driver_pc_golf,&driver_pc_grdus,&driver_pc_grdue,&driver_pc_hgaly,&driver_pc_kngfu,&driver_nss_lwep,&driver_pc_mario,&driver_pc_moglf,&driver_pc_mman3,&driver_pc_mtoid,&driver_pc_miket,&driver_nss_ncaa,&driver_pc_ngaid,&driver_pc_ngai2,&driver_pc_ngai3,&driver_pc_wcup,&driver_pc_pinbt,&driver_pc_pwbld,&driver_pc_pwrst,&driver_pc_rcpam,&driver_pc_radrc,&driver_pc_radr2,&driver_nss_rob3,&driver_pc_rkats,&driver_pc_rnatk,&driver_pc_rygar,&driver_nss_skin,&driver_pc_sjetm,&driver_pc_suprc,&driver_pc_smb,&driver_pc_smb2,&driver_pc_smb3,&driver_nss_smw,&driver_nss_ssoc,&driver_nss_sten,&driver_pc_tbowl,&driver_pc_tmnt,&driver_pc_tmnt2,&driver_pc_tenis,&driver_nss_adam,&driver_pc_goons,&driver_pc_tkfld,&driver_pc_trjan,&driver_pc_ftqst,&driver_pc_vball,&driver_rbibb,&driver_rbibba,&driver_balonfgt,&driver_vsbball,&driver_vsbballj,&driver_vsbbalja,&driver_vsbbaljb,&driver_btlecity,&driver_cstlevna,&driver_cluclu,&driver_drmario,&driver_duckhunt,&driver_excitebk,&driver_excitbkj,&driver_vsfdf,&driver_vsgradus,&driver_vsgshoe,&driver_hogalley,&driver_iceclimb,&driver_iceclmbj,&driver_iceclmrj,&driver_machridr,&driver_machridj,&driver_vsmahjng,&driver_mightybj,&driver_jajamaru,&driver_vspinbal,&driver_vspinblj,&driver_platoon,&driver_bnglngby,&driver_vsslalom,&driver_vssoccer,&driver_starlstr,&driver_ladygolf,&driver_smgolfb,&driver_smgolf,&driver_smgolfj,&driver_suprmrio,&driver_vsskykid,&driver_supxevs,&driver_vstennis,&driver_vstennij,&driver_vstetris,&driver_goonies,&driver_tkoboxng,&driver_topgun,&driver_wrecking,&driver_pc_wgnmn,&driver_pc_ynoid"


# uses these CPUs
CPUS+=G65816@
CPUS+=N2A03@
CPUS+=SPC700@
CPUS+=Z80@


# uses these SOUNDs
SOUNDS+=CUSTOM@
SOUNDS+=DAC@
SOUNDS+=NES@


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
