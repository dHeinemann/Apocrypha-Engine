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
#include "player.h"
#include "room.h"
#include "strfun.h"

int getDiceRoll(int min, int max)
{
    return rand() % max + min;
}

void playerAttack(struct Player* player, struct Npc* npc)
{
    int attack;
    int damage;
    struct Item* weapon;
    int needToFreeWeapon;

    if (npc == NULL)
    {
        printf("There's nobody there!\n");
        return;
    }

    needToFreeWeapon = 0;
    weapon = player->equipment->mainHand;
    if (weapon == NULL)
    {
        needToFreeWeapon = 1;
        weapon = createWeapon("fists", 0, 1, 4, NULL);
    }

    npc->hostile = 1;
    attack = getDiceRoll(1, 20);
    if (attack < npc->armorClass)
    {
        printf("Your attack misses %s!\n", npc->name);
        return;
    }

    damage = getDiceRoll(weapon->damageDiceNumber, weapon->damageDiceSize);

    npc->hitPoints -= damage;
    printf("Your %s wounds %s, dealing %i damage!\n", weapon->name, npc->name, damage);
    if (npc->hitPoints + damage > 0 && npc->hitPoints <= 0)
        printf("You have slain %s!\n", npc->name);

    if (needToFreeWeapon)
        destroyItem(weapon);
}

void npcAttack(struct Npc* npc, struct Player* player)
{
    int attack;
    int damage;
    char* npcName;

    if (npc == NULL || npc->hitPoints <= 0)
        return;

    npcName = malloc(NPC_NAME_MAX_LENGTH);
    firstCharToUpper(npcName, npc->name);

    attack = getDiceRoll(1, 20);
    if (attack < player->armorClass)
    {
        printf("%s misses their attack!\n", npcName);
    }
    else
    {
        damage = getDiceRoll(1, 6);
        player->hitPoints -= damage;
        printf("%s slashes at you violently, dealing %i damage!\n",  npcName, damage);
    }

    free(npcName);
}

int resolveCombat(struct Player* player, char* target)
{
    int i;
    struct Npc* targetNpc;
    struct Npc* currentNpc;

    if (player->room->numberOfNpcs == 0)
    {
        if (target != NULL)
        {
            printf("There's nobody here to fight.\n");
        }
        return 1;
    }

    if (strlen(target) <= 2)
    {
        printf("Be more specific.\n");
        return 0;
    }

    targetNpc = getNpcByName(target, player->room);
    playerAttack(player, targetNpc);

    for (i = 0; i < player->room->numberOfNpcs; i++)
    {
        currentNpc = player->room->npcs[i];
        if (currentNpc->hitPoints > 0 && currentNpc->hostile)
        {
            npcAttack(currentNpc, player);
        }
    }

    if (player->hitPoints <= 0)
    {
        printf("Oh dear, you are dead!\n");
        exit(0);
    }

    return 1;
}
