#include "../header/Sottoinsiemi.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
  size_t arr1[] = {1, 2};
  size_t arr2[] = {1, 2, 3, 4};

  printf("Sottoinsiemi di {1, 2}:\n");
  sottoinsiemi(arr1, 2);

  printf("---------------\n");

  printf("Sottoinsiemi di {1, 2, 3, 4}:\n");
  sottoinsiemi(arr2, 4);

  return EXIT_SUCCESS;
}
