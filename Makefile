# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright 2001-2022, ps2dev - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.

EE_BIN = hello.elf

# KERNEL_NOPATCH = 1
# NEWLIB_NANO = 1

EE_OBJS = main.o ioprp.o
EE_CXXFLAGS += -fdata-sections -ffunction-sections
EE_LDFLAGS += -Wl,--gc-sections
EE_LIBS += -liopreboot -lpatches
.INTERMEDIATE: ioprp.c $(EE_OBJS)
ioprp.c: ioprp.img
	bin2c $< $@ ioprp

ifeq ($(DEBUG), 1)
  EE_CXXFLAGS += -DDEBUG -O0 -g
else 
  EE_CXXFLAGS += -Os
  EE_LDFLAGS += -s
endif

all: $(EE_BIN)

clean:
	rm -rf $(EE_OBJS) $(EE_BIN) ioprp.c

# Include makefiles
include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal_cpp
