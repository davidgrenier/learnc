#ifndef _ex19_h
#define _ex19_h

#include "object.h"

typedef struct {
    Object proto;
    int hitPoints;
} Monster;

struct Room {
    Object proto;

    Monster *badGuy;

    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
};

typedef struct Room Room;

typedef struct {
    Object proto;
    Room *start;
    Room *location;
} Map;

#endif
