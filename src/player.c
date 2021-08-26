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

#include "limits.h"
#include "player.h"
#include "strfun.h"

struct Player* createPlayer()
{
    struct Player* player;

    player = malloc(sizeof(struct Player));
    player->hitPoints = 6;
    player->armorClass = 12;

    player->equipment = malloc(sizeof(struct EquipmentLoadout));
    player->inventory = malloc(sizeof(struct Item*) * MAX_INVENTORY_SIZE);
    player->itemsInInventory = 0;

    return player;
}

void destroyPlayer(struct Player* player)
{
    int i;

    /* Inventory */
    for (i = 0; i < MAX_INVENTORY_SIZE; i++) free(player->inventory[i]);
    free(player->inventory);

    /* Equipment */
    destroyItem(player->equipment->body);
    destroyItem(player->equipment->offHand);
    destroyItem(player->equipment->mainHand);
    free(player->equipment);

    free(player);
}

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

void getItem(char* name)
{
    int i;
    struct Item* item;

    if (player->itemsInInventory >= MAX_INVENTORY_SIZE)
    {
        printf("You cannot carry any more items.\n");
        return;
    }

    if (strlen(name) <= 2)
    {
        printf("Be more specific.\n");
        return;
    }

    item = getRoomItemByName(name, player->room);
    if (item == NULL)
    {
        printf("You don't see that here.\n");
        return;
    }

    /* Add item to player's inventory. */
    for (i = 0; i < MAX_INVENTORY_SIZE; i++)
    {
        if (player->inventory[i] == NULL)
        {
            player->inventory[i] = item;
            player->itemsInInventory++;
            break;
        }
    }

    /* Remove item from room. */
    for (i = 0; i < ROOM_MAX_ITEMS; i++)
    {
        if (player->room->items[i] == item)
        {
            player->room->items[i] = NULL;
            player->room->numberOfItems--;
        }
    }

    printf("You pick up the %s.", item->name);
}

void equipItem(char* name)
{
    int i;
    struct Item* item;

    if (strlen(name) <= 2)
    {
        printf("Be more specific.\n");
        return;
    }

    item = getInventoryItemByName(name, player);
    if (item == NULL)
    {
        printf("You don't have that.\n");
        return;
    }

    if (item->isWeapon)
    {
        player->equipment->mainHand = item;
    }
    /* todo: armor, shields, etc. */

    /* Remove item from player's inventory. */
    for (i = 0; i < MAX_INVENTORY_SIZE; i++)
    {
        if (player->inventory[i] == item)
        {
            player->inventory[i] = NULL;
            player->itemsInInventory--;
            break;
        }
    }

    printf("You equip the %s.", item->name);
}

int travel(struct Player* player, struct Room* destination)
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
