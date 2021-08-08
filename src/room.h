/*
 * Rooms and travel.
 */

#ifndef ROOM_H
#define ROOM_H

struct Room
{
    char* name;
    char* description;

    struct Npc** npcs;
    int numberOfNpcs;

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

#endif
