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

/*
 * NPCs and monsters.
 */

#ifndef NPC_H
#define NPC_H

struct Npc
{
    char* name;
    int hitPoints;
    int armorClass;
    int hostile;
};

/*
 * Create a new NPC.
 * @param name NPC's name.
 * @param hitPoints NPC's hit points.
 * @param armorClass NPC's armor class.
 */
struct Npc* createNpc(char* name, int hitPoints, int armorClass);

/*
 * Destroy an NPC.
 */
void destroyNpc(struct Npc* npc);

#endif
