#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"

void destroyObject(void *self)
{
    Object *obj = self;

    if (obj) {
        if (obj->description) free(obj->description);
        free(obj);
    }
}

void describeObject(void *self)
{
    Object *obj = self;

    printf("%s.\n", obj->description);
}

int initObject(void *self)
{
    return 1;
}

void *moveObject(void *self, Direction direction)
{
    printf("You can't go that direction.\n");
    return NULL;
}

int attackObject(void *self, int damage)
{
    printf("You can't attack that.\n");
    return 0;
}

void *newObject(size_t size, Object proto, char *description)
{
    if (!proto.init) proto.init = initObject;
    if (!proto.attack) proto.attack = attackObject;
    if (!proto.destroy) proto.destroy = destroyObject;
    if (!proto.move) proto.move = moveObject;
    if (!proto.describe) proto.describe = describeObject;

    Object *el = calloc(1, size);
    *el = proto;

    el->description = strdup(description);

    if (!el->init(el)) {
        el->destroy(el);
        return NULL;
    } else {
        return el;
    }
}

