#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "limits.h"
#include "mob.h"
#include "room.h"
#include "strfun.h"

void addMob(struct Room* room, struct Mob* mob)
{
    if (room->mobs == NULL)
    {
        room->mobs = malloc(sizeof(struct Mob) * MAX_MOBS_PER_ROOM);
    }
    room->mobs[room->numberOfMobs++] = mob;
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

void destroyRoom(struct Room* room)
{
    if (room == NULL)
        return;

    free(room->name);
    free(room->mobs);
    free(room);
}

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