#include <stdio.h>
#include "monster.h"

static int Monster_attack(void *self, int damage) {
  Monster *monster = self;

  printf("You attack %s!\n", monster->proto.description);

  monster->hit_points -= damage;
  if (monster->hit_points > 0) {
    printf("It is still alive.\n");
    return 0;
  } else {
    printf("It is dead!\n");
    return 1;
  }
}

static int Monster_init(void *self) {
  Monster *monster = self;
  monster->hit_points = 10;
  return 1;
}

Object MonsterProto = {
  .init = Monster_init,
  .attack = Monster_attack
};
