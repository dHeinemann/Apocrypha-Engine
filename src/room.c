/*
 * Apocrypha, a text adventure game engine
 * Copyright (C) 2021 David Heinemann
 * 
 * This file is part of Apocrypha.
 *
 * Apocrypha is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Apocrypha is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Apocrypha. If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"
#include "limits.h"
#include "npc.h"
#include "room.h"
#include "strfun.h"

void addNpc(struct Room* room, struct Npc* npc)
{
    if (room->npcs == NULL)
    {
        room->npcs = malloc(sizeof(struct Npc) * ROOM_MAX_NPCS);
    }
    room->npcs[room->numberOfNpcs++] = npc;
}

void addItem(struct Room* room, struct Item* item)
{
    if (room->items == NULL)
    {
        room->items = malloc(sizeof(struct Item) * ROOM_MAX_ITEMS);
    }
    room->items[room->numberOfItems++] = item;
}

struct Room* createRoom(char* name, char* description)
{
    struct Room* room;
    
    /* General */
    room = malloc(sizeof(struct Room));

    room->name = malloc(ROOM_NAME_MAX_LENGTH);
    strcpy(room->name, name);
    room->description = malloc(ROOM_DESCRIPTION_MAX_LENGTH);
    strcpy(room->description, description);

    /* NPCs */
    room->npcs = NULL;
    room->numberOfNpcs = 0;

    /* Items */
    room->items = NULL;
    room->numberOfItems = 0;

    /* Travel */
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

void destroyRoom(struct Room* room)
{
    int i;

    if (room == NULL)
        return;

    free(room->name);
    free(room->description);

    for (i = 0; i < room->numberOfNpcs; i++) destroyNpc(room->npcs[i]);
    free(room->npcs);

    for (i = 0; i < room->numberOfItems; i++) destroyItem(room->items[i]);
    free(room->items);

    free(room);
}

struct Npc* getNpcByName(char* name, struct Room* room)
{
    int i = 0;
    char* nameToFind;
    char* currentName;
    struct Npc* npc;

    nameToFind = malloc(sizeof(char) * NPC_NAME_MAX_LENGTH); /* todo: can I declare these without malloc? */
    currentName = malloc(sizeof(char) * NPC_NAME_MAX_LENGTH);

    npc = NULL;
    if (name != NULL)
    {
        nameToFind = convertToLower(nameToFind, name, NPC_NAME_MAX_LENGTH);
        for (i = 0; i < room->numberOfNpcs; i++)
        {
            currentName = convertToLower(currentName, room->npcs[i]->name, NPC_NAME_MAX_LENGTH);
            if (strstr(currentName, nameToFind) != NULL)
            {
                npc = room->npcs[i];
                break;
            }
        }
    }

    free(nameToFind);
    free(currentName);

    return npc;
}

struct Item* getRoomItemByName(char* name, struct Room* room)
{
    int i = 0;
    char* nameToFind;
    char* currentName;
    struct Item* item;

    nameToFind = malloc(sizeof(char) * ITEM_NAME_MAX_LENGTH);
    currentName = malloc(sizeof(char) * ITEM_NAME_MAX_LENGTH);

    item = NULL;
    if (name != NULL)
    {
        nameToFind = convertToLower(nameToFind, name, ITEM_NAME_MAX_LENGTH);
        for (i = 0; i < room->numberOfItems; i++)
        {
            currentName = convertToLower(currentName, room->items[i]->name, ITEM_NAME_MAX_LENGTH);
            if (strstr(currentName, nameToFind) != NULL)
            {
                item = room->items[i];
                break;
            }
        }
    }

    free(nameToFind);
    free(currentName);

    return item;
}
