#ifndef REGINE2_H
#define REGINE2_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

extern size_t tentativi; 

void toString(int *regine, int j);
bool completa(int regineLength, int j);
bool rifiuta(int *regine, int j);
bool accetta(int *regine, int j, int regineLength);
void swap(int *regine, int i, int j);
void soluzioni(int *regine, int j, int regineLength);

#endif // REGINE2_H
