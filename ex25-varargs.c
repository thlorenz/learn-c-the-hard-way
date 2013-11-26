#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include "dbg.h"

#define MAXDATA 100

int read_string(char **outs, int maxbuffer) {
  *outs = calloc(1, maxbuffer + 1);
  check_mem(*outs);

  char *res = fgets(*outs, maxbuffer, stdin);
  check(res != NULL, "input error");

  return 0;

error:
  if (*outs) free(*outs);
  *outs = NULL;
  return -1;
}

int read_int(int *outi) {
  char *inp = NULL;
  int rc = read_string(&inp, MAXDATA);
  check(rc == 0, "failed to read number");

  *outi = atoi(inp);
  free(inp);
  return 0;

error:
  if (inp) free(inp);
  return -1;
}

int read_scan(const char *fmt, ...) {
  int maxbuffer, rc;
  int *ip;
  char *cp;
  char **sp;
  va_list argp;

  va_start(argp, fmt);
  for(int i = 0; fmt[i] != '\0'; i++) {
    if (fmt[i] == '%') {
      i++;
      switch(fmt[i]) {
        case 'd':
          ip = va_arg(argp, int *);
          rc = read_int(ip);
          check(rc == 0, "failed to read int");
          break;

        case 'c':
          cp = va_arg(argp, char *);
          *cp = fgetc(stdin);
          break;

        case 's':
          maxbuffer = va_arg(argp, int);
          sp = va_arg(argp, char **);
          rc = read_string(sp, maxbuffer);
          check(rc == 0, "failed to read string");
          break;

        case '\0':
          sentinel("invalid format, ended with %%");
          break;

        default:
          sentinel("invalid format");
          break;
      }
    } else {
      // eat up remaining input
      fgetc(stdin);
    }

    check(!feof(stdin) && !ferror(stdin), "input error");
  }

  va_end(argp);
  return 0;
error:
  va_end(argp);
  return -1;
}

int main(void) {
  char *first_name = NULL;
  char initial = ' ';
  char *last_name = NULL;
  int age = 0;

  printf("What's your first name? ");
  int rc = read_scan("%s", MAXDATA, &first_name);
  check(rc == 0, "Failed first name.");

  printf("What's your initial? ");
  rc = read_scan("%c\n", &initial);
  check(rc == 0, "Failed initial.");

  printf("What's your last name? ");
  rc = read_scan("%s", MAXDATA, &last_name);
  check(rc == 0, "Failed last name.");

  printf("How old are you? ");
  rc = read_scan("%d", &age);

  printf("---- RESULTS ----\n");
  printf("First Name: %s", first_name);
  printf("Initial: '%c'\n", initial);
  printf("Last Name: %s", last_name);
  printf("Age: %d\n", age);

  free(first_name);
  free(last_name);

  return 0;

error:
  return -1;
}
