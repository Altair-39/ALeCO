#ifndef HEADER_H
#define HEADER_H

#include <stddef.h>

struct GenPair {
  void *first;
  void *second;
};

void swap(size_t *a, size_t i, size_t j);

void print_array(size_t *array, size_t length);

char *toString(size_t *a, int k);

#endif // !HEADER_H
