#include "minunit.h"
#include <lcthw/list.h>
#include <assert.h>

static List *list = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";

char *create() {
  list = List_create();
  mu_assert(list != NULL, "Failed to create list.");
  return NULL;
}

char *destroy() {
  List_clear_destroy(list);
  return NULL;
}

char *push_pop() {
  List_push(list, test1);
  mu_assert(List_last(list) == test1, "last pushed is last");
  return NULL;
}

char *all_tests() {
  mu_suite_start();
  mu_run_test(create);
  mu_run_test(push_pop);
  return NULL;
}

RUN_TESTS(all_tests);
