#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mob.h"
#include "limits.h"
#include "player.h"
#include "room.h"
#include "strfun.h"

/**
 * State of the player character.
 */
static struct Player* player;

/**
 * Calculate a random number between two values (inclusive).
 * @returns Calculated result.
 */
int getDiceRoll(int min, int max)
{
    return rand() % max + min;
}

/**
 * Resolve the player's attack against a mob.
 * @param mob Mob to attack.
 */
void playerAttack(struct Mob* mob)
{
    int attack;
    int damage;

    if (mob == NULL)
    {
        printf("There's nobody there!\n");
        return;
    }

    mob->aggro = 1;
    attack = getDiceRoll(1, 20);
    if (attack < mob->ac)
    {
        printf("Your attack misses %s!\n", mob->name);
        return;
    }

    damage = getDiceRoll(1, 6);

    mob->hp -= damage;
    printf("Your axe hacks into %s, dealing %i damage!\n", mob->name, damage);
    if (mob->hp + damage > 0 && mob->hp <= 0)
        printf("You have slain %s!\n", mob->name);
}

/**
 * Resolve a mob's attack against the player.
 * @param mob Mob whose attack to resolve.
 */
void mobAttack(struct Mob* mob)
{
    int attack;
    int damage;
    char* mobName;

    if (mob == NULL || mob->hp <= 0)
        return;

    mobName = malloc(MOB_NAME_MAX_LENGTH);
    firstCharToUpper(mob->name, mobName);

    attack = getDiceRoll(1, 20);
    if (attack < player->ac)
    {
        printf("%s misses their attack!\n", mobName);
    }
    else
    {
        damage = getDiceRoll(1, 6);
        player->hp -= damage;
        printf("%s slashes at you violently, dealing %i damage!\n",  mobName, damage);
    }

    free(mobName);
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

    if (player->hp <= 0)
    {
        printf("Oh dear, you are dead!\n");
        exit(0);
    }

    return 1;
}

/**
 * Travel to another room.
 * @param destination Room to travel to.
 * @result True if successful, otherwise False.
 */
int travel(struct Room* destination)
{
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
 * Create the world.
 * @returns The starting room.
 */
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

    addMob(parlor, createMob("an orc", 6, 8));

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

/**
 * Get the player's input.
 * @param buffer Buffer to store input in.
 * @result Pointer to buffer.
 */
char* getInput(char* buffer)
{
    char* input;

    input = malloc(INPUT_LEN);
    fgets(input, INPUT_LEN, stdin);
    input[strcspn(input, "\n")] = 0; /* Remove newline */
    buffer = convertToLower(buffer, input, INPUT_LEN);

    free(input);
    return buffer;
}

void initPlayer()
{
    player = malloc(sizeof(struct Player));
    player->hp = 6;
    player->ac = 12;
}

void mainLoop()
{
    char* input;
    int changedRooms;
    char* token;

    input = malloc(sizeof(char) * INPUT_LEN);
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

        printf("\n");
        printVitals();
        printf("> ");
        input = trim(getInput(input));

        if (strcmp(input, "n") == 0 || strcmp(input, "north") == 0)
        {
            changedRooms = travel(player->room->north);
        }
        else if (strcmp(input, "s") == 0 || strcmp(input, "south") == 0)
        {
            changedRooms = travel(player->room->south);
        }
        else if (strcmp(input, "e") == 0 || strcmp(input, "east") == 0)
        {
            changedRooms = travel(player->room->east);
        }
        else if (strcmp(input, "w") == 0 || strcmp(input, "west") == 0)
        {
            changedRooms = travel(player->room->west);
        }
        else if (strcmp(input, "u") == 0 || strcmp(input, "up") == 0)
        {
            changedRooms = travel(player->room->up);
        }
        else if (strcmp(input, "d") == 0 || strcmp(input, "down") == 0)
        {
            changedRooms = travel(player->room->down);
        }
        else if (strcmp(input, "in") == 0 || strcmp(input, "inside") == 0)
        {
            changedRooms = travel(player->room->in);
        }
        else if (strcmp(input, "out") == 0 || strcmp(input, "outside") == 0)
        {
            changedRooms = travel(player->room->out);
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
}

int main()
{
    int i;
    struct Room* rooms[6];

    srand(time(NULL)); /* Seed RNG */

    initPlayer();
    player->room = initWorld(rooms);

    printRoom(player->room);
    printMobs(player->room);
    printExits(player->room);

    mainLoop();

    for (i = 0; i < 6; i++)
    {
        destroyRoom(rooms[i]);
    }

    return 0;
}
