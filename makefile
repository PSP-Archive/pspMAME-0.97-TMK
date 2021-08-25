# set this to mame, mess or the destination you want to build
# TARGET = mame
# TARGET = mess
# example for a tiny compile
# TARGET = tiny
ifeq ($(TARGET),)
TARGET = mame
endif

# uncomment one of the next lines to build a target-optimized build
# ATHLON = 1
# I686 = 1
# P4 = 1
# PM = 1
#PSP =1
#PSP2 =1
PSP3 =1

# uncomment next line to include the symbols for symify
# SYMBOLS = 1

# uncomment next line to generate a link map for exception handling in windows
# MAP = 1

# uncomment next line to include the debugger
# DEBUG = 1

# uncomment next line to use the new multiwindow debugger
NEW_DEBUGGER = 1

# uncomment next line to use DRC MIPS3 engine
#X86_MIPS3_DRC = 1

# uncomment next line to use DRC PowerPC engine
#X86_PPC_DRC = 1

# uncomment next line to use cygwin compiler
# COMPILESYSTEM_CYGWIN	= 1

# uncomment next line to build expat as part of MAME build
BUILD_EXPAT = 1

# uncomment next line to build zlib as part of MAME build
BUILD_ZLIB = 1

# cpu emulation
#CZ80=1
C6809_BUILD=1

# set this the operating system you're building for
# MAMEOS = msdos
# MAMEOS = windows
MAMEOS = psp
MAMEOS2 = psp3
ifeq ($(MAMEOS),)
MAMEOS = windows
endif

# extension for executables
EXE = .exe

