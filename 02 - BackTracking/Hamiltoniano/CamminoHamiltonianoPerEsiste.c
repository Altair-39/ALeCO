#include "header/CamminoHamiltonianoPerEsiste.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

bool risposta(bool **grafo, int *soluzione, int j, int lengthSoluzione) {
  if (!completa(j, lengthSoluzione)) {
    if (!rifiuta(grafo, soluzione, j)) {
      int i = j;
      bool accetta = false;
      while (i < lengthSoluzione && !accetta) {
        swap(soluzione, i, j);
        accetta = risposta(grafo, soluzione, j + 1, lengthSoluzione);
        swap(soluzione, i, j);
        i++;
      }
      return accetta;
    } else {
      printf(" Rifiuta: ");
      print_solution(soluzione, j);
      return false;
    }
  } else {
    bool acc = accetta(grafo, soluzione, j);
    if (acc) {
      printf(" Accetta: ");
      print_solution(soluzione, j);
    }
    return acc;
  }
}

bool completa(int j, int lengthSoluzione) { return j == lengthSoluzione; }

bool rifiuta(bool **grafo, int *soluzione, int j) {
  bool rifiuta = false;
  if (j > 1) {
    rifiuta = !grafo[soluzione[j - 2]][soluzione[j - 1]];
  }
  return rifiuta;
}

bool accetta(bool **grafo, int *soluzione, int j) {
  bool accetta = true;
  if (j > 1) {
    accetta = grafo[soluzione[j - 2]][soluzione[j - 1]];
  }
  return accetta;
}

void swap(int *a, int i, int j) {
  int tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}

void print_solution(int *soluzione, int j) {
  size_t i = 0;
  while (i < j) {
    printf("%d ", soluzione[i]);
    i++;
  }
  printf("\n");
}
