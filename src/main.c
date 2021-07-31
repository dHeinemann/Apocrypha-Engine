#include <ctype.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#define INPUT_LEN 20

enum Direction {
    DIRECTION_NORTH,
    DIRECTION_SOUTH,
    DIRECTION_EAST,
    DIRECTION_WEST,
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_IN,
    DIRECTION_OUT
};

struct Room {
    char* name;

    /* Exits */
    struct Room* north;
    struct Room* south;
    struct Room* east;
    struct Room* west;
    struct Room* up;
    struct Room* down;
    struct Room* in;
    struct Room* out;
};

static struct Room* currentRoom;

int travel(enum Direction dir) {
    struct Room* destination;

    destination = NULL;
    if (dir == DIRECTION_NORTH) { destination = currentRoom->north; }
    if (dir == DIRECTION_SOUTH) { destination = currentRoom->south; }
    if (dir == DIRECTION_EAST)  { destination = currentRoom->east;  }
    if (dir == DIRECTION_WEST)  { destination = currentRoom->west;  }
    if (dir == DIRECTION_UP)    { destination = currentRoom->up;    }
    if (dir == DIRECTION_DOWN)  { destination = currentRoom->down;  }
    if (dir == DIRECTION_IN)    { destination = currentRoom->in;    }
    if (dir == DIRECTION_OUT)   { destination = currentRoom->out;   }

    if (destination != NULL) {
        currentRoom = destination;
        return 1;
    } else {
        printf("There is no exit in that direction.\n");
        return 0;
    }
}

struct Room* createRoom(char* name) {
    struct Room* room;
    
    room = malloc(sizeof(struct Room));
    room->name = malloc(30);

    strcpy(room->name, name);
    room->north = NULL;
    room->south = NULL;
    room->east = NULL;
    room->west = NULL;
    room->up = NULL;
    room->down = NULL;
    room->in = NULL;
    room->out = NULL;

    return room;
}

void printRoom(struct Room* room) {
    int i;

    i = 0;
    while (room->name[i]) {
        printf("%c", (char) toupper((int) room->name[i]));
        i++;
    }
    printf("\n");
}

void printExits(struct Room* room) {
    printf("Exits:\n");
    printf("  ");
    if (room->north != NULL) { printf("north "); }
    if (room->south != NULL) { printf("south "); }
    if (room->east  != NULL) { printf("east ");  }
    if (room->west  != NULL) { printf("west ");  }
    if (room->up    != NULL) { printf("up ");    }
    if (room->down  != NULL) { printf("down ");  }
    if (room->in    != NULL) { printf("in ");    }
    if (room->out   != NULL) { printf("out ");   }
    printf("\n");
}

struct Room* initWorld(struct Room* rooms[]) {
    struct Room* parlor;
    struct Room* livingRoom;
    struct Room* hallway;
    struct Room* kitchen;
    struct Room* bedroom;
    struct Room* bathroom;

    parlor = createRoom("Parlor");
    livingRoom = createRoom("Living Room");
    hallway = createRoom("Hallway");
    kitchen = createRoom("Kitchen");
    bedroom = createRoom("Bedroom");
    bathroom = createRoom("Bathroom");

    parlor->west = livingRoom;
    livingRoom->east = parlor;

    livingRoom->north = hallway;
    hallway->south = livingRoom;

    hallway->north = bathroom;
    bathroom->south = hallway;

    hallway->east = bedroom;
    bedroom->west = hallway;

    hallway->west = kitchen;
    kitchen->east = hallway;

    rooms[0] = parlor;
    rooms[1] = livingRoom;
    rooms[2] = hallway;
    rooms[3] = kitchen;
    rooms[4] = bedroom;
    rooms[5] = bathroom;

    return parlor;
}

int main() {
    int i;
    char input[INPUT_LEN];
    struct Room* rooms[6];
    int changedRooms;

    currentRoom = initWorld(rooms);
    printRoom(currentRoom);
    printExits(currentRoom);

    changedRooms = 0;
    while (1) {
        if (changedRooms) {
            printRoom(currentRoom);
            printExits(currentRoom);
        }

        printf("\n> ");
        scanf("%s", input);
        printf("%s\n\n", input);

        if      (strcmp(input, "n") == 0) { changedRooms = travel(DIRECTION_NORTH); }
        else if (strcmp(input, "s") == 0) { changedRooms = travel(DIRECTION_SOUTH); }
        else if (strcmp(input, "e") == 0) { changedRooms = travel(DIRECTION_EAST); }
        else if (strcmp(input, "w") == 0) { changedRooms = travel(DIRECTION_WEST); }
        else if (strcmp(input, "l") == 0) { printRoom(currentRoom); }
        else if (strcmp(input, "exits") == 0) { printExits(currentRoom); }
        else if (strcmp(input, "q") == 0) { break;        }
    }

    for (i = 0; i < 6; i++) {
        free(rooms[i]->name);
        free(rooms[i]);
    }

    return 0;
}