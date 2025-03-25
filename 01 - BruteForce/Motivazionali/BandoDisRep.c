#include "header/BandoDisRep.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

static void swap(size_t *a, size_t i, size_t j) {
  size_t tmp;
  tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}

/* Pubblica una terna di progetti. La singola componente dipende dal livello
 * nella disposizione al quale ci troviamo.
 */

char *spazioStatiOut(GenPair *area0, GenPair *area1, GenPair *area2,
                     size_t *disposizione, size_t length) {
  size_t firstValue, secondValue;

  char *result = (char *)malloc(BUFFER_SIZE);
  if (!result)
    return NULL;

  char buffer[BUFFER_SIZE];
  size_t i = 0;

  strcpy(result, "[");

  while (i < length) {
    switch (i) {
    case 0:
      firstValue = *(int *)area0[disposizione[i]].first;
      secondValue = *(int *)area0[disposizione[i]].second;
      snprintf(buffer, BUFFER_SIZE, "%zu:(%ld,%ld),", disposizione[i],
               firstValue, secondValue);
      break;
    case 1:
      firstValue = *(int *)area1[disposizione[i]].first;
      secondValue = *(int *)area1[disposizione[i]].second;
      snprintf(buffer, BUFFER_SIZE, "%zu:(%ld,%ld),", disposizione[i],
               firstValue, secondValue);
      break;
    case 2:
      firstValue = *(int *)area2[disposizione[i]].first;
      secondValue = *(int *)area2[disposizione[i]].second;
      snprintf(buffer, BUFFER_SIZE, "%zu:(%ld,%ld),", disposizione[i],
               firstValue, secondValue);
      break;
    default:
      continue;
    }
    snprintf(result + strlen(result), BUFFER_SIZE - strlen(result) - 1, "%s",
             buffer);
    i++;
  }

  if (result[strlen(result) - 1] == ',') {
    result[strlen(result) - 1] = '\0';
  }
  strcat(result, "] ");

  return result;
}

/* Elenca terne (x,y,z) di progetti, in cui x e' un progetto dell'area0, y uno
 * dell'area1 e z uno dell'area2. Ipotizzando che ogni area abbia lo stesso
 * numero di progetti, diciamo n, l'elenco e' costruito generando tutte le
 * disposizioni con ripetizione di 3 elementi presi tra gli n disponibili. Ad
 * esempio, la disposizione (1,1,1) individua una terna di progetti formata dal
 * primo progetto di ogni area. Invece, una disposizione (3,1,n) individua una
 * terna composta dal terzo progetto in area0, dal primo in area1 e dall'ultimo,
 * l'n-esimo, in area2.
 */

void spazioStati(GenPair *area0, GenPair *area1, GenPair *area2, size_t *a,
                 size_t j, size_t *disposizione, size_t k, size_t length) {
  size_t i = 0;
  char *spazioS;
  if (j == k) {
    spazioS = spazioStatiOut(area0, area1, area2, disposizione, length);
    if (spazioS) {
      printf("%s", spazioS);
      free(spazioS);
    }
  } else {
    while (i < length) {
      disposizione[j] = a[i];
      swap(a, i, j);
      spazioStati(area0, area1, area2, a, j + 1, disposizione, k, length);
      swap(a, i, j);
      i++;
    }
  }
}

/* Individua una soluzione. Accumula in richiestaTotale la somma delle richieste
 * elencate in soluzione[0..length_soluzione). Se richiestaTotale non eccede
 * finanziabileTotale, allora e' una soluzione valida.
 */
static char *soluzioniOut(GenPair *area0, GenPair *area1, GenPair *area2,
                   size_t *soluzione, size_t finanziabileTotale,
                   size_t length_soluzione) {
  int richiestaTotale = 0;
  size_t i = 0;

  while (i < length_soluzione) {
    if (i == 0) {
      richiestaTotale += *(int *)area0[soluzione[i]].first;
    } else if (i == 1) {
      richiestaTotale += *(int *)area1[soluzione[i]].first;
    } else {
      richiestaTotale += *(int *)area2[soluzione[i]].first;
    }
    i++;
  }

  if (richiestaTotale >= 0 && richiestaTotale <= finanziabileTotale) {
    char *result = (char *)malloc(BUFFER_SIZE);
    if (!result)
      return NULL;

    char *stateString =
        spazioStatiOut(area0, area1, area2, soluzione, length_soluzione);
    if (!stateString) {
      free(result);
      return NULL;
    }

    snprintf(result, BUFFER_SIZE, "%s con richiesta totale %d <= %ld.\n",
             stateString, richiestaTotale, finanziabileTotale);

    free(stateString);
    return result;
  }

  return NULL;
}

/* Genera tutte le combinazioni di "soluzione" (non solo disposizioni con
 * ripetizione). Ogni soluzione è un'istanza di a[0..length_soluzione) che non
 * eccede finanziabileTotale.
 */
