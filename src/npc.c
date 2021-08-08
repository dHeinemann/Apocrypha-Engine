#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "limits.h"
#include "npc.h"
#include "strfun.h"

struct Npc* createNpc(char* name, int hitPoints, int armorClass)
{
    struct Npc* npc;
    npc = malloc(sizeof(struct Npc));
    npc->name = name;
    npc->hitPoints = hitPoints;
    npc->armorClass = armorClass;
    npc->hostile = 0;

    return npc;
}
