#include "object.h"
#include "map.h"
#include "room.h"
#include "monster.h"

static void *Map_move(void *self, Direction direction) {
  Map *map = self;
  Room *location = map->location;
  Room *next = location->proto.move(location, direction);
  if (next) map->location = next;
  return next;
}

static int Map_attack(void *self, int damage) {
  Map *map = self;
  Room *location = map->location;
  return location->proto.attack(location, damage);
}

static int Map_init(void *self) {
  Map *map = self;

  Room *hall = NEW(Room, "The great Hall");
  Room *throne = NEW(Room, "The throne room");
  Room *arena = NEW(Room, "The arena, with the minotaur");
  Room *kitchen = NEW(Room, "Kitchen, you have the knife now");

  arena->bad_guy = NEW(Monster, "The evil minotaur");

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
  .init = Map_init,
  .move = Map_move,
  .attack = Map_attack
};
