#include <stdio.h>

int main(void)
{
  int ages[] = { 23, 43, 12, 89, 2 };
  char *names[] = { "Alan", "Frank", "Mary", "John", "Lisa" };

  int count = sizeof ages / sizeof(int);

  for (int i = 0; i < count; i++)
    printf("%s has been %d years alive.\n", names[i], ages[i]);

  printf("---\n");

  char **names_p = names;
  int *ages_p = ages;

  for (int i = 0; i < count; i++)
    printf("%s has been %d years alive.\n", *(names_p + i), *(ages_p + i));

  printf("---\n");

  for (names_p = names, ages_p = ages; (names_p - names) < count; )
    printf("%s has been %d years alive.\n", *names_p++, *ages_p++);

  return 0;
}
