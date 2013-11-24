#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "die.h"

typedef int (*compare_cb)(int a, int b);

int *bubble_sort(int *numbers, int count, compare_cb cmp) {
  int *target = malloc(count * sizeof(int));
  if (!target) die("Memory error");

  memcpy(target, numbers, count * sizeof(int));

  int tmp;
  for(int i = 0; i < count; i++) {
    for(int j = 0; j < count; j++) {
      if (cmp(target[j], target[j + 1]) > 0) {
        tmp = target[j + 1];
        target[j + 1] = target[j];
        target[j] = tmp;
      }
    }
  }
  return target;
}

int ascending(int a, int b) {
  return a - b;
}

int descending(int a, int b) {
  return b - a;
}

int strange(int a, int b) {
  return (a == 0 || b == 0) ? 0 : a % b;
}

void test_sort(int *numbers, int count, compare_cb cmp) {
  int *sorted = bubble_sort(numbers, count, cmp);
  if (!sorted) die("Failed to sort");
  for (int i = 0; i < count; i++) printf("%d ", sorted[i]);
  printf("\n");

  free(sorted);
}

int main(int argc, const char *argv[]) {
  if (argc < 2) die("USAGE ex18_pointers_to_functions n1 n2 .. nx");
  int count = argc - 1;
  const char **inputs = argv + 1;

  int *numbers = malloc(count * sizeof(int));
  if (!numbers) die("Memory error");

  for (int i = 0; i < count; i++) numbers[i] = atoi(inputs[i]);

  test_sort(numbers, count, ascending);
  test_sort(numbers, count, descending);
  test_sort(numbers, count, strange);

  free(numbers);
  return 0;
}
