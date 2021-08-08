/*
 * NPCs and monsters.
 */

#ifndef MOB_H
#define MOB_H

struct Mob
{
    char* name;
    int hp;
    int ac;
    int aggro;
};

/*
 * Create a new mob.
 * @param name Mob's name.
 * @param hp Mob's hit points.
 * @param ac Mob's armor class.
 */
struct Mob* createMob(char* name, int hp, int ac);

#endif
