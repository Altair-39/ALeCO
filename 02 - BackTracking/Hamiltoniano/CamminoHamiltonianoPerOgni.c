#include "header/CamminoHamiltonianoPerOgni.h"
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

void risposte(bool **grafo, int *soluzione, int j, int n) {
    if (!completa(soluzione, j, n)) {
        if (!rifiuta(grafo, soluzione, j)) {
            int i = j;
            while (i < n) {
                swap(soluzione, i, j);
                risposte(grafo, soluzione, j + 1, n);
                swap(soluzione, i, j);
                i++;
            }
        } else {
            printf("Rifiuta: ");
            printSolution(soluzione, j);
        }
    } else {
        if (accetta(grafo, soluzione, j)) {
            printf("Accetta: ");
            printSolution(soluzione, j);
        }
    }
}

bool completa(int *soluzione, int j, int n) {
    return j == n;
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

void swap(int *soluzione, int i, int j) {
    int tmp = soluzione[i];
    soluzione[i] = soluzione[j];
    soluzione[j] = tmp;
}

void printSolution(int *soluzione, int j) {
    for (int i = 0; i < j; i++) {
        printf("%d ", soluzione[i]);
    }
    printf("\n");
}
