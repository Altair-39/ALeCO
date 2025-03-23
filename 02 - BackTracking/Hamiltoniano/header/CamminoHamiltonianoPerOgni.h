#ifndef CAMMINO_HAMILTONIANO_OGNI_H
#define CAMMINO_HAMILTONIANO_OGNI_H

#include <stdbool.h>

void risposte(bool **grafo, int *soluzione, int j, int n);
bool completa(int *soluzione, int j, int n);
bool rifiuta(bool **grafo, int *soluzione, int j);
bool accetta(bool **grafo, int *soluzione, int j);
void swap(int *soluzione, int i, int j);
void printSolution(int *soluzione, int j);

#endif
