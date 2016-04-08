CC=gcc
CFLAGS=-Wall
#LIBS=-lcurses

all: battle_ship

battle_ship: *.o 
    $(CC) $(CFLAGS) -o battle_ship main.o library.o ui.o

.c.o: battle_ship.h $<
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f battle_ship
