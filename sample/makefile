CFLAGS = --std c90
DBFLAGS = -g -O0 -da -Wall -Wextra

ifeq ($(MAKECMDGOALS), debug)
FLAGS = $(CFLAGS) $(DBFLAGS)
else
FLAGS = $(CFLAGS)
endif

demo: npc.o room.o strfun.o
	$(CC) $(FLAGS) main.c -o demo *.o

npc.o:
	$(CC) $(FLAGS) -c ../src/npc.c -o npc.o

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