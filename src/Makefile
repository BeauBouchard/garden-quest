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
LLCFLAGS_dt     = -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o 

AS = $(LCC) -c
CC = $(LCC) $(LCCFLAGS_gb)

BIN = $(PROJECT_NAME).gb
OBJS =  main.o Background.o Font.o 

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) -o $(BIN) main.o Background.o Font.o

main.o: main.c Background.h Font.h
	$(CC) -c main.c

Background.o: Background.c Background.h
	$(CC) -c Background.c

Font.o: Font.c Font.h
	$(CC) -c Font.c

# Include available build targets - Compile and link single file in one pass
# -o flag specifies the output file
# $@ evaluates to the target (the .o file)
# $< evaluates to the first prerequisite (the .c file)
# $(BIN): $(OBJS)
# 	$(CC) -o $@ $<

clean:
	sh ./utils/clean.sh


