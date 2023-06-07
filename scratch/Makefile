AS = lcc -c
CC = lcc -Wa-l -Wl-m

BIN = movement.gb
OBJS = movement.o player.o

all: $(BIN)

%.s: %.ms
	maccer -o $@ $<

$(BIN): $(OBJS)
	$(CC) -o $(BIN) $(OBJS)

clean:
	rm -rf $(BIN) $(OBJS) *~
