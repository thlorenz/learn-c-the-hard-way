#include <stdio.h>
#include "dbg.h"

#define MAXDATA 100

typedef enum {
  BLUE_EYES,
  GREEN_EYES,
  BROWN_EYES,
  BLACK_EYES,
  OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
  "Blue",
  "Green",
  "Brown",
  "Black",
  "Other"
};

typedef struct {
  int age;
  char first_name[MAXDATA];
  char last_name[MAXDATA];
  EyeColor eyes;
  float income;
} Person;

int main(void) {
  Person you = { .age = 0 };
  int i = 0;
  char *in = NULL;

  // first name
  printf("first name? ");
  in = fgets(you.first_name, MAXDATA - 1, stdin);
  check(in != NULL, "failed to read first name");

  // last name
  printf("last name? ");
  in = fgets(you.last_name, MAXDATA - 1, stdin);
  check(in != NULL, "failed to read last name");

  // age
  printf("age? ");
  int rc = fscanf(stdin, "%d", &you.age);
  check(rc > 0, "failed to read age - needs to be a number");

  // eye color
  printf("eye color:\n");
  for (int i = 0; i<= OTHER_EYES; i++) printf("%d) %s\n", i + 1, EYE_COLOR_NAMES[i]);
  printf("> ");

  int eyes = -1;
  rc = fscanf(stdin, "%d", &eyes);
  check(rc > 0, "failed to read eyes - enter a number");

  you.eyes = eyes - 1;
  check(0 <= you.eyes && you.eyes <= OTHER_EYES, "you picked an invalid option");

  // income
  printf("hourly income? ");
  rc = fscanf(stdin, "%f", &you.income);
  check(rc > 0, "failed to read income - needs to be floating point");

  printf("----- RESULTS -----\n");

  printf("First Name: %s", you.first_name);
  printf("Last Name: %s", you.last_name);
  printf("Age: %d\n", you.age);
  printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
  printf("Income: %f\n", you.income);

  return 0;

error:
  return -1;
}
