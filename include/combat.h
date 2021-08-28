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

#ifndef COMBAT_H
#define COMBAT_H

#include "npc.h"
#include "player.h"

/**
 * Calculate a random number between two values (inclusive).
 * @returns Calculated result.
 */
int getDiceRoll(int min, int max);

/**
 * Resolve the player's attack against an NPC.
 * @param player Player who is attacking.
 * @param npc NPC to attack.
 */
void playerAttack(struct Player* player, struct Npc* npc);

/**
 * Resolve a npc's attack against the player.
 * @param npc Npc whose attack to resolve.
 * @param player Player being attacked.
 */
void npcAttack(struct Npc* npc, struct Player* player);

/**
 * Resolve a combat turn.
 * @returns 1 if the turn was resolved, or 0 if there was an error.
 */
int resolveCombat(struct Player* player, char* target);

#endif
