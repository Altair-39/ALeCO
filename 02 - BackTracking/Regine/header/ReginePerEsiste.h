#ifndef REGINE_H
#define REGINE_H

#include <stdbool.h>
#include <stddef.h>

// Function prototypes
bool soluzione(int regine[], int j, int n);
bool completa(int regine[], int j, int n);
bool rifiuta(int regine[], int j);
bool accetta(int regine[], int j);
void swap(int regine[], int i, int j);
void toString(int regine[], int j);

#endif // REGINE_H
