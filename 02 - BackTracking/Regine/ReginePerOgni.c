#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

size_t tentativi = 0;

void toString(int *regine, int j) {
  size_t i = 0;
  while (i < j) {
    printf("(%ld, %d) ", i, regine[i]);
    i++;
  }
}

/* Tutte le regine sono state piazzate.                                    */
bool completa(int regineLength, int j) { return j == regineLength; }

/* Rifiuta a[0..j) se almeno due regine sono piazzate e l'ultima piazzata, cioe'
 * j-1 e' minacciata da qualcuna delle altre regine gia' piazzate, ovvero
 * 0..j-2.
 */
bool rifiuta(int *regine, int j) {
  bool rif = false;
  int i = 0;
  /* Dalla regina 0, sino alla penultima regina piazzata j-2 ... */
  while (i < j - 1 && !rif) {
    rif = regine[j - 1] == regine[i]                 /* stessa colonna? */
          || abs(regine[j - 1] - regine[i]) == abs(j - 1 - i); /* stessa diagonale? */
    i++;
  }
  return rif && 2 <= j;
}

/* Accetta se ci sono almeno due regine piazzate, oppure, essendo almeno due,
 * accetta se l'ultima regina piazzata, cioe' j-1, non e' minacciata da alcuna
 * delle altre gia' piazzate, ovvero 0..j-2.
 */
bool accetta(int *regine, int j, int regineLength) {
  bool acc = true;
  int i = 0;
  while (i < j - 1 && acc) {
    acc =
        regine[j - 1] !=
            regine[i] /* regina i e regina j - 1 sono nella stessa colonna */
        /* i e j-1 sono sulla stessa diagonale se la differenza tra le righe su
         * cui si trovano e' identica alla differenza tra le due loro colonne */
        && abs(regine[j - 1] - regine[i]) != abs(j - 1 - i);
    i++;
  }
  return regineLength <= 1 || acc;
}

void swap(int *regine, int i, int j) {
  int tmp = regine[i];
  regine[i] = regine[j];
  regine[j] = tmp;
}

void soluzioni(int *regine, int j, int regineLength) {
  size_t i = j;
  bool acc;
  if (!completa(regineLength, j)) {
    if (!rifiuta(regine, j)) {
      while (i < regineLength) {
        swap(regine, i, j);
        soluzioni(regine, j + 1, regineLength);
        swap(regine, i, j);
        i++;
      }
    } else {
      //toString(regine, j);
      //printf("<-- rifiuta. Tentativo %ld\n", ++tentativi);
    }
  } else {
    acc = accetta(regine, j, regineLength);
    if (acc) {
            toString(regine, j);
            printf("<-- accetta. Tentativo %ld\n", ++tentativi);
        } else {
        //    toString(regine, j);
        //    printf("<-- rifiuta. Tentativo %ld\n", ++tentativi);
        }
      
  }
}
