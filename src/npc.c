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

#include "../include/limits.h"
#include "../include/npc.h"
#include "../include/strfun.h"

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

void destroyNpc(struct Npc* npc)
{
    free(npc);
}
