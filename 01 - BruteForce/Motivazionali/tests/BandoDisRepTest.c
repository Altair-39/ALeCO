#include "../header/BandoDisRep.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GenPair area0[4];
GenPair area1[4];
GenPair area2[4];

void setGenPair(GenPair *pair, int first, int second) {
  pair->first = malloc(sizeof(int));
  pair->second = malloc(sizeof(int));

  if (!pair->first || !pair->second) {
    fprintf(stderr, "Memory allocation failed!\n");
    exit(EXIT_FAILURE);
  }

  *(int *)(pair->first) = first;
  *(int *)(pair->second) = second;
}

void initializeAreas() {
  setGenPair(&area0[0], 8, 10);
  setGenPair(&area0[1], 10, 43);
  setGenPair(&area0[2], 20, 51);
  setGenPair(&area0[3], 22, 63);

  setGenPair(&area1[0], 11, 39);
  setGenPair(&area1[1], 21, 12);
  setGenPair(&area1[2], 0, 0);
  setGenPair(&area1[3], 0, 0);

  setGenPair(&area2[0], 8, 27);
  setGenPair(&area2[1], 10, 9);
  setGenPair(&area2[2], 20, 47);
  setGenPair(&area2[3], 0, 0);
}

void freeAreas() {
  for (int i = 0; i < 4; i++) {
    free(area0[i].first);
    free(area0[i].second);
    free(area1[i].first);
    free(area1[i].second);
    free(area2[i].first);
    free(area2[i].second);
  }
}

void testSpazioStati() {
  initializeAreas();
  const size_t numeroAreeIntervento = 3;
  size_t length_a = 4;

  size_t a[length_a];
  for (size_t i = 0; i < length_a; i++)
    a[i] = i;

  size_t disposizione[numeroAreeIntervento];

  printf("-------------- Spazio degli stati \n");
  spazioStati(area0, area1, area2, a, 0, disposizione, numeroAreeIntervento,
              length_a);

  freeAreas();
}

void testSoluzioni() {
  initializeAreas();
  const size_t numeroAreeIntervento = 3;
  size_t length_a = 4;
  size_t length_soluzione = numeroAreeIntervento;

  size_t a[length_a];
  for (size_t i = 0; i < length_a; i++)
    a[i] = i;

  size_t finanziabileTotale = 40;
  size_t soluzione[length_soluzione];

  memset(soluzione, 0, length_soluzione * sizeof(size_t));

  printf("-------------- Soluzioni \n");
  soluzioni(area0, area1, area2, a, length_a, soluzione, length_soluzione,
            finanziabileTotale, 0);

  freeAreas();
}

void testRisposta() {
  initializeAreas();

  const size_t numeroAreeIntervento = 3;
  size_t length_a = 4;
  size_t length_soluzione = numeroAreeIntervento;
  size_t length_risposta = numeroAreeIntervento;

  size_t a[length_a];
  for (size_t i = 0; i < length_a; i++) {
    a[i] = i;
  }

  size_t finanziabileTotale = 40;
  size_t soluzione[length_soluzione];
  size_t r[length_risposta];

  memset(soluzione, 0, length_soluzione * sizeof(size_t));
  memset(r, 0, length_risposta * sizeof(size_t));

  printf("-------------- Risposta \n");

  risposta(area0, area1, area2, a, r, length_risposta, soluzione,
           length_soluzione, finanziabileTotale, 0, length_a, length_a);

  char *result = spazioStatiOut(area0, area1, area2, r, length_soluzione);
  if (result) {
    printf("Risposta %s\n", result);
    free(result);
  }

  freeAreas();
}

int main() {
  testSpazioStati();
  testSoluzioni();
  testRisposta();
  return EXIT_SUCCESS;
}
