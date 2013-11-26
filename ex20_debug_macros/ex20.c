#include <stdlib.h>
#include <stdio.h>

#include "../dbg.h"

void test_debug() {
  debug("I have brown hair");
  debug("I am %d years old", 122);
}

void test_log_err() {
  log_err("I believe everything is broken.");
  log_err("There are %d problems in %s", 0, "space");
}

void test_log_warn() {
  log_warn("You can safely ignore this.");
  log_warn("Maybe consider looking at: %s.", "/etc/passwd");
}

void test_log_info() {
  log_info("Well I did something mundane.");
  log_info("It happened %f times today.", 1.3f);
}

int test_check(char *filename) {
    FILE *input = NULL;
    char *block = NULL;

    block = malloc(100);
    check_mem(block); // should work

    input = fopen(filename,"r");
    check(input, "Failed to open %s.", filename);

    free(block);
    fclose(input);
    return 0;

error:
    if(block) free(block);
    if(input) fclose(input);
    return -1;
}

int test_sentinel(int code) {
  char *tmp = malloc(100);
  check_mem(tmp);

  switch(code) {
    case 1:
      log_info("It worked.");
      break;
    default:
      sentinel("I shouldn't run");
  }
  free(tmp);
  return 0;

error:
  if (tmp) free(tmp);
  return -1;
}

int test_check_mem() {
  char *test = NULL;
  check_mem(test);

  free(test);
  return 1;

error:
  return -1;
}

int main(int argc, const char *argv[]) {

  check(argc == 1, "My version doesn't need an argument");

  test_debug();
  test_log_err();
  test_log_warn();
  test_log_info();

  check(test_check("ex20_debug_macros.c") == 0, "failed with ex20_debug_macros.c");
  check(test_check("i_dont_exist.c") == -1, "failed with i_dont_exist.c");

  check(test_sentinel(1) == 0, "test_sentinel failed");
  check(test_sentinel(100) == -1, "test_sentinel failed");

  check(test_check_mem() == -1, "test_check_mem failed");
  return 0;

error:
  return 1;
}
