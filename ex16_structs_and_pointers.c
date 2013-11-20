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

struct Person *Person_new(char *name, int age, int height, int weight) {
  struct Person *who = malloc(sizeof(struct Person));
  assert(who != NULL);

  who->name   =  strdup(name);
  who->age    =  age;
  who->height =  height;
  who->weight =  weight;

  return who;
}

void Person_free(struct Person *who) {
  assert(who != NULL);
  free(who->name);
  free(who);
}

void Person_print(struct Person *who) {
  printf("Name: %s\n"     ,  who->name);
  printf("\tAge: %d\n"    ,  who->age);
  printf("\tHeight: %d\n" ,  who->height);
  printf("\tWeight: %d\n" ,  who->weight);
}

int main(void)
{
  struct Person *joe   =  Person_new("Joe Alex", 32, 64, 14);
  struct Person *frank =  Person_new("Frank Blank", 20, 72, 180);

  printf("Joe is stored at %p\n", joe);
  Person_print(joe);

  printf("Frank is stored at %p\n", frank);
  Person_print(frank);

  joe->age += 20;
  Person_print(joe);

  frank->age += 10;
  Person_print(frank);

  Person_free(joe);
  Person_free(frank);

  return 0;
}
