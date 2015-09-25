#ifndef _object_h
#define _object_h

typedef enum {
    NORTH, SOUTH, EAST, WEST
} Direction;

typedef struct {
    char* description;
    void (*describe)(void *self);
    int (*attack)(void *self, int damage);
    int (*init)(void *self);
    void *(*move)(void *self, Direction direction);
    void (*destroy)(void *self);
} Object;

void *newObject(size_t size, Object proto, char *description);

#define NEW(T, N) newObject(sizeof(T), T##Proto, N)

#endif
