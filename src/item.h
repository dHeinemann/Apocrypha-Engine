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

/*
 * Items
 */
#ifndef ITEM_H
#define ITEM_H

enum ItemType
{
    ITEM_TYPE_MISC,
    ITEM_TYPE_WEAPON,
    ITEM_TYPE_ARMOR
};

/*
 * Represents a weapon, piece of armor, or other item.
 */
struct Item
{
    char* name;

    enum ItemType itemType;

    /* Weapon details */

    /*
     * Indicates whether this item is a weapon.
     */
    int isWeapon;
    int attackBonus;
    int damageDiceNumber;
    int damageDiceSize;

    /* Armor details */

    /*
     * Indicates whether this item is a piece of armor.
     */
    int isArmor;
    int armorClassBonus;
};

/*
 * Create a general item.
 */
struct Item* createItem(char* name, int* error);

/*
 * Create a weapon.
 */
struct Item* createWeapon(char* name, int attackBonus, int damageDiceNumber, int damageDiceSize, int* error);

/*
 * Create a piece of armor.
 */
struct Item* createArmor(char* name, int armorClassBonus, int* error);

/*
 * Destroy an item.
 */
void destroyItem(struct Item* item);

#endif
