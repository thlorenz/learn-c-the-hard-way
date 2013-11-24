#include <stdio.h>
#include "monster.h"
#include "room.h"

static void *Room_move(void *self, Direction direction) {
  Room *room = self;
  Room *next;

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
    printf("You can't go that direction.");
    return NULL;
  }

  next->proto.describe(next);

  return next;
}

static int Room_attack(void *self, int damage) {
  Room *room = self;
  Monster *monster = room->bad_guy;

  if (monster) {
    monster->proto.attack(monster, damage);
    return 1;
  } else {
    printf("You flail in the air at nothing. Idiot.\n");
    return 0;
  }
}

Object RoomProto = {
  .move = Room_move,
  .attack = Room_attack
};
