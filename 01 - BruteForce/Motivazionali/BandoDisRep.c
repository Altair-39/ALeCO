#include "header/BandoDisRep.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void swap(size_t *a, size_t i, size_t j) {
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
  char *result = (char *)malloc(BUFFER_SIZE);
  if (!result)
    return NULL;

  char buffer[BUFFER_SIZE];
  size_t i;

  strcpy(result, "[");

  for (i = 0; i < length; i++) {
    int firstValue, secondValue;
    switch (i) {
    case 0:
      firstValue = *(int *)area0[disposizione[i]].first;
      secondValue = *(int *)area0[disposizione[i]].second;
      snprintf(buffer, BUFFER_SIZE, "%zu:(%d,%d),", disposizione[i], firstValue,
               secondValue);
      break;
    case 1:
      firstValue = *(int *)area1[disposizione[i]].first;
      secondValue = *(int *)area1[disposizione[i]].second;
      snprintf(buffer, BUFFER_SIZE, "%zu:(%d,%d),", disposizione[i], firstValue,
               secondValue);
      break;
    case 2:
      firstValue = *(int *)area2[disposizione[i]].first;
      secondValue = *(int *)area2[disposizione[i]].second;
      snprintf(buffer, BUFFER_SIZE, "%zu:(%d,%d),", disposizione[i], firstValue,
               secondValue);
      break;
    default:
      continue;
    }
    snprintf(result + strlen(result), BUFFER_SIZE - strlen(result) - 1, "%s", buffer);
  }

  if (result[strlen(result) - 1] == ',') {
    result[strlen(result) - 1] = '\0';
  }
  strcat(result, "]\n");

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
  if (j == k) {
    printf("%s", spazioStatiOut(area0, area1, area2, disposizione, length));
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
char *soluzioniOut(GenPair *area0, GenPair *area1, GenPair *area2,
                   size_t *soluzione, size_t finanziabileTotale,
                   size_t length_soluzione) {
  int richiestaTotale = 0;
  size_t i;

  for (i = 0; i < length_soluzione; i++) {
    if (i == 0) {
      richiestaTotale += *(int *)area0[soluzione[i]].first;
    } else if (i == 1) {
      richiestaTotale += *(int *)area1[soluzione[i]].first;
    } else {
      richiestaTotale += *(int *)area2[soluzione[i]].first;
    }
  }

  if (richiestaTotale >= 0 && richiestaTotale <= finanziabileTotale) {
    char *result = (char *)malloc(BUFFER_SIZE);
    if (!result)
      return NULL;

    char *stateString = spazioStatiOut(area0, area1, area2, soluzione, length_soluzione);
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

/* Genera tutte le combinazioni di "soluzione" (non solo disposizioni con ripetizione). 
 * Ogni soluzione è un'istanza di a[0..length_soluzione) che non eccede finanziabileTotale.
 */
void soluzioni(GenPair *area0, GenPair *area1, GenPair *area2, size_t *a,
               size_t length_a, size_t *soluzione, size_t length_soluzione, 
               size_t finanziabileTotale, size_t j) {
  if (j == length_soluzione) {
    char *result = soluzioniOut(area0, area1, area2, soluzione, finanziabileTotale, length_soluzione);
    if (result != NULL) {
      printf("%s", result);
      free(result);
    }
  } else {
    for (size_t i = 0; i < length_a; i++) {
      soluzione[j] = a[i];
      swap(a, i, j);
      soluzioni(area0, area1, area2, a, length_a, soluzione, length_soluzione, finanziabileTotale, j + 1);
      swap(a, i, j);
    }
  }
}

/* Individua una risposta migliore */
char *rispostaOut(GenPair *area0, GenPair *area1, GenPair *area2,
                  size_t finanziabileTotale, size_t *risposta, size_t length_risposta,
                  size_t *soluzione, size_t length_soluzione) {
  size_t richiestaTotale = 0;
  size_t utilitaCorrente = 0;
  size_t utilitaMaxAttuale = 0;
  size_t i;

  /* Calcola richiestaTotale */
  for (i = 0; i < length_soluzione; i++) {
    size_t index = soluzione[i];

    // Calculate richiestaTotale (financing)
    if (i == 0 && index < 4) {
      richiestaTotale += *(int *)area0[index].first;
    } else if (i == 1 && index < 4) {
      richiestaTotale += *(int *)area1[index].first;
    } else if (i == 2 && index < 4) {
      richiestaTotale += *(int *)area2[index].first;
    }

    // Calculate utilitaCorrente (utility)
    if (i == 0 && index < 4) {
      utilitaCorrente += *(int *)area0[index].second;
    } else if (i == 1 && index < 4) {
      utilitaCorrente += *(int *)area1[index].second;
    } else if (i == 2 && index < 4) {
      utilitaCorrente += *(int *)area2[index].second;
    }
  }

  /* Calcola utilitaMaxAttuale */
  for (i = 0; i < length_risposta; i++) {
    size_t index = risposta[i];

    // Calculate utilitaMaxAttuale (utility of the best response)
    if (i == 0 && index < 4) {
      utilitaMaxAttuale += *(int *)area0[index].second;
    } else if (i == 1 && index < 4) {
      utilitaMaxAttuale += *(int *)area1[index].second;
    } else if (i == 2 && index < 4) {
      utilitaMaxAttuale += *(int *)area2[index].second;
    }
  }

  /* Se richiestaTotale non è eccessiva e se utilitaMaxAttuale è inferiore a utilitaCorrente, aggiorna la risposta */
  if (richiestaTotale <= finanziabileTotale && utilitaMaxAttuale < utilitaCorrente) {
    for (i = 0; i < length_soluzione; i++) {
      risposta[i] = soluzione[i];
    }

    // Allocate space for the result
    char *result = (char *)malloc(BUFFER_SIZE);
    if (!result) {
      return NULL; // If malloc fails, return NULL
    }

    // Generate the state string with spazioStatiOut
    char *stateString = spazioStatiOut(area0, area1, area2, risposta, length_risposta);
    if (!stateString) {
      free(result);  // Free result memory in case of error
      return NULL;
    }

    // Format the result string
    snprintf(result, BUFFER_SIZE,
             "%s nuova risposta con richiesta totale %ld <= %ld e utilità totale %ld.\n",
             stateString, richiestaTotale, finanziabileTotale, utilitaCorrente);

    free(stateString); // Free the memory allocated for stateString
    return result;
  }

  return NULL; // Return NULL if no improvement was found
}

/* Genera e verifica risposte migliori */
void risposta(GenPair *area0, GenPair *area1, GenPair *area2, size_t *a,
              size_t *r, size_t length_risposta, size_t *soluzione, size_t length_soluzione,
              size_t finanziabileTotale, size_t j, size_t k, size_t length) {
  if (j == k) {
    char *result = rispostaOut(area0, area1, area2, finanziabileTotale, r, length_risposta, soluzione, length_soluzione);
    if (result) {
      printf("%s", result);
      free(result);
    }
  } else {
    for (size_t i = 0; i < length; i++) {
      soluzione[j] = a[i];
      swap(a, i, j);

      risposta(area0, area1, area2, a, r, length_risposta, soluzione, length_soluzione,
               finanziabileTotale, j + 1, k, length);
      swap(a, i, j);
    }
  }
}
