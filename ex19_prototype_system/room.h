#ifndef _ROOM_H
#define _ROOM_H
#include "object.h"
#include "monster.h"

struct Room {
  Object proto;

  Monster *bad_guy;

  struct Room *north;
  struct Room *south;
  struct Room *east;
  struct Room *west;
};

typedef struct Room Room;

Object RoomProto;

#endif
