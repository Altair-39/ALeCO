#include "header/ReginePerEsiste.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
extern int tentativi;


bool soluzione(int regine[], int j, int n) {
    if (!completa(regine, j, n)) {
        if (!rifiuta(regine, j)) {
            bool foundSolution = false;
            int i = 0;
            while (i < n && !foundSolution) {
                regine[j] = i;  // Directly place the queen at column 'i' in row 'j'
                foundSolution = soluzione(regine, j + 1, n);
                i++;
            }
            return foundSolution;
        } else {
            toString(regine, j);
            printf("<-- rifiuta. Tentativo %d\n", ++tentativi);
            return false;
        }
    } else {
        bool accepted = accetta(regine, j);
        if (accepted) {
            toString(regine, j);
            printf("<-- accetta. Tentativo %d\n", ++tentativi);
        } else {
            toString(regine, j);
            printf("<-- rifiuta. Tentativo %d\n", ++tentativi);
        }
        return accepted;
    }
}

bool completa(int regine[], int j, int n) {
    return j == n;
}

bool rifiuta(int regine[], int j) {
    bool rifiuta = false;
    for (int i = 0; i < j - 1 && !rifiuta; i++) {
        rifiuta = regine[j - 1] == regine[i] // same column?
            || abs(regine[j - 1] - regine[i]) == abs((j - 1) - i); // same diagonal?
    }
    return rifiuta && 2 <= j;
}

bool accetta(int regine[], int j) {
    bool accetta = true;
    for (int i = 0; i < j - 1 && accetta; i++) {
        accetta = regine[j - 1] != regine[i] // same column
            && abs(regine[j - 1] - regine[i]) != abs((j - 1) - i); // same diagonal
    }
    return j <= 1 || accetta;
}

void swap(int regine[], int i, int j) {
    int tmp = regine[i];
    regine[i] = regine[j];
    regine[j] = tmp;
}

void toString(int regine[], int j) {
    for (int i = 0; i < j; i++) {
        printf("(%d, %d) ", i, regine[i]);
    }
}

