#include "../header/Sottoinsiemi.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  int arr1[] = {1, 2};
  int arr2[] = {1, 2, 3, 4};

  printf("Sottoinsiemi di {1, 2}:\n");
  sottoinsiemi(arr1, 2);

  printf("---------------\n");

  printf("Sottoinsiemi di {1, 2, 3, 4}:\n");
  sottoinsiemi(arr2, 4);

  return EXIT_SUCCESS;
}
