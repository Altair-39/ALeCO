#include "../header/Disposizioni.h"
#include "../header/common.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  size_t test1[] = {1, 2};
  size_t test2[] = {1, 2, 3};
  size_t test3[] = {1, 2, 3, 4};
  size_t *test_cases[] = {test1, test2, test3};
  size_t test_sizes[] = {2, 3, 4};

  for (size_t t = 0; t < sizeof(test_sizes) / sizeof(test_sizes[0]); t++) {
    for (size_t k = 1; k <= test_sizes[t]; k++) {
      printf("Test with array size %zu and k = %zu\n", test_sizes[t], k);
      print_array(test_cases[t], test_sizes[t]);
      risposte(test_cases[t], 0, k, test_sizes[t]);
      printf("After risposte:\n");
      print_array(test_cases[t], test_sizes[t]);
      printf("---------------\n");
      count = 0;
    }
  }
  return EXIT_SUCCESS;
}
