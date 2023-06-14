PROJECT_NAME = garden_quest

GBDK_PATH = /opt/gbdk/
BUILD_PATH = build/

LCC = $(GBDK_PATH)bin/lcc

# Set platforms to build here, spaced separated. (These are in the separate Makefile.targets)
# They can also be built/cleaned individually: "make gg" and "make gg-clean"
# Possible are: gb gbc pocket megaduck sms gg
TARGETS=gb

# Configure platform specific LCC flags here:
LCCFLAGS_gb     = -Wm-ys -Wl-yt0x1B -autobank # Set an MBC for banking (1B-ROM+MBC5+RAM+BATT)
LLCFLAGS_other 	= -Wa-l -Wl-m -Wl-j # Link with the small library
LLCFLAGS_dn     = -Wa-l -c -o main.o main.c #  main.o main.c dont link just compile

AS = $(LCC) -c
CC = $(LCC) $(LCCFLAGS_gb)

BIN = $(PROJECT_NAME).gb
OBJS = main.o player.o font.o

all: $(BIN)

# Include available build targets

# Compile and link single file in one pass
$(BIN):	main.c player.c player.h font.c font.h
	$(CC) -o $@ $<

clean:
	rm -f *.o *.lst *.map *.gb *~ *.rel *.cdb *.ihx *.lnk *.sym *.asm *.noi
