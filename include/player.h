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

#ifndef PLAYER_H
#define PLAYER_H

#include "item.h"

struct EquipmentLoadout
{
    struct Item* body;
    struct Item* offHand;
    struct Item* mainHand;
};

struct Player
{
    int hitPoints;
    int armorClass;

    struct EquipmentLoadout* equipment;

    struct Item** inventory;
    int itemsInInventory;

    struct Room* room;
};

/**
 * Create a new Player.
 */
struct Player* createPlayer();

/**
 * Destroy a Player.
 */
void destroyPlayer();

/**
 * Get an inventory item by part or whole name.
 */
struct Item* getInventoryItemByName(char* name, struct Player* player);

/**
 * Get an item from the current room.
 * @param name Full or partial name of item to get.
 */
void getItem(struct Player* player, char* name);

/**
 * Equip an item.
 * @param name Full or partial name of item to equip.
 */
void equipItem(struct Player* player, char* name);

/**
 * Travel to another room.
 * @param player Player to move.
 * @param destination Room to travel to.
 * @result True if successful, otherwise False.
 */
int travel(struct Player* player, struct Room* destination);

#endif
