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

#include <stdlib.h>
#include <string.h>

#include "../include/error.h"
#include "../include/item.h"
#include "../include/limits.h"

struct Item* createItem(char* name, int* error)
{
    struct Item* item;

    if (strlen(name) > ITEM_NAME_MAX_LENGTH)
    {
        if (error != NULL)
            *error = ERROR_INVALID_ARGUMENT_LENGTH;

        return NULL;
    }
    
    item = malloc(sizeof(struct Item));
    if (item == NULL)
    {
        if (error != NULL)
            *error = ERROR_OUT_OF_MEMORY;

        return NULL;
    }

    item->name = malloc(sizeof(char) * ITEM_NAME_MAX_LENGTH);
    strncpy(item->name, name, ITEM_NAME_MAX_LENGTH);
    item->isWeapon = 0;
    item->isArmor = 0;

    return item;
}

struct Item* createWeapon(char* name, int attackBonus, int damageDiceNumber, int damageDiceSize, int* error)
{
    struct Item* item;

    item = createItem(name, error);
    if (item == NULL)
    {
        return NULL;
    }

    item->isWeapon = 1;
    item->isArmor = 0;

    item->attackBonus = attackBonus;
    item->damageDiceNumber = damageDiceNumber;
    item->damageDiceSize = damageDiceSize;

    return item;
}

struct Item* createArmor(char* name, int armorClassBonus, int* error)
{
    struct Item* item;

    item = createItem(name, error);
    if (item == NULL)
    {
        return NULL;
    }

    item->isWeapon = 0;
    item->isArmor = 1;

    item->armorClassBonus = armorClassBonus;

    return item;
}

void destroyItem(struct Item* item)
{
    free(item->name);
    free(item);
}
