/*
 * Rooms and travel.
 */

#ifndef ROOM_H
#define ROOM_H

struct Room
{
    char* name;

    struct Npc** mobs;
    int numberOfMobs;

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
 * Add a mob to a room.
 * @param room Room to add mob to.
 * @param mob Npc to add.
 */
void addMob(struct Room* room, struct Npc* mob);

/**
 * Create a new room.
 * @param name Name of room.
 * @returns The created room.
 */
struct Room* createRoom(char* name);

/**
 * Destroy and deallocate a room.
 * @param room Room to destroy.
 */
void destroyRoom(struct Room* room);

/*
 * Get the first mob matching the given name, or NULL if no match was found.
 */
struct Npc* getMobByName(char* name, struct Room* room);

#endif
