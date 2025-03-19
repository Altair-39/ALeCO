#include "../header/Permutazioni.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  size_t test1[] = {1, 2};
  printf("Test 1:\n");
  risposte(test1, 0, 2, 2);

  printf("---------------\n");

  size_t test2[] = {1, 2, 3};
  printf("Test 2:\n");
  risposte(test2, 0, 3, 3);

  printf("---------------\n");

  size_t test3[] = {1, 2, 3, 4};
  printf("Test 3:\n");
  risposte(test3, 0, 4, 4);

  return EXIT_SUCCESS;
}
