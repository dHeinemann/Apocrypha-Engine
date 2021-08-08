#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "limits.h"
#include "npc.h"
#include "room.h"
#include "strfun.h"

void addNpc(struct Room* room, struct Npc* npc)
{
    if (room->npcs == NULL)
    {
        room->npcs = malloc(sizeof(struct Npc) * MAX_NPCS_PER_ROOM);
    }
    room->npcs[room->numberOfNpcs++] = npc;
}

struct Room* createRoom(char* name, char* description)
{
    struct Room* room;
    
    room = malloc(sizeof(struct Room));
    room->name = malloc(ROOM_NAME_MAX_LENGTH);
    room->description = malloc(ROOM_DESCRIPTION_MAX_LENGTH);
    room->npcs = NULL;
    room->numberOfNpcs = 0;

    strcpy(room->name, name);
    strcpy(room->description, description);
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
    for (i = 0; i < room->numberOfNpcs; i++) free(room->npcs[i]);
    free(room->npcs);
    free(room);
}

struct Npc* getNpcByName(char* name, struct Room* room)
{
    int i = 0;
    char* nameToFind;
    char* currentName;
    struct Npc* npc;

    nameToFind = malloc(sizeof(char) * NPC_NAME_MAX_LENGTH);
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