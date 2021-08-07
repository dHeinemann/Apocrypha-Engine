#include <ctype.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#define INPUT_LEN 20
#define MOB_NAME_MAX_LENGTH 10
#define MAX_MOBS_PER_ROOM 10

struct Mob
{
    char* name;
    int hp;
    int aggro;
};

struct Room
{
    char* name;

    struct Mob** mobs;
    int numberOfMobs;

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

struct Player
{
    int hp;
    struct Room* room;
};

static struct Player* player;

void addMob(struct Room* room, struct Mob* mob)
{
    if (room->mobs == NULL)
    {
        room->mobs = malloc(sizeof(struct Mob) * MAX_MOBS_PER_ROOM);
    }
    room->mobs[room->numberOfMobs++] = mob;
}

char* convertToLower(char* destination, char* source, int num)
{
    int i;

    strncpy(destination, source, num);
    for (i = 0; i < (int) strlen(destination); i++)
    {
        if (isupper(destination[i]))
        {
            destination[i] = tolower(destination[i]);
        }
    }

    return destination;
}


/*
 * Get the first mob matching the given name, or NULL if no match was found.
 */
struct Mob* getMobByName(char* name, struct Room* room)
{
    int i = 0;
    char* nameToFind;
    char* currentName;
    struct Mob* mob;

    nameToFind = malloc(sizeof(char) * MOB_NAME_MAX_LENGTH);
    currentName = malloc(sizeof(char) * MOB_NAME_MAX_LENGTH);

    mob = NULL;
    if (name != NULL)
    {
        nameToFind = convertToLower(nameToFind, name, MOB_NAME_MAX_LENGTH);
        for (i = 0; i < room->numberOfMobs; i++)
        {
            currentName = convertToLower(currentName, room->mobs[i]->name, MOB_NAME_MAX_LENGTH);
            if (strstr(currentName, nameToFind) != NULL)
            {
                mob = room->mobs[i];
                break;
            }
        }
    }

    free(nameToFind);
    free(currentName);

    return mob;
}

void playerAttack(struct Mob* mob)
{
    const int damage = 2;

    if (mob == NULL)
    {
        printf("There's nobody there!\n");
        return;
    }

    mob->hp -= damage;
    mob->aggro = 1;
    printf("Your axe hacks into %s, dealing %i damage!\n", mob->name, damage);
    if (mob->hp + damage > 0 && mob->hp <= 0)
    {
        printf("You have slain %s!\n", mob->name);
    }
}

void mobAttack(struct Mob* mob)
{
    if (mob == NULL || mob->hp <= 0)
    {
        return;
    }

    const int damage = 1;
    player->hp -= damage;
    printf("%s slashes at you violently, dealing %i damage!\n",  mob->name, damage);
}

/**
 * Resolve a combat turn.
 * @returns 1 if the turn was resolved, or 0 if there was an error.
 */
int resolveCombat(char* target)
{
    int i;
    struct Mob* targetMob;
    struct Mob* currentMob;

    if (player->room->numberOfMobs == 0)
    {
        if (target != NULL)
        {
            printf("There's nobody here to fight.\n");
        }
        return 1;
    }

    if (strlen(target) <= 2)
    {
        printf("Be more specific. Lives are at stake here!\n");
        return 0;
    }

    targetMob = getMobByName(target, player->room);
    playerAttack(targetMob);

    for (i = 0; i < player->room->numberOfMobs; i++)
    {
        currentMob = player->room->mobs[i];
        if (currentMob->hp > 0 && currentMob->aggro)
        {
            mobAttack(currentMob);
        }
    }

    return 1;
}

enum Direction
{
    DIRECTION_NORTH,
    DIRECTION_SOUTH,
    DIRECTION_EAST,
    DIRECTION_WEST,
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_IN,
    DIRECTION_OUT
};

int travel(enum Direction dir)
{
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

    if (destination != NULL)
    {
        player->room = destination;
        return 1;
    }
    else
    {
        printf("There is no exit in that direction.\n");
        return 0;
    }
}

struct Room* createRoom(char* name)
{
    struct Room* room;
    
    room = malloc(sizeof(struct Room));
    room->name = malloc(30);
    room->mobs = NULL;

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

struct Mob* createMob(char* name, int hp)
{
    struct Mob* mob;
    mob = malloc(sizeof(struct Mob));
    mob->name = name;
    mob->hp = hp;
    mob->aggro = 0;

