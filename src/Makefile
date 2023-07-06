PROJECT_NAME = garden_quest

GBDK_PATH = /opt/gbdk/
BUILD_PATH = build/

LCC = $(GBDK_PATH)bin/lcc

# Set platforms to build here, spaced separated. (These are in the separate Makefile.targets)
# They can also be built/cleaned individually: "make gg" and "make gg-clean"
# Possible are: gb gbc pocket megaduck sms gg
TARGETS=gb

# Configure platform specific LCC flags here:
LCCFLAGS_gb     = -Wm-ys -Wl-yt0x1B -autobank -DMUSIC_DRIVER_GBT # Set an MBC for banking (1B-ROM+MBC5+RAM+BATT)
LLCFLAGS_other 	= -Wa-l -Wl-m -Wl-j # Link with the small library
LLCFLAGS_dn     = -Wa-l -c -o main.o main.c #  main.o main.c dont link just compile
LLCFLAGS_dt     = -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o 

AS = $(LCC) -c
CC = $(LCC) $(LCCFLAGS_gb)

BIN = $(PROJECT_NAME).gb
OBJS =  main.o Background.o Font.o 

all: $(BIN)

# Include available build targets - Compile and link single file in one pass
# -o flag specifies the output file
# $@ evaluates to the target (the .o file)
# $< evaluates to the first prerequisite (the .c file)
# $(BIN): $(OBJS)
# 	$(CC) -o $@ $<


# Manually target objects
$(BIN): $(OBJS)
	$(CC) -o $(BIN) main.o Background.o Font.o 

main.o: main.c ./Graphics/Background.h ./Graphics/Font.h
	@echo compiling $<
	$(CC) -c main.c

Background.o: ./Graphics/Background.c ./Graphics/Background.h
	@echo compiling $<
	$(CC) -c ./Graphics/Background.c

Font.o: ./Graphics/Font.c ./Graphics/Font.h
	@echo compiling $<
	$(CC) -c ./Graphics/Font.c

# This is broken, I need to figure out how to compile the music driver
# Music.o: Music.c ./Music/gbt_player.h ./Music/gbt_player.s ./Music/gbt_player_bank1.s ./Music/Music.h
# 	@echo compiling $<
# 	$(CC) -c ./Music/Music.c



clean:
	sh ./utils/clean.sh


