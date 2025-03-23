#ifndef CAMMINO_HAMILTONIANO_ESISTE_H
#define CAMMINO_HAMILTONIANO_ESISTE_H

#include <stdbool.h>

bool risposta(bool **grafo, int *soluzione, int j, int m);
bool completa(int j, int m);
bool rifiuta(bool **grafo, int *soluzione, int j);
bool accetta(bool **grafo, int *soluzione, int j);
void swap(int *a, int i, int j);
void print_solution(int *soluzione, int j);

#endif
