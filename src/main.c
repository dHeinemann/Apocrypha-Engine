#include <ctype.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#define INPUT_LEN 20

struct Mob {
    char* name;
    int hp;
};

struct Room {
    char* name;

    struct Mob* mob;

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

struct Player {
    int hp;
    struct Room* room;
};

static struct Player* player;

void playerAttack(struct Mob* mob) {
    const int damage = 2;
    if (mob == NULL) {
        printf("There's nobody there!\n");
        return;
    }

    mob->hp -= damage;
    printf("Your axe hacks into %s!, dealing %i damage!\n", mob->name, damage);
    if (mob->hp <= 0) {
        printf("You have slain %s!\n", mob->name);
    }
}

void mobAttack(struct Mob* mob) {
    if (mob == NULL || mob->hp <= 0) {
        return;
    }

    const int damage = 1;
    player->hp -= damage;
    printf("%s slashes at you violently, dealing %i damage!\n",  mob->name, damage);
}

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

int travel(enum Direction dir) {
    struct Room* destination;

    destination = NULL;
    if (dir == DIRECTION_NORTH) { destination = player->room->north; }
    if (dir == DIRECTION_SOUTH) { destination = player->room->south; }
    if (dir == DIRECTION_EAST)  { destination = player->room->east;  }
    if (dir == DIRECTION_WEST)  { destination = player->room->west;  }
    if (dir == DIRECTION_UP)    { destination = player->room->up;    }
    if (dir == DIRECTION_DOWN)  { destination = player->room->down;  }
    if (dir == DIRECTION_IN)    { destination = player->room->in;    }
    if (dir == DIRECTION_OUT)   { destination = player->room->out;   }

    if (destination != NULL) {
        player->room = destination;
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
    room->mob = NULL;

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

void destroyRoom(struct Room* room) {
    if (room == NULL) {
        return;
    }

    free(room->name);
    free(room->mob);
    free(room);
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

void printMobs(struct Room* room) {
    if (room->mob != NULL) {
        printf("%s is here.\n", room->mob->name);
    }
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

    parlor->mob = malloc(sizeof(struct Mob));
    parlor->mob->name = "The orc";
    parlor->mob->hp = 6;

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

    player = malloc(sizeof(struct Player));
    player->hp = 6;
    player->room = initWorld(rooms);
    printRoom(player->room);
    printMobs(player->room);
    printExits(player->room);

    changedRooms = 0;
    while (1) {
        if (changedRooms) {
            printRoom(player->room);
            printMobs(player->room);
            printExits(player->room);
            changedRooms = 0;
        }

        printf("\n> ");
        scanf("%s", input);
        printf("%s\n\n", input);

        if (strcmp(input, "n") == 0 || strcmp(input, "north") == 0) {
            changedRooms = travel(DIRECTION_NORTH);
        }
        else if (strcmp(input, "s") == 0 || strcmp(input, "south") == 0) {
            changedRooms = travel(DIRECTION_SOUTH);
        }
        else if (strcmp(input, "e") == 0 || strcmp(input, "east") == 0) {
            changedRooms = travel(DIRECTION_EAST);
        }
        else if (strcmp(input, "w") == 0 || strcmp(input, "west") == 0) {
            changedRooms = travel(DIRECTION_WEST);
        }
        else if (strcmp(input, "u") == 0 || strcmp(input, "up") == 0) {
            changedRooms = travel(DIRECTION_UP);
        }
        else if (strcmp(input, "d") == 0 || strcmp(input, "down") == 0) {
            changedRooms = travel(DIRECTION_DOWN);
        }
        else if (strcmp(input, "in") == 0 || strcmp(input, "inside") == 0) {
            changedRooms = travel(DIRECTION_IN);
        }
        else if (strcmp(input, "out") == 0 || strcmp(input, "outside") == 0) {
            changedRooms = travel(DIRECTION_OUT);
        }
        else if (strcmp(input, "kill") == 0) {
            playerAttack(player->room->mob);
            mobAttack(player->room->mob);
        }
        else if (strcmp(input, "l") == 0 || strcmp(input, "look") == 0) {
            printRoom(player->room);
            printExits(player->room);
        }
        else if (strcmp(input, "exits") == 0) {
            printExits(player->room);
        }
        else if (strcmp(input, "q") == 0 || strcmp(input, "quit") == 0) {
            break;
        } else {
            printf("I don't understand what that means.");
        }
    }

    for (i = 0; i < 6; i++) {
        destroyRoom(rooms[i]);
    }

    return 0;
}