#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ex19.h"

int attackMonster(void *self, int damage)
{
    Monster *monster = self;

    printf("You attack %s!\n", monster->proto.description);

    monster->hitPoints -= damage;

    if (monster->hitPoints > 0) {
        printf("It is still alive.\n");
        return 0;
    } else {
        printf("It is dead!\n");
        return 1;
    }
}

int initMonster(void *self)
{
    Monster *monster = self;
    monster->hitPoints = 10;
    return 1;
}

Object MonsterProto = {
    .init = initMonster,
    .attack = attackMonster
};

void *moveRoom(void *self, Direction direction)
{
    Room *room = self;
    Room *next = NULL;

    if (direction == NORTH && room->north) {
        printf("You go north, into:\n");
        next = room->north;
    } else if (direction == SOUTH && room->south) {
        printf("You go south, into:\n");
        next = room->south;
    } else if (direction == EAST && room->east) {
        printf("You go east, into:\n");
        next = room->east;
    } else if (direction == WEST && room->west) {
        printf("You go west, into:\n");
        next = room->west;
    } else {
        printf("You can't go that direction.\n");
    }

    if (next) {
        next->proto.describe(next);
    }

    return next;
}

int attackRoom(void *self, int damage)
{
    Room *room = self;
    Monster *monster = room->badGuy;

    if (monster) {
        monster->proto.attack(monster, damage);
        return 1;
    } else {
        printf("You flail in the air at nothing. Idiot.\n");
        return 0;
    }
}

Object RoomProto = {
    .move = moveRoom,
    .attack = attackRoom
};

void *moveMap(void *self, Direction direction)
{
    Map *map = self;
    Room *location = map->location;
    Room *next = location->proto.move(location, direction);

    if (next) {
        location = next;
    }
    
    return next;
}

int attackMap(void *self, int damage)
{
    Map *map = self;
    Room *location = map->location;

    return location->proto.attack(location, damage);
}

int initMap(void *self)
{
    Map *map = self;

    Room *hall = NEW(Room, "The great Hall");
    Room *throne = NEW(Room, "The throne room");
    Room *arena = NEW(Room, "The arena, with the minotaur");
    Room *kitchen = NEW(Room, "Kitchen, you have the knife now");


    arena->badGuy = NEW(Monster, "The evil minotaur");

    hall->north = throne;

    throne->west = arena;
    throne->east = kitchen;
    throne->south = hall;

    arena->east = throne;
    kitchen->west = throne;

    map->start = hall;
    map->location = hall;

    return 1;
}

Object MapProto = {
    .move = moveMap,
    .attack = attackMap,
    .init = initMap
};

int processInput(Map *game)
{
    printf("\n>");

    char ch = getchar();
    getchar();

    switch(ch) {
        case -1:
            printf("Giving up? You suck.\n");
            return 0;

        case 'n':
            game->proto.move(game, NORTH);
            break;

        case 's':
            game->proto.move(game, SOUTH);
            break;

        case 'w':
            game->proto.move(game, WEST);
            break;

        case 'e':
            game->proto.move(game, EAST);
            break;

        case 'a':
            game->proto.attack(game, random() % 4);
            break;

        case 'l':
            printf("You can go:\n");

            Room *location = game->location;

            if (location->north) printf("NORTH\n");
            if (location->south) printf("SOUTH\n");
            if (location->west) printf("WEST\n");
            if (location->east) printf("EAST\n");
            break;

        default:
            printf("What: %d\n", ch);
    }

    return 1;
}

int main()
{
   srandom(time(NULL));

   Map *game = NEW(Map, "The Hall of the Minotaur.");

   printf("You enter the ");
   game->location->proto.describe(game->location);

   while (processInput(game)) {}

   return 0;
}
