#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
  char *name;
  int age;
  int height;
  int weight;
};

struct Person Person_new(char *name, int age, int height, int weight) {
  struct Person who;

  who.name   =  strdup(name);
  who.age    =  age;
  who.height =  height;
  who.weight =  weight;

  // who passed back by value -- would disappear otherwise once we lose scope
  return who;
}

void Person_free(struct Person who) {
  free(who.name);
}

void Person_print(struct Person who) {
  printf("Name: %s\n"     ,  who.name);
  printf("\tAge: %d\n"    ,  who.age);
  printf("\tHeight: %d\n" ,  who.height);
  printf("\tWeight: %d\n" ,  who.weight);
}

int main(void)
{
  struct Person joe   =  Person_new("Joe Alex", 32, 64, 14);
  struct Person frank =  Person_new("Frank Blank", 20, 72, 180);

  printf("Joe is stored at %p\n",(void *)&joe);
  Person_print(joe);

  printf("Frank is stored at %p\n",(void *)&frank);
  Person_print(frank);

  joe.age += 20;
  Person_print(joe);

  frank.age += 10;
  Person_print(frank);

  // don't need to free persons themselves since they'll be gone once we lose scope
  // however we need to free the name (char*) on each
  Person_free(joe);
  Person_free(frank);

  return 0;
}
