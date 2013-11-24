#include <errno.h>

void die(const char *msg) {
  if (errno) perror(msg); else printf("Error: %s\n", msg);
  exit(1);
}
