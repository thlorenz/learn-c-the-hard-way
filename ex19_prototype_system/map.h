#ifndef _MAP_H
#define _MAP_H
#include "object.h"
#include "room.h"

struct Map {
  Object proto;
  Room *start;
  Room *location;
};

typedef struct Map Map;

Object MapProto;

#endif
