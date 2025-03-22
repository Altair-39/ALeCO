#include "../header/Disposizioni.h"
#include "../header/common.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int test1[] = {1, 2};
  int test2[] = {1, 2, 3};
  int test3[] = {1, 2, 3, 4};
  int *test_cases[] = {test1, test2, test3};
  int test_sizes[] = {2, 3, 4};
  int t = 0, k = 1;

  while (t < sizeof(test_sizes) / sizeof(test_sizes[0])) {
    while (k <= test_sizes[t]) {
      printf("Test with array size %d and k = %d\n", test_sizes[t], k);
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
