#ifndef _MONSTER_H
#define _MONSTER_H
#include "object.h"

struct Monster {
  Object proto;
  int hit_points;
};

typedef struct Monster Monster;

Object MonsterProto;

#endif
