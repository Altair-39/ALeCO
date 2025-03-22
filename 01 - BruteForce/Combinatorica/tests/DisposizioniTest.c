#include "../header/Disposizioni.h"
#include "../header/common.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  size_t test1[] = {1, 2};
  size_t test2[] = {1, 2, 3};
  size_t test3[] = {1, 2, 3, 4};
  size_t *test_cases[] = {test1, test2, test3};
  size_t test_sizes[] = {2, 3, 4};
  size_t t = 0, k = 1;

  while (t < sizeof(test_sizes) / sizeof(test_sizes[0])) {
    while (k <= test_sizes[t]) {
      printf("Test with array size %zu and k = %zu\n", test_sizes[t], k);
      print_array(test_cases[t], test_sizes[t]);
      risposte(test_cases[t], 0, k, test_sizes[t]);
      printf("After risposte:\n");
      print_array(test_cases[t], test_sizes[t]);
      printf("---------------\n");
      count = 0;
      k++;
    }
    t++;
  }
  return EXIT_SUCCESS;
}