# CPU core include paths
VPATH=src $(wildcard src/cpu/*)

# compiler, linker and utilities
AR = @ar
CC = @gcc
LD = @gcc
ASM = @nasm
#TMK ASMFLAGS = -f coff
#ASMFLAGS = -march=r4000 -g -mabi=eabi -mgp32 -c -xassembler -O
MD = -mkdir
RM = @rm -f


ifeq ($(MAMEOS),msdos)
PREFIX = d
else
PREFIX =
endif

# by default, compile for Pentium target and add no suffix
NAME = $(PREFIX)$(TARGET)$(SUFFIX)
ARCH = -march=pentium

# architecture-specific builds get extra options and a suffix
ifdef ATHLON
NAME = $(PREFIX)$(TARGET)$(SUFFIX)at
ARCH = -march=athlon
endif

ifdef I686
NAME = $(PREFIX)$(TARGET)$(SUFFIX)pp
ARCH = -march=pentiumpro
endif

ifdef P4
NAME = $(PREFIX)$(TARGET)$(SUFFIX)p4
ARCH = -march=pentium4
endif

ifdef PM
NAME = $(PREFIX)$(TARGET)$(SUFFIX)pm
ARCH = -march=pentium3 -msse2
endif

ifdef PSP
NAME = $(PREFIX)$(TARGET)$(SUFFIX)psp
ARCH = -march=r4000 -mabi=eabi -mgp32 -mlong32 -msingle-float -fshort-double -include src/psp/floatonly.h
#ARCH = -march=r4000 -mabi=eabi -mgp32 -mlong32 -msingle-float
endif

ifdef PSP2
NAME = $(PREFIX)$(TARGET)$(SUFFIX)psp2
ARCH = -mabi=eabi -mgp32 -mlong32 -msingle-float -include src/psp/floatonly.h -include src/psp/stdout.h
MAMEOS2 = psp2
endif

ifdef PSP3
NAME = $(PREFIX)$(TARGET)$(SUFFIX)psp3
ARCH = 
MAMEOS2 = psp3
endif

# debug builds just get the 'd' suffix and nothing more
ifdef DEBUG
NAME = $(PREFIX)$(TARGET)$(SUFFIX)d
endif


# build the targets in different object dirs, since mess changes
# some structures and thus they can't be linked against each other.
OBJ = obj/$(NAME)

#TMK EMULATOR = $(NAME)$(EXE)
EMULATOR = EBOOT.PBP

#TMK DEFS = -DX86_ASM -DLSB_FIRST -DINLINE="static __inline__" -Dasm=__asm__ -DCRLF=3
DEFS = -DLSB_FIRST -DINLINE="static __inline__" -Dasm=__asm__ -DCRLF=3 -DPI=M_PI -DCLOCKS_PER_SEC=1000000
ifdef NEW_DEBUGGER
DEFS += -DNEW_DEBUGGER
endif

CFLAGS = -std=gnu99 -Isrc -Isrc/includes -Isrc/debug -Isrc/$(MAMEOS) -I$(OBJ)/cpu/m68000 -Isrc/cpu/m68000

ifdef SYMBOLS
CFLAGS += -O0 -Wall -Wno-unused -g
else
CFLAGS += -DNDEBUG \
	$(ARCH) -O3 -fomit-frame-pointer -fno-strict-aliasing \
	-Wall -Wno-sign-compare -Wunused \
	-Wpointer-arith -Wbad-function-cast -Wcast-align \
	-Wstrict-prototypes -Wundef \
	-Wformat-security -Wwrite-strings \
	-Wdisabled-optimization \
#	-Wno-unused-functions
#TMK	-Werror -Wall -Wno-sign-compare -Wunused -Wno-unused-functions \
#	-Wredundant-decls
#	-Wfloat-equal
#	-Wunreachable-code -Wpadded
#	-W had to remove because of the "missing initializer" warning
#	-Wlarger-than-262144  \
#	-Wcast-qual \
#	-Wconversion \
#	-Wmissing-prototypes \
#	-Wmissing-declarations
endif

# extra options needed *only* for the osd files
CFLAGSOSDEPEND = $(CFLAGS)

# the windows osd code at least cannot be compiled with -pedantic
CFLAGSPEDANTIC = $(CFLAGS) -pedantic

ifdef SYMBOLS
LDFLAGS =
else
#LDFLAGS = -s -Wl,--warn-common
LDFLAGS = -s
endif

ifdef MAP
MAPFLAGS = -Wl,-Map,$(NAME).map
else
MAPFLAGS =
endif

OBJDIRS = obj $(OBJ) $(OBJ)/cpu $(OBJ)/sound $(OBJ)/$(MAMEOS) \
	$(OBJ)/drivers $(OBJ)/machine $(OBJ)/vidhrdw $(OBJ)/sndhrdw $(OBJ)/debug pbp pbp/$(TARGET)
ifdef MESS
OBJDIRS += $(OBJ)/mess $(OBJ)/mess/systems $(OBJ)/mess/machine \
	$(OBJ)/mess/vidhrdw $(OBJ)/mess/sndhrdw $(OBJ)/mess/tools
endif

# start with an empty set of libs
LIBS = 

ifdef BUILD_EXPAT
CFLAGS += -Isrc/expat
OBJDIRS += $(OBJ)/expat
EXPAT = $(OBJ)/libexpat.a
else
LIBS += -lexpat
EXPAT =
endif

ifdef BUILD_ZLIB
CFLAGS += -Isrc/zlib
OBJDIRS += $(OBJ)/zlib
ZLIB = $(OBJ)/libz.a
else
LIBS += -lz
ZLIB =
endif

all:	maketree emulator extra

DESCJ =$(OBJ)/null_descj.o

# include the various .mak files
include src/core.mak
include makes/$(TARGET).mak
include src/rules.mak
include src/$(MAMEOS)/$(MAMEOS2).mak

COREOBJS += $(DESCJ)

ifdef DEBUG
DBGDEFS = -DMAME_DEBUG
else
DBGDEFS =
DBGOBJS =
endif

ifdef COMPILESYSTEM_CYGWIN
CFLAGS	+= -mno-cygwin
LDFLAGS	+= -mno-cygwin
endif

emulator: maketree $(EMULATOR)

#TMK extra:	$(TOOLS) $(TEXTS)
extra:	$(TEXTS)

# combine the various definitions to one
CDEFS = $(DEFS) $(COREDEFS) $(CPUDEFS) $(SOUNDDEFS) $(ASMDEFS) $(DBGDEFS)

ifeq ($(PSP_LARGE_MEMORY),1)
MKSFO = mksfoex -d MEMSIZE=1
endif

ifeq ($(PSP_FW_VERSION),)
PSP_FW_VERSION=150
endif

CFLAGS += -D_PSP_FW_VERSION=$(PSP_FW_VERSION)
CXXFLAGS += -D_PSP_FW_VERSION=$(PSP_FW_VERSION)

ifeq ($(BUILD_PRX),1)
	LDFLAGS  := $(addprefix -L,$(LIBDIR)) -specs=$(PSPSDK)/lib/prxspecs -Wl,-q,-T$(PSPSDK)/lib/linkfile.prx $(LDFLAGS)
	EXTRA_CLEAN += $(TARGET).elf
	# Setup default exports if needed
	ifdef PRX_EXPORTS
		EXPORT_OBJ=$(patsubst %.exp,%.o,$(PRX_EXPORTS))
		EXTRA_CLEAN += $(EXPORT_OBJ)
	else 
		EXPORT_OBJ=$(PSPSDK)/lib/prxexports.o
	endif
else
	LDFLAGS  := $(addprefix -L,$(LIBDIR)) $(LDFLAGS)
endif

# Library selection.  By default we link with Newlib's libc.  Allow the
# user to link with PSPSDK's libc if USE_PSPSDK_LIBC is set to 1.

ifeq ($(USE_KERNEL_LIBC),1)
	# Use the PSP's kernel libc
	PSPSDK_LIBC_LIB = 
	CFLAGS := -I$(PSPSDK)/include/libc $(CFLAGS)
else
	ifeq ($(USE_PSPSDK_LIBC),1)
		# Use the pspsdk libc
		PSPSDK_LIBC_LIB = -lpsplibc
		CFLAGS := -I$(PSPSDK)/include/libc $(CFLAGS)
	else
		# Use newlib (urgh)
		PSPSDK_LIBC_LIB = -lc
	endif
endif

# Link with following default libraries.  Other libraries should be specified in the $(LIBS) variable.
# TODO: This library list needs to be generated at configure time.
#
ifeq ($(USE_KERNEL_LIBS),1)
	PSPSDK_LIBS = -lpspdebug -lpspdisplay_driver -lpspctrl_driver -lpspsdk
	LIBS     := $(LIBS) $(PSPSDK_LIBS) $(PSPSDK_LIBC_LIB) -lpspkernel
else
	ifeq ($(USE_USER_LIBS),1)
		PSPSDK_LIBS = -lpspdebug -lpspdisplay -lpspge -lpspctrl -lpspsdk
		LIBS     := $(LIBS) $(PSPSDK_LIBS) $(PSPSDK_LIBC_LIB) -lpspnet \
				-lpspnet_inet -lpspnet_apctl -lpspnet_resolver -lpsputility \
				-lpspuser
	else
		PSPSDK_LIBS = -lpspdebug -lpspdisplay -lpspge -lpspctrl -lpspsdk
		LIBS     := $(LIBS) $(PSPSDK_LIBS) $(PSPSDK_LIBC_LIB) -lpspnet \
				-lpspnet_inet -lpspnet_apctl -lpspnet_resolver -lpsputility \
				-lpspuser -lpspkernel
	endif
endif

# Define the overridable parameters for EBOOT.PBP
ifndef PSP_EBOOT_TITLE
PSP_EBOOT_TITLE = PSPMAME 0.97 $(TARGET)
endif

ifndef PSP_EBOOT_SFO
PSP_EBOOT_SFO = PARAM.SFO
endif

ifndef PSP_EBOOT_ICON
PSP_EBOOT_ICON = Icon0.png
endif

ifndef PSP_EBOOT_ICON1
PSP_EBOOT_ICON1 = NULL
endif

ifndef PSP_EBOOT_UNKPNG
PSP_EBOOT_UNKPNG = NULL
endif

ifndef PSP_EBOOT_PIC1
PSP_EBOOT_PIC1 = NULL
endif

ifndef PSP_EBOOT_SND0
PSP_EBOOT_SND0 = NULL
endif

ifndef PSP_EBOOT_PSAR
PSP_EBOOT_PSAR = NULL
endif

ifndef PSP_EBOOT
PSP_EBOOT = EBOOT.PBP
endif

	
# primary target
$(EMULATOR): $(OBJS) $(COREOBJS) $(OSOBJS) $(DRVLIBS) $(EXPAT) $(ZLIB) $(OSDBGOBJS)
# always recompile the version string
	$(CC) $(CDEFS) $(CFLAGSPEDANTIC) -c src/version.c -o $(OBJ)/version.o
	@echo Linking $@...
	$(LINK.c) $^ $(LIBS) -o $(TARGET).elf
	$(FIXUP) $(TARGET).elf
	$(STRIP) $(TARGET).elf -o $(TARGET)_strip.elf
	$(MKSFO) '$(PSP_EBOOT_TITLE)' $(PSP_EBOOT_SFO)
	cp ./icon/$(TARGET).png ./Icon0.png
	$(PACK_PBP) $(PSP_EBOOT) $(PSP_EBOOT_SFO) $(PSP_EBOOT_ICON)  \
		$(PSP_EBOOT_ICON1) $(PSP_EBOOT_UNKPNG) $(PSP_EBOOT_PIC1)  \
		$(PSP_EBOOT_SND0)  $(TARGET)_strip.elf $(PSP_EBOOT_PSAR)
	-rm -f $(TARGET)_strip.elf
	cp $(PSP_EBOOT) pbp/$(TARGET)

#TMK	$(LD) $(LDFLAGS) $(OSDBGLDFLAGS) $^ $(LIBS) -o $@ $(MAPFLAGS)

#TMK romcmp$(EXE): $(OBJ)/romcmp.o $(OBJ)/unzip.o $(ZLIB) $(OSDBGOBJS)
#	@echo Linking $@...
#	$(LD) $(LDFLAGS) $(OSDBGLDFLAGS) $^ $(LIBS) -o $@
#
#chdman$(EXE): $(OBJ)/chdman.o $(OBJ)/chd.o $(OBJ)/chdcd.o $(OBJ)/cdrom.o $(OBJ)/md5.o $(OBJ)/sha1.o $(OBJ)/version.o $(ZLIB) $(OSDBGOBJS)
#	@echo Linking $@...
#	$(LD) $(LDFLAGS) $(OSDBGLDFLAGS) $^ $(LIBS) -o $@
#
#xml2info$(EXE): $(OBJ)/xml2info.o $(EXPAT) $(OSDBGOBJS)
#	@echo Linking $@...
#	$(LD) $(LDFLAGS) $(OSDBGLDFLAGS) $^ $(LIBS) -o $@

# secondary libraries
$(OBJ)/libexpat.a: $(OBJ)/expat/xmlparse.o $(OBJ)/expat/xmlrole.o $(OBJ)/expat/xmltok.o

$(OBJ)/libz.a: $(OBJ)/zlib/adler32.o $(OBJ)/zlib/compress.o $(OBJ)/zlib/crc32.o $(OBJ)/zlib/deflate.o \
				$(OBJ)/zlib/gzio.o $(OBJ)/zlib/inffast.o $(OBJ)/zlib/inflate.o $(OBJ)/zlib/infback.o \
				$(OBJ)/zlib/inftrees.o $(OBJ)/zlib/trees.o $(OBJ)/zlib/uncompr.o $(OBJ)/zlib/zutil.o

$(OBJ)/$(MAMEOS)/%.o: src/$(MAMEOS)/%.c
	@echo Compiling $<...
	$(CC) $(CDEFS) $(CFLAGSOSDEPEND) -c $< -o $@

$(OBJ)/%.o: src/%.c
	@echo Compiling $<...
	$(CC) $(CDEFS) $(CFLAGS) -c $< -o $@

# compile generated C files for the 68000 emulator
$(M68000_GENERATED_OBJS): $(OBJ)/cpu/m68000/m68kmake$(EXE)
	@echo Compiling $(subst .o,.c,$@)...
	$(CC) $(CDEFS) $(CFLAGSPEDANTIC) -c $*.c -o $@

# additional rule, because m68kcpu.c includes the generated m68kops.h :-/
$(OBJ)/cpu/m68000/m68kcpu.o: $(OBJ)/cpu/m68000/m68kmake$(EXE)

# generate C source files for the 68000 emulator
$(OBJ)/cpu/m68000/m68kmake$(EXE): src/cpu/m68000/m68kmake.c $(OSDBGOBJS)
	@echo M68K make $<...
	cp obj/m68000/m68k* $(OBJ)/cpu/m68000
#TMK	$(CC) $(CDEFS) $(CFLAGSPEDANTIC) -DDOS -o $(OBJ)/cpu/m68000/m68kmake$(EXE) $< $(OSDBGOBJS)
#	@echo Generating M68K source files...
#	$(OBJ)/cpu/m68000/m68kmake$(EXE) $(OBJ)/cpu/m68000 src/cpu/m68000/m68k_in.c

$(OBJ)/%.a:
	@echo Archiving $@...
	$(RM) $@
	$(AR) cr $@ $^

$(sort $(OBJDIRS)):
	$(MD) $@

maketree: $(sort $(OBJDIRS))

clean:
	@echo Deleting object tree $(OBJ)...
	$(RM) -r $(OBJ)
	@echo Deleting $(EMULATOR)...
	$(RM) $(EMULATOR)

check: $(EMULATOR) xml2info$(EXE)
	./$(EMULATOR) -listxml > $(NAME).xml
	./xml2info < $(NAME).xml > $(NAME).lst
	./xmllint --valid --noout $(NAME).xml
