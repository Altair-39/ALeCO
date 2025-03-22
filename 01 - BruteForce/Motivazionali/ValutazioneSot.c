#include "header/ValutazioneSot.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(GenPair *a, size_t i, size_t j) {
  GenPair tmp;
  tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}

void spazioStati(GenPair *a, bool *sottoinsieme, size_t j, size_t length) {
  char *spazioS;
  if (j == length) {
    spazioS = spazioStatiOut(a, sottoinsieme, length);
    if (spazioS) {
      printf("%s", spazioS);
      free(spazioS);
    }
  } else {
    spazioStati(a, sottoinsieme, j + 1, length);
    sottoinsieme[j] = !sottoinsieme[j];
    spazioStati(a, sottoinsieme, j + 1, length);
    sottoinsieme[j] = !sottoinsieme[j];
  }
}

/*
 * Stampa tutte le soluzioni, cioe' i sottoinsiemi di risposte che sono
 * potenziali risposte: sottoinsiemi in grado di assegnare un voto massimo
 * che non supera quello consentito.
 */
char *spazioStatiOut(GenPair *a, bool *sottoinsieme, size_t length) {
  size_t buffer_size = 100 * length;
  size_t i = 0;
  char *s = (char *)malloc(buffer_size * sizeof(char));
  if (s == NULL) {
    return NULL;
  }

  snprintf(s, buffer_size, "[");

  while (i < length) {
    if (sottoinsieme[i]) {
      char temp[50];
      snprintf(temp, sizeof(temp), "(%d, %.2f)", *(int *)a[i].first,
               *(float *)a[i].second);
      strncat(s, temp, buffer_size - strlen(s) - 1);
    }
    i++;
  }

  strncat(s, "]", buffer_size - strlen(s) - 1);

  return s;
}

/*
 * Stampa tutte le soluzioni, cioe' i sottoinsiemi di risposte che sono
 * potenziali risposte: sottoinsiemi in grado di assegnare un voto massimo
 * che non supera quello consentito.
 */

void soluzioni(GenPair *a, bool *soluzione, size_t votoMaxConsentito, size_t j,
               size_t length) {
  char *ris;
  if (j == length) {
    ris = soluzioniOut(a, soluzione, votoMaxConsentito, length);
    if (ris) {
      printf("%s\n", ris);
      free(ris);
    }
  } else {
    soluzioni(a, soluzione, votoMaxConsentito, j + 1, length);
    soluzione[j] = !soluzione[j];
    soluzioni(a, soluzione, votoMaxConsentito, j + 1, length);
    soluzione[j] = !soluzione[j];
  }
}

char *soluzioniOut(GenPair *a, bool *soluzione, size_t votoMaxConsentito,
                   size_t length) {
  size_t i = 0;
  size_t votoMaxCorrente = 0;
  float votazioneCorrente = 0.0f;

  // Calculate votoMaxCorrente and votazioneCorrente based on the solution array
  while (i < length) {
    if (soluzione[i]) {
      votoMaxCorrente += *(int *)a[i].first;
      votazioneCorrente += *(float *)a[i].second;
    }
    i++;
  }

  // If the current maximum vote is less than or equal to the allowed maximum,
  // proceed
  size_t buffer_size = 200;
  char *result = (char *)malloc(buffer_size * sizeof(char));
  char *ris;
  if (!result) {
    return NULL; // Error allocating memory
  }

  // Format the output string
  if (votoMaxCorrente <= votoMaxConsentito) {
    ris = spazioStatiOut(a, soluzione, length);
    if (ris) {
      snprintf(result, buffer_size,
               "%s ha una soluzione in a[0..%zu) con voto max %zu e votazione "
               "%.2f.\n",
               ris, length, votoMaxCorrente, votazioneCorrente);
      free(ris);
    }
  } else {
    snprintf(
        result, buffer_size,
        "Soluzione invalida. Voto max %zu supera il voto consentito %zu.\n",
        votoMaxCorrente, votoMaxConsentito);
  }

  return result;
}

char *rispostaOut(GenPair *a, size_t votoMaxConsentito, bool *soluzione,
                  bool *risposta, size_t length) {
  size_t i = 0;
  size_t votoMaxCorrente = 0;
  float votazioneCorrente = 0.0f;

  while (i < length) {
    if (soluzione[i]) {
      votoMaxCorrente += *(int *)a[i].first;
      votazioneCorrente += *(float *)a[i].second;
    }
    i++;
  }

  i = 0;

  float attualeMiglioreVotazione = 0.0f;
  while (i < length) {
    if (risposta[i])
      attualeMiglioreVotazione += *(float *)a[i].second;
    i++;
  }

  if (votoMaxCorrente <= votoMaxConsentito &&
      attualeMiglioreVotazione < votazioneCorrente) {
    i = 0;
    while (i < length) {
      risposta[i] = soluzione[i];
      i++;
    }

    size_t buffer_size = 200;
    char *messaggio = (char *)malloc(buffer_size * sizeof(char));
    char *ris = spazioStatiOut(a, soluzione, length);
    if (messaggio && ris) {
      snprintf(messaggio, buffer_size,
               "Nuova risposta %s che distribuisce voto max %zu e assegna "
               "votazione %.2f.\n",
               ris, votoMaxCorrente, votazioneCorrente);
      free(ris);
      return messaggio;
    } else {
      return NULL;
    }
  }
  return NULL;
}

void risposta(GenPair *a, size_t votoMaxConsentito, bool *r, bool *soluzione,
              size_t j, size_t length) {
  char *ris;
  if (j == length) {
    ris = rispostaOut(a, votoMaxConsentito, soluzione, r, length);
    if (ris) {
      printf("%s", ris);
      free(ris);
    }
  } else {
    // Recursive call to explore both possibilities (include or exclude)
    risposta(a, votoMaxConsentito, r, soluzione, j + 1,
             length); // Do not include a[j]

    // Flip the current solution element and recurse again
    soluzione[j] = !soluzione[j];
    risposta(a, votoMaxConsentito, r, soluzione, j + 1, length); // Include a[j]

    // Restore the original state
    soluzione[j] = !soluzione[j];
  }
}
