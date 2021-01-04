PSP_FW_VERSION=200

PSPSDK=$(shell psp-config --pspsdk-path)

CC       = psp-gcc
CXX      = psp-g++
AS       = psp-gcc
LD       = psp-gcc
AR       = psp-ar
RANLIB   = psp-ranlib
STRIP    = psp-strip
MKSFO    = mksfo
PACK_PBP = pack-pbp
FIXUP    = psp-fixup-imports

CFLAGS += -G0 -D_HUGE=HUGE_VAL -DCLIB_DECL= -I$(PSPSDK)/include
ASMFLAGS = -g -c -xassembler -O


# add libs
#TMK LIBS += -lalleg -laudio -lemu -lzvg
#LIBS = -L$(PSPSDK)/lib -lpspgu -lpspge -lc -lm /usr/local/pspdev/lib/gcc/psp/4.0.1/libgcc.a
LIBS = -L$(PSPSDK)/lib -lpspgu -lpspge -lpsppower -lpspaudiolib -lpspaudio -lm -lc

# only PSP specific output files and rules
OSOBJS = $(OBJ)/psp/psp.o $(OBJ)/psp/video.o $(OBJ)/psp/blit.o \
	$(OBJ)/psp/sound.o $(OBJ)/psp/input.o $(OBJ)/psp/rc.o $(OBJ)/psp/misc.o \
	$(OBJ)/psp/ticker.o $(OBJ)/psp/config.o $(OBJ)/psp/fronthlp.o \
	$(OBJ)/psp/fileio.o $(OBJ)/psp/debugwin.o \
    $(OBJ)/psp/pg.o $(OBJ)/psp/pspmain.o $(OBJ)/psp/menu.o \
	$(OBJ)/psp/pspgu.o \

#	$(OBJ)/psp/syscalls.o \
#	$(OBJ)/psp/y_malloc.o \
#	$(OBJ)/psp/y_malloc.o \
#	$(OBJ)/psp/v_malloc.o \
#	$(OBJ)/psp/malloc.o \
#	$(OBJ)/psp/fpgnulib.o \

# startup functions
#$(OBJ)/psp/startup.o: src/psp/startup.s
#	@echo Assembling $<...
#	$(CC) -o $@ $(ASMFLAGS) $(subst -D,-d,$(ASMDEFS)) $<

# $(OBJ)/psp/fpgnulib.o: src/psp/fpgnulib.c

