#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAXDATA 512
#define MAXROWS 100

struct Address {
  int id;
  int set;
  char name[MAXDATA];
  char email[MAXDATA];
};

struct Database {
  struct Address rows[MAXROWS];
};

struct Connection {
  FILE *file;
  struct Database *db;
};

void die(const char *msg) {
  if (errno) perror(msg); else printf("Error: %s\n", msg);
  exit(1);
}

int main(int argc, const char *argv[]) {

  if (argc < 3) die("USAGE: ex17_heap_and_stack <dbfile> <action> [action params]");

  int id = 0;
  const char *filename = argv[1];
  const char action = argv[2][0];

  if (argc > 3) id = atoi(argv[3]);

  if (id >= MAXROWS) die("There are not that many records");
  return 0;
}
