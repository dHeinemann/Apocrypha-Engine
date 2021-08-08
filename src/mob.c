#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "limits.h"
#include "mob.h"
#include "strfun.h"

struct Mob* createMob(char* name, int hp, int ac)
{
    struct Mob* mob;
    mob = malloc(sizeof(struct Mob));
    mob->name = name;
    mob->hp = hp;
    mob->ac = ac;
    mob->aggro = 0;

    return mob;
}
