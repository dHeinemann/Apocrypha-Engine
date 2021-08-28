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
 * Rooms and travel.
 */

#ifndef ROOM_H
#define ROOM_H

struct Room
{
    char* name;
    char* description;

    /* NPCs */
    struct Npc** npcs;
    int numberOfNpcs;

    /* Items */
    struct Item** items;
    int numberOfItems;

    /* Exits */
    struct Room* north;
    struct Room* south;
    struct Room* east;
    struct Room* west;
    struct Room* up;
    struct Room* down;
    struct Room* in;
    struct Room* out;
};

/**
 * Add an NPC to a room.
 * @param room Room to add NPC to.
 * @param npc Npc to add.
 */
void addNpc(struct Room* room, struct Npc* npc);

/**
 * Add an Item to a room.
 * @param room Room to add Item to.
 * @param npc Item to add.
 */
void addItem(struct Room* room, struct Item* item);

/**
 * Create a new room.
 * @param name Name of room.
 * @returns The created room.
 */
struct Room* createRoom(char* name, char* description);

/**
 * Destroy and deallocate a room.
 * @param room Room to destroy.
 */
void destroyRoom(struct Room* room);

/*
 * Get the first mob matching the given name, or NULL if no match was found.
 */
struct Npc* getNpcByName(char* name, struct Room* room);

/*
 * Get the first item matching the given name, or NULL if no match was found.
 */
struct Item* getRoomItemByName(char* name, struct Room* room);

#endif
