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

#endif
