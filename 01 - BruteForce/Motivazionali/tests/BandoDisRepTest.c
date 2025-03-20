
#include "../header/BandoDisRep.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/* Global arrays for project areas */
GenPair area0[4];
GenPair area1[4];
GenPair area2[4];

/* Function to allocate and initialize integer values */
void setGenPair(GenPair *pair, int first, int second) {
  pair->first = malloc(sizeof(int));
  pair->second = malloc(sizeof(int));
  
  if (pair->first)
    *(int *)(pair->first) = first;
  if (pair->second)
    *(int *)(pair->second) = second;
}

/* Initialize project areas */
void initializeAreas() {
  /* Area 0 initialization */
  setGenPair(&area0[0], 8, 10);
  setGenPair(&area0[1], 10, 43);
  setGenPair(&area0[2], 20, 51);
  setGenPair(&area0[3], 22, 63);

  /* Area 1 initialization */
  setGenPair(&area1[0], 11, 39);
  setGenPair(&area1[1], 21, 12);
  setGenPair(&area1[2], 0, 0); // Previously (0, INT_MIN)
  setGenPair(&area1[3], 0, 0); // Previously (0, INT_MIN)

  /* Area 2 initialization */
  setGenPair(&area2[0], 8, 27);
  setGenPair(&area2[1], 10, 9);
  setGenPair(&area2[2], 20, 47);
  setGenPair(&area2[3], 0, 0); // Previously (0, INT_MIN)
}

/* Function to free allocated memory */
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

/* Test case for spazioStati */
void testSpazioStati() {
  initializeAreas();
  const size_t numeroAreeIntervento = 3;
  size_t length_a = 4; 

  size_t a[length_a];
  for (size_t i = 0; i < length_a; i++)
    a[i] = i;

  size_t disposizione[numeroAreeIntervento];

  printf("-------------- Spazio degli stati \n");
  spazioStati(area0, area1, area2, a, 0, disposizione, numeroAreeIntervento, length_a);

  freeAreas();
}

/* Test case for soluzioni */
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

  printf("-------------- Soluzioni \n");
  soluzioni(area0, area1, area2, a, length_a, soluzione, length_soluzione, finanziabileTotale, 0);

  freeAreas();
}

/* Test case for risposta */

void testRisposta() {
  initializeAreas();
  
  const size_t numeroAreeIntervento = 3;
  size_t length_a = 4;               // Length of array `a`
  size_t length_soluzione = numeroAreeIntervento;  // Length of the solution array
  size_t length_risposta = numeroAreeIntervento;   // Length of the response array (this is often the same as `length_soluzione` in your case)
  
  size_t a[length_a];
  for (size_t i = 0; i < length_a; i++) {
    a[i] = i;
  }

  size_t finanziabileTotale = 40;
  size_t soluzione[length_soluzione];
  size_t r[length_risposta];  // Response array

  printf("-------------- Risposta \n");

  // Correcting the risposta function call by passing the correct parameters
  risposta(area0, area1, area2, a, r, length_risposta, soluzione, 
           length_soluzione, finanziabileTotale, 0, length_a, length_a);

  char *result = spazioStatiOut(area0, area1, area2, r, length_soluzione);
  if (result) {
    printf("Risposta %s\n", result);
    free(result);
  }

  freeAreas();
}

/* Main function to run tests */
int main() {
  testSpazioStati();
  testSoluzioni();
  testRisposta();
  return 0;
}