void soluzioni(GenPair *area0, GenPair *area1, GenPair *area2, size_t *a,
               size_t length_a, size_t *soluzione, size_t length_soluzione,
               size_t finanziabileTotale, size_t j) {
  size_t i = 0;
  if (j == length_soluzione) {
    char *result = soluzioniOut(area0, area1, area2, soluzione,
                                finanziabileTotale, length_soluzione);
    if (result != NULL) {
      printf("%s", result);
      free(result);
    }
  } else {
    while (i < length_a) {
      soluzione[j] = a[i];
      swap(a, i, j);
      soluzioni(area0, area1, area2, a, length_a, soluzione, length_soluzione,
                finanziabileTotale, j + 1);
      swap(a, i, j);
      i++;
    }
  }
}

/* Individua una risposta migliore */
static char *rispostaOut(GenPair *area0, GenPair *area1, GenPair *area2,
                  size_t finanziabileTotale, size_t *risposta,
                  size_t length_risposta, size_t *soluzione,
                  size_t length_soluzione) {
  size_t richiestaTotale = 0;
  size_t utilitaCorrente = 0;
  size_t utilitaMaxAttuale = 0;
  size_t i = 0;

  /* Ensure soluzione and risposta are initialized */
  if (!soluzione || !risposta)
    return NULL;

  /* Calcola richiestaTotale e utilitaCorrente */
  while (i < length_soluzione) {
    size_t index = soluzione[i];

    /* Validate index */
    if (index >= 4)
      continue;

    /* Ensure pointers are valid before dereferencing */
    if (i == 0 && area0[index].first) {
      richiestaTotale += *(int *)area0[index].first;
    } else if (i == 1 && area1[index].first) {
      richiestaTotale += *(int *)area1[index].first;
    } else if (i == 2 && area2[index].first) {
      richiestaTotale += *(int *)area2[index].first;
    }

    if (i == 0 && area0[index].second) {
      utilitaCorrente += *(int *)area0[index].second;
    } else if (i == 1 && area1[index].second) {
      utilitaCorrente += *(int *)area1[index].second;
    } else if (i == 2 && area2[index].second) {
      utilitaCorrente += *(int *)area2[index].second;
    }
    i++;
  }

  i = 0;

  /* Calcola utilitaMaxAttuale */
  while (i < length_risposta) {
    size_t index = risposta[i];

    /* Validate index */
    if (index >= 4)
      continue;

    /* Ensure pointers are valid before dereferencing */
    if (i == 0 && area0[index].second) {
      utilitaMaxAttuale += *(int *)area0[index].second;
    } else if (i == 1 && area1[index].second) {
      utilitaMaxAttuale += *(int *)area1[index].second;
    } else if (i == 2 && area2[index].second) {
      utilitaMaxAttuale += *(int *)area2[index].second;
    }

    i++;
  }

  i = 0;

  /* Se richiestaTotale non è eccessiva e se utilitaMaxAttuale è inferiore a
   * utilitaCorrente, aggiorna la risposta */
  if (richiestaTotale <= finanziabileTotale &&
      utilitaMaxAttuale < utilitaCorrente) {
    while (i < length_soluzione) {
      risposta[i] = soluzione[i];
      i++;
    }

    // Allocate space for the result
    char *result = (char *)malloc(BUFFER_SIZE);
    if (!result) {
      return NULL; // If malloc fails, return NULL
    }

    // Generate the state string with spazioStatiOut
    char *stateString =
        spazioStatiOut(area0, area1, area2, risposta, length_risposta);
    if (!stateString) {
      free(result);
      return NULL;
    }

    // Format the result string
    snprintf(result, BUFFER_SIZE,
             "%s nuova risposta con richiesta totale %ld <= %ld e utilità "
             "totale %ld.\n",
             stateString, richiestaTotale, finanziabileTotale, utilitaCorrente);

    free(stateString); // Free the memory allocated for stateString
    return result;
  }

  return NULL; // Return NULL if no improvement was found
}

/* Genera e verifica risposte migliori */
void risposta(GenPair *area0, GenPair *area1, GenPair *area2, size_t *a,
              size_t *r, size_t length_risposta, size_t *soluzione,
              size_t length_soluzione, size_t finanziabileTotale, size_t j,
              size_t k, size_t length) {
  size_t i = 0;
  if (j == k) {
    char *result = rispostaOut(area0, area1, area2, finanziabileTotale, r,
                               length_risposta, soluzione, length_soluzione);
    if (result) {
      printf("%s", result);
      free(result);
    }
  } else {
    while (i < length) {
      soluzione[j] = a[i];
      swap(a, i, j);
      risposta(area0, area1, area2, a, r, length_risposta, soluzione,
               length_soluzione, finanziabileTotale, j + 1, k, length);
      swap(a, i, j);
      i++;
    }
  }
}
