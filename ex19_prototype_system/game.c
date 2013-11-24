#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "object.h"
#include "map.h"
#include "room.h"
#include "monster.h"

static int process_input(Map *game) {
  printf("\n> ");

  char ch = getchar();
  getchar(); // Enter

  int damage = rand() % 4;

  switch(ch) {
    case 'q':
      printf("Giving up? You suck.\n");
      return 0;
      break;

    case 'n':
      game->proto.move(game, NORTH);
      break;
    case 's':
      game->proto.move(game, SOUTH);
      break;
    case 'e':
      game->proto.move(game, EAST);
      break;
    case 'w':
      game->proto.move(game, WEST);
      break;

    case 'a':
      game->proto.attack(game, damage);
      break;

    case 'l':
      printf("You can go:\n");
      if (game->location->north) printf("North\n");
      if (game->location->south) printf("South\n");
      if (game->location->east) printf("East\n");
      if (game->location->west) printf("West\n");
      break;

    default:
      printf("What?: %d", ch);
  }

  return 1;
}

int main(void) {
  srand(time(NULL));

  Map *game = NEW(Map, "The Hall of the Minotaur.");

  printf("You enter the ");
  game->location->proto.describe(game->location);

  while(process_input(game)) ;

  return 0;
}
