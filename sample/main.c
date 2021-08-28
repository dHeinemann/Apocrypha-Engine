/*
 * Apocrypha Tech Demo
 * Copyright (C) 2021 David Heinemann
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. GNU General Public License for more
 * details.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/combat.h"
#include "../include/error.h"
#include "../include/limits.h"
#include "../include/npc.h"
#include "../include/room.h"
#include "../include/strfun.h"

/**
 * State of the player character.
 */
static struct Player* player;

/**
 * Print a room's name and description.
 * @param room Room to print.
 */
void printRoom(struct Room* room)
{
    int i;

    for (i = 0; i < (int) strlen(room->name); i++)
        printf("%c", (char) toupper((int) room->name[i]));

    printf("\n");

    printf("%s", room->description);
}

/**
 * Print a list of visible NPCs or monsters in a room.
 * @param room Room to print NPCs for.
 */
void printNpcs(struct Room* room, int showNoNpcsMessage)
{
    int i;
    char* npcName;

    npcName = malloc(NPC_NAME_MAX_LENGTH);

    if (room->numberOfNpcs == 0)
    {
        if (showNoNpcsMessage)
            printf("You don't see anybody here.");
    }
    else if (room->numberOfNpcs == 1)
    {
        printf("%s is here.", firstCharToUpper(npcName, room->npcs[0]->name));
    }
    else
    {
        for (i = 0; i < room->numberOfNpcs; i++)
        {
            if (room->numberOfNpcs > 1 && i == room->numberOfNpcs - 1)
            {
                printf("and ");
            }

            printf(firstCharToUpper(npcName, room->npcs[i]->name));
            if (i == room->numberOfNpcs - 1)
            {
                printf(" are here.");
            }
            else
            {
                printf(", ");
            }
        }
    }

    free(npcName);
}

void printItems(struct Room* room, int showNoItemsMessage)
{
    int i;
    char* itemName;

    itemName = malloc(sizeof(char) * ITEM_NAME_MAX_LENGTH);

    if (room->numberOfItems == 0)
    {
        if (showNoItemsMessage)
            printf("There are no items here.");
    }
    else
    {
        printf("You see ");
        for (i = 0; i < room->numberOfNpcs; i++)
        {
            if (room->numberOfNpcs > 1 && i == room->numberOfNpcs - 1)
            {
                printf("and ");
            }

            printf(firstCharToUpper(itemName, room->items[i]->name));
            if (i == room->numberOfItems - 1)
            {
                printf(".");
            }
            else
            {
                printf(", ");
            }
        }
    }

    free(itemName);
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
}

/**
 * Print the hero's vitals.
 */
void printVitals()
{
    printf("[HP: %i] ", player->hitPoints);
}

/**
 * Create the world.
 * @returns The starting room.
 */
struct Room* initWorld(struct Room* rooms[])
{
    struct Room* shack;
    struct Room* cellar;
    int error;

    shack = createRoom("Abandoned Shack", "You stand inside an abandoned, rundown shack. The windows have been "
        "boarded up from the inside. In the corner is a ladder descending downward.");
    cellar = createRoom("Spooky Cellar", "It is dark here. You are likely to be eaten by a grue.");

    addNpc(shack, createNpc("an orc", 6, 8));
    addItem(shack, createWeapon("copper spear", 0, 1, 6, &error));
    shack->down = cellar;
    cellar->up = shack;

    rooms[0] = shack;
    rooms[1] = cellar;

    if (error != 0)
    {
        printf("Failed to initialize world: %s\n", errorToString(error));
        exit(1);
    }

    return shack;
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

void printRoomDetailed(struct Room* room)
{
    printRoom(room);
    printf(" ");
    printNpcs(room, 0);
    printf("\n");
    printItems(room, 0);
    printf("\n");
    printExits(room);
    printf("\n");
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
            printRoomDetailed(player->room);
            changedRooms = 0;
        }

        printf("\n");
        printVitals();
        printf("> ");
        input = trim(getInput(input));

        if (strcmp(input, "n") == 0 || strcmp(input, "north") == 0)
        {
            changedRooms = travel(player, player->room->north);
        }
        else if (strcmp(input, "s") == 0 || strcmp(input, "south") == 0)
        {
            changedRooms = travel(player, player->room->south);
        }
        else if (strcmp(input, "e") == 0 || strcmp(input, "east") == 0)
        {
            changedRooms = travel(player, player->room->east);
        }
        else if (strcmp(input, "w") == 0 || strcmp(input, "west") == 0)
        {
            changedRooms = travel(player, player->room->west);
        }
        else if (strcmp(input, "u") == 0 || strcmp(input, "up") == 0)
        {
            changedRooms = travel(player, player->room->up);
        }
        else if (strcmp(input, "d") == 0 || strcmp(input, "down") == 0)
        {
            changedRooms = travel(player, player->room->down);
        }
        else if (strcmp(input, "in") == 0 || strcmp(input, "inside") == 0)
        {
            changedRooms = travel(player, player->room->in);
        }
        else if (strcmp(input, "out") == 0 || strcmp(input, "outside") == 0)
        {
            changedRooms = travel(player, player->room->out);
        }
        else if (startsWith(input, "get"))
        {
            token = strtok(input, " "); /* first token will be "get" */
            token = strtok(NULL, " "); /* second token should be item name */
            if (token != NULL && strlen(token) > 0)
            {
                getItem(player, token);
            }
            else
            {
                printf("Get what?\n");
            }
        }
        else if (startsWith(input, "wield") || startsWith(input, "equip"))
        {
            token = strtok(input, " "); /* first token will be "wield" or "equip", etc. */
            token = strtok(NULL, " "); /* second token should be item name */
            if (token != NULL && strlen(token) > 0)
            {
                equipItem(player, token);
            }
            else
            {
                printf("Equip what?\n");
            }
        }
        else if (startsWith(input, "kill"))
        {
            token = strtok(input, " "); /* first token will be "kill" */
            token = strtok(NULL, " ");  /* second token should be target name */
            if (token != NULL && strlen(token) > 0)
            {
                resolveCombat(player, token);
            }
            else
            {
                printf("Kill whom?\n");
            }
        }
        else if (strcmp(input, "l") == 0 || strcmp(input, "look") == 0)
        {
            printRoomDetailed(player->room);
        }
        else if (strcmp(input, "exits") == 0)
        {
            printExits(player->room);
            printf("\n");
        }
        else if (strcmp(input, "mobs") == 0)
        {
            printNpcs(player->room, 1);
            printf("\n");
        }
        else if (strcmp(input, "items") == 0)
        {
            printItems(player->room, 1);
            printf("\n");
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

    player = createPlayer();
    player->room = initWorld(rooms);

    printRoomDetailed(player->room);
    mainLoop();

    for (i = 0; i < 1; i++)
    {
        destroyRoom(rooms[i]);
    }

    destroyPlayer();

    return 0;
}