    return mob;
}

void destroyRoom(struct Room* room)
{
    if (room == NULL)
        return;

    free(room->name);
    free(room->mobs);
    free(room);
}

/**
 * Print a room's name and description.
 * @param room Room to print.
 */
void printRoom(struct Room* room)
{
    int i;

    i = 0;
    while (room->name[i])
    {
        printf("%c", (char) toupper((int) room->name[i]));
        i++;
    }
    printf("\n");
}

/**
 * Print a list of visible NPCs or monsters in a room.
 * @param room Room to print mobs for.
 */
void printMobs(struct Room* room)
{
    int i;

    if (room->numberOfMobs == 1)
    {
        printf("%s is here.\n", room->mobs[0]->name);
    }
    else
    {
        for (i = 0; i < room->numberOfMobs; i++)
        {
            if (room->numberOfMobs > 1 && i == room->numberOfMobs - 1)
            {
                printf("and ");
            }

            printf(room->mobs[i]->name);
            if (i == room->numberOfMobs - 1)
            {
                printf(" are here.\n");
            }
            else
            {
                printf(", ");
            }
        }
    }
}

/**
 * Print a list of visible exits from a room.
 * @params room Room to print exits for.
 */
void printExits(struct Room* room)
{
    int numExits = 0;
    printf("Exits: ");
    if (room->north != NULL) { if (numExits) { printf(", "); } printf("north"); numExits++; }
    if (room->south != NULL) { if (numExits) { printf(", "); } printf("south"); numExits++; }
    if (room->east  != NULL) { if (numExits) { printf(", "); } printf("east");  numExits++; }
    if (room->west  != NULL) { if (numExits) { printf(", "); } printf("west");  numExits++; }
    if (room->up    != NULL) { if (numExits) { printf(", "); } printf("up");    numExits++; }
    if (room->down  != NULL) { if (numExits) { printf(", "); } printf("down");  numExits++; }
    if (room->in    != NULL) { if (numExits) { printf(", "); } printf("in");    numExits++; }
    if (room->out   != NULL) { if (numExits) { printf(", "); } printf("out");   numExits++; }
    printf("\n");
}

/**
 * Print the hero's vitals.
 */
void printVitals()
{
    printf("[HP: %i] ", player->hp);
}

/**
 * Trim whitespace surrounding a string.
 * @param str String to trim.
 */
char* trim(char* str)
{
    int i;

    /* Trim start */
    for (i = 0; (size_t) i < strlen(str); i++)
    {
        if (!isspace(str[i]))
            break;
        str++;
    }

    /* Trim end */
    for (i = (int) strlen(str) - 1; i >= 0; i--)
    {
        if (!isspace(str[i]))
            break;
        str[i] = '\0';
    }

    return str;
}

struct Room* initWorld(struct Room* rooms[])
{
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

    addMob(parlor, createMob("an orc", 6));

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

int startsWith(char* string, char* target)
{
    return strncmp(string, target, strlen(target)) == 0;
}

char* getInput(char* buffer)
{
    fgets(buffer, INPUT_LEN, stdin);
    buffer[strcspn(buffer, "\n")] = 0; /* Remove newline */
    buffer = convertToLower(buffer, buffer, INPUT_LEN);

    return buffer;
}

int main()
{
    int i;
    char* input;
    struct Room* rooms[6];
    int changedRooms;
    char* token;

    input = malloc(sizeof(char) * INPUT_LEN);

    player = malloc(sizeof(struct Player));
    player->hp = 6;
    player->room = initWorld(rooms);
    printRoom(player->room);
    printMobs(player->room);
    printExits(player->room);

    changedRooms = 0;
    while (1)
    {
        if (changedRooms)
        {
            printRoom(player->room);
            printMobs(player->room);
            printExits(player->room);
            changedRooms = 0;
        }

        printVitals();
        printf("> ");
        input = trim(getInput(input));
        printf("%s\n\n", input);

        if (strcmp(input, "n") == 0 || strcmp(input, "north") == 0)
        {
            changedRooms = travel(DIRECTION_NORTH);
        }
        else if (strcmp(input, "s") == 0 || strcmp(input, "south") == 0)
        {
            changedRooms = travel(DIRECTION_SOUTH);
        }
        else if (strcmp(input, "e") == 0 || strcmp(input, "east") == 0)
        {
            changedRooms = travel(DIRECTION_EAST);
        }
        else if (strcmp(input, "w") == 0 || strcmp(input, "west") == 0)
        {
            changedRooms = travel(DIRECTION_WEST);
        }
        else if (strcmp(input, "u") == 0 || strcmp(input, "up") == 0)
        {
            changedRooms = travel(DIRECTION_UP);
        }
        else if (strcmp(input, "d") == 0 || strcmp(input, "down") == 0)
        {
            changedRooms = travel(DIRECTION_DOWN);
        }
        else if (strcmp(input, "in") == 0 || strcmp(input, "inside") == 0)
        {
            changedRooms = travel(DIRECTION_IN);
        }
        else if (strcmp(input, "out") == 0 || strcmp(input, "outside") == 0)
        {
            changedRooms = travel(DIRECTION_OUT);
        }
        else if (startsWith(input, "kill"))
        {
            token = strtok(input, " "); /* first token will be "kill" */
            token = strtok(NULL, " ");  /* second token should be target name */
            if (token != NULL && strlen(token) > 0)
            {
                resolveCombat(token);
            }
            else
            {
                printf("Kill whom?\n");
            }
        }
        else if (strcmp(input, "l") == 0 || strcmp(input, "look") == 0)
        {
            printRoom(player->room);
            printExits(player->room);
        }
        else if (strcmp(input, "exits") == 0)
        {
            printExits(player->room);
        }
        else if (strcmp(input, "q") == 0 || strcmp(input, "quit") == 0)
        {
            break;
        }
        else
        {
            printf("I don't understand what that means.\n");
        }
    }

    free(input);
    for (i = 0; i < 6; i++)
    {
        destroyRoom(rooms[i]);
    }

    return 0;
}