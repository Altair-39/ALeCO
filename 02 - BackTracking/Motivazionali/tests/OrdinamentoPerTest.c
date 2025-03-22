#include "../header/OrdinamentoPer.h"
#include <assert.h>
#include <stdio.h>

/* Function to print test separation */
void print_test_separator() { printf("-------------------------\n"); }

void test02() {
  int arr[2] = {2, 1}; /* Array with two elements that need sorting */
  ordinamento(arr, 0, 2);
}

void test03() {
  int arr[4] = {1, 2, 3, 4}; /* Already sorted array */
  ordinamento(arr, 0, 4);
}

void test04() {
  int arr[4] = {2, 1, 4, 3}; /* Array with two pairs of elements out of order */
  ordinamento(arr, 0, 4);
}

void test05() {
  int arr[10] = {32, 3, 2, 4, 1, 3, 5, 6, 7, 2}; /* A larger unsorted array */
  ordinamento(arr, 0, 10);
}

void test06() {
  int arr[4] = {1, 3, 2, 4}; /* Array with two elements out of order */
  ordinamento(arr, 0, 4);
}

int main() {
  /* Run all the tests */
  print_test_separator();
  test02();
  print_test_separator();
  test03();
  print_test_separator();
  test04();
  print_test_separator();
  test05();
  print_test_separator();
  test06();
  print_test_separator();

  return 0;
}
