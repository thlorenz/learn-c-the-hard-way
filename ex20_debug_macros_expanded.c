#include <stdlib.h>
#include <stdio.h>

void test_debug() {
  fprintf(__stderrp, "DEBUG %s:%d: " "I have brown hair" "\n", "ex20_debug_macros.c", 7, ##);
  fprintf(__stderrp, "DEBUG %s:%d: " "I am %d years old" "\n", "ex20_debug_macros.c", 8, ## 122);
}

void test_log_err() {
  fprintf(__stderrp, "[ERR] (%s:%d: errno: %s) " "I believe everything is broken." "\n", "ex20_debug_macros.c", 12, ((*__error()) == 0 ? "None" : strerror((*__error()))), ##);
  fprintf(__stderrp, "[ERR] (%s:%d: errno: %s) " "There are %d problems in %s" "\n", "ex20_debug_macros.c", 13, ((*__error()) == 0 ? "None" : strerror((*__error()))), ## 0, "space");
}


void test_log_warn() {
  fprintf(__stderrp, "[WARN] (%s:%d: errno: %s) " "You can safely ignore this." "\n", "ex20_debug_macros.c", 17, ((*__error()) == 0 ? "None" : strerror((*__error()))), ##);
  fprintf(__stderrp, "[WARN] (%s:%d: errno: %s) " "Maybe consider looking at: %s." "\n", "ex20_debug_macros.c", 18, ((*__error()) == 0 ? "None" : strerror((*__error()))), ## "/etc/passwd");
}

void test_log_info() {
  fprintf(__stderrp, "[INFO] (%s:%d) " "Well I did something mundane." "\n", "ex20_debug_macros.c", 22, ##);
  fprintf(__stderrp, "[INFO] (%s:%d) " "It happened %f times today." "\n", "ex20_debug_macros.c", 23, ## 1.3f);
}

int test_check(char *filename) {

  FILE *input = ((void *)0);
  char *block = ((void *)0);

  block = malloc(100);
  if(!((block))) {
    fprintf(__stderrp, "[ERR] (%s:%d: errno: %s) " "Out of memory." "\n", "ex20_debug_macros.c", 31, ((*__error()) == 0 ? "None" : strerror((*__error()))), ####); (*__error())=0; goto error;
  }
  // should work

  input = fopen(filename,"r");
  if(!(input)) {
    fprintf(__stderrp, "[ERR] (%s:%d: errno: %s) " "Failed to open %s." "\n", "ex20_debug_macros.c", 34, ((*__error()) == 0 ? "None" : strerror((*__error()))), #### filename); (*__error())=0; goto error;
  }

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
  if(!((tmp))) {
    fprintf(__stderrp, "[ERR] (%s:%d: errno: %s) " "Out of memory." "\n", "ex20_debug_macros.c", 48, ((*__error()) == 0 ? "None" : strerror((*__error()))), ####); (*__error())=0; goto error;
  }
  ;

  switch(code) {
    case 1:
      fprintf(__stderrp, "[INFO] (%s:%d) " "It worked." "\n", "ex20_debug_macros.c", 52, ##);
      break;
    default: {
        fprintf(__stderrp, "[ERR] (%s:%d: errno: %s) " "I shouldn't run" "\n", "ex20_debug_macros.c", 55, ((*__error()) == 0 ? "None" : strerror((*__error()))), ####); (*__error())=0; goto error;
      }
  }

  free(tmp);
  return 0;

error:
  if (tmp) free(tmp);
  return -1;
}

int test_check_mem() {
  char *test = ((void *)0);
  if(!((test))) {
    fprintf(__stderrp, "[ERR] (%s:%d: errno: %s) " "Out of memory." "\n", "ex20_debug_macros.c", 67, ((*__error()) == 0 ? "None" : strerror((*__error()))), ####); (*__error())=0; goto error;
  }
  ;

  free(test);
  return 1;

error:
  return -1;
}

int main(int argc, __const char *argv[]) {
  if(!(argc == 1)) {
    fprintf(__stderrp, "[ERR] (%s:%d: errno: %s) " "My version doesn't need an argument" "\n", "ex20_debug_macros.c", 78, ((*__error()) == 0 ? "None" : strerror((*__error()))), ####); (*__error())=0; goto error;
  }

  test_debug();
  test_log_err();
  test_log_warn();
  test_log_info();

  if(!(test_check("ex20_debug_macros.c") == 0)) {
    fprintf(__stderrp, "[ERR] (%s:%d: errno: %s) " "failed with ex20_debug_macros.c" "\n", "ex20_debug_macros.c", 85, ((*__error()) == 0 ? "None" : strerror((*__error()))), ####); (*__error())=0; goto error;
  }
  if(!(test_check("i_dont_exist.c") == -1)) {
    fprintf(__stderrp, "[ERR] (%s:%d: errno: %s) " "failed with i_dont_exist.c" "\n", "ex20_debug_macros.c", 86, ((*__error()) == 0 ? "None" : strerror((*__error()))), ####); (*__error())=0; goto error;
  }
  if(!(test_sentinel(1) == 0)) {
    fprintf(__stderrp, "[ERR] (%s:%d: errno: %s) " "test_sentinel failed" "\n", "ex20_debug_macros.c", 88, ((*__error()) == 0 ? "None" : strerror((*__error()))), ####); (*__error())=0; goto error;
  }
  if(!(test_sentinel(100) == -1)) {
    fprintf(__stderrp, "[ERR] (%s:%d: errno: %s) " "test_sentinel failed" "\n", "ex20_debug_macros.c", 89, ((*__error()) == 0 ? "None" : strerror((*__error()))), ####); (*__error())=0; goto error;
  }
  if(!(test_check_mem() == -1)) {
    fprintf(__stderrp, "[ERR] (%s:%d: errno: %s) " "test_check_mem failed" "\n", "ex20_debug_macros.c", 91, ((*__error()) == 0 ? "None" : strerror((*__error()))), ####); (*__error())=0; goto error;
  }
  return 0;

error:
  return 1;
}
