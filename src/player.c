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
 * along with Apocrypha. If not, see * <https://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <string.h>

#include "limits.h"
#include "player.h"
#include "strfun.h"

struct Item* getInventoryItemByName(char* name, struct Player* player)
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
        for (i = 0; i < player->itemsInInventory; i++)
        {
            currentName = convertToLower(currentName, player->inventory[i]->name, ITEM_NAME_MAX_LENGTH);
            if (strstr(currentName, nameToFind) != NULL)
            {
                item = player->inventory[i];
                break;
            }
        }
    }

    free(nameToFind);
    free(currentName);

    return item;
}
