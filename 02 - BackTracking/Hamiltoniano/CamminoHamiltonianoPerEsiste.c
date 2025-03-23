#include "header/CamminoHamiltonianoPerEsiste.h"
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

bool risposta(bool **grafo, int *soluzione, int j, int m) {
    if (!completa(j, m)) {
        if (!rifiuta(grafo, soluzione, j)) {
            int i = j;
            bool accetta = false;
            while (i < m && !accetta) {
                swap(soluzione, i, j);
                accetta = risposta(grafo, soluzione, j + 1, m);
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

bool completa(int j, int m) {
    return j == m;
}

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
  while (i < j ) {
        printf("%d ", soluzione[i]);
  i++; 
  }
    printf("\n");
}
