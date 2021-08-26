CFLAGS = --std c90
DBFLAGS = -g -O0 -da -Wall -Wextra

ifeq ($(MAKECMDGOALS), debug)
FLAGS = $(CFLAGS) $(DBFLAGS)
else
FLAGS = $(CFLAGS)
endif

demo: npc.o room.o strfun.o item.o error.o player.o combat.o
	$(CC) $(FLAGS) main.c -o demo *.o

combat.o:
	$(CC) $(FLAGS) -c ../src/combat.c -o combat.o

player.o:
	$(CC) $(FLAGS) -c ../src/player.c -o player.o

npc.o:
	$(CC) $(FLAGS) -c ../src/npc.c -o npc.o

item.o:
	$(CC) $(FLAGS) -c ../src/item.c -o item.o

error.o:
	$(CC) $(FLAGS) -c ../src/error.c -o error.o

room.o: npc.o
	$(CC) $(FLAGS) -c ../src/room.c -o room.o

strfun.o:
	$(CC) $(FLAGS) -c ../src/strfun.c -o strfun.o

run: demo
	./demo

debug: demo

clean:
	$(RM) *.o
	$(RM) demo