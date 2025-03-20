#include "header/ValutazionePer.h"
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

/* Stampa lo spazio degli stati, ovvero le permutazioni degli elementi
 * in a[0..a.length).
 * */
char *spazioStatiOut(GenPair *a, size_t length) {
  size_t buffer_size = 100 * length;
  size_t i;
  char *s = (char *)malloc(buffer_size * sizeof(char));

  snprintf(s, buffer_size, "[");

  for (i = 0; i < length; i++) {
    char temp[50];
    snprintf(temp, sizeof(temp), "(%d, %.2f)", *(int *)a[i].first,
             *(float *)a[i].second);

    strncat(s, temp, buffer_size - strlen(s) - 1);
  }

  strncat(s, "]\n", buffer_size - strlen(s) - 1);

  return s;
}

void permutazioni(GenPair *a, size_t j, size_t length) {
  size_t i = j;
  if (j == length) {
    printf("%s", spazioStatiOut(a, length));
  } else {
    while (i < length) {
      swap(a, j, i);
      permutazioni(a, j + 1, length);
      swap(a, j, i);
      i++;
    }
  }
}

/* Individua lo spazio delle soluzioni come spazio dei prefissi delle
 * permutazioni degli elementi inizialmente in a[0.. a.length): per ogni
 * permutazione p, cerca il prefisso piu' lungo il cui votoMaxDistribuito non
 * sia maggiore del votoMaxConsentito. Quindi, determina la votazione che il
 * prefisso assegna.
 */

void soluzioni(GenPair *a, size_t votoMaxConsentito, size_t j, size_t length) {
  size_t i = j;
  if (j == length) {
    printf("%s\n", soluzioniOut(a, votoMaxConsentito, length));
  } else {
    while (i < length) {
      swap(a, j, i);
      soluzioni(a, votoMaxConsentito, j + 1, length);
      swap(a, j, i);
      i++;
    }
  }
}

/* Per ogni permutazione p degli elementi inizialmente in a[0.. a.length),
 * cerca il prefisso piu' lungo il cui votoMaxDistribuito
 * non sia maggiore del votoMaxConsentito. Quindi, determina la votazione che
 * il prefisso assegna.
 */

char *soluzioniOut(GenPair *a, size_t votoMaxConsentito, size_t length) {
  /* Segmento iniziale di a[0..a.length) il cui voto massimo distribuito,
   * indicato da votoMaxCorrente, non supera votoMaxConsentito.
   * Quindi, il segmento iniziale e' una soluzione.
   */
  size_t votoMaxCorrente = 0;
  size_t lunghezzaSoluzione = 0;
  size_t i = 0;
  float votazioneCorrente = 0.0f;
  bool oltreVotoMaxConsentito = false;

  while (lunghezzaSoluzione < length && !oltreVotoMaxConsentito) {
    /* Se, votoMaxCorrente sommato al nuovo voto a[lunghezzaSoluzione].pi0()
     * non sfora votoMax, allora aggiorna votoMaxCorrente. */
    oltreVotoMaxConsentito =
        (votoMaxCorrente + *(size_t *)a[lunghezzaSoluzione].first) >
        votoMaxConsentito;

    if (!oltreVotoMaxConsentito) {
      votoMaxCorrente += *(size_t *)a[lunghezzaSoluzione].first;
      lunghezzaSoluzione++;
    }
  }
  /* Il prefisso individuato, cioe' la soluzione, e' a[0..lunghezzaSoluzione).
   */

  /* Votazione che la soluzione a[1..lunghezzaSoluzione) assegna. */

  for (i = 0; i < lunghezzaSoluzione; i++)
    votazioneCorrente += *(float *)a[i].second;

  size_t buffer_size = 200;
  char *result = (char *)malloc(buffer_size * sizeof(char));
  if (!result) {
    return NULL;
  }

  snprintf(
      result, buffer_size,
      "%s ha una soluzione in a[0..%zu) con voto max %zu e votazione %.2f.\t",
      spazioStatiOut(a, length), lunghezzaSoluzione, votoMaxCorrente,
      votazioneCorrente);

  return result;
}

/*
 * Stampa la prima delle liste di migliori risposte date, enumerando tutte le
 * permutazioni possibili degli elementi inizialmente in test[0..test.length).
 * Esse si ricavano: i) generando tutte le permutazioni di test[0..test.length)
 * iniziale; ii) per ognuna di tali permutazioni P: ii.1) cercando un indice
 * currentLimit tale che il punteggio totale prodotto da P non superi il massimo
 * consentito; ii.2) confrontando il voto che P assegna ed il miglior voto
 * assegnato fino a quel punto da una qualche permutazione di
 * test[0..test.length) iniziale, visitata prima di P.
 */

GenPair *risposta(GenPair *a, GenPair *r, float votoMaxConsentito, size_t j,
                  size_t lengthA, size_t lengthRisposta) {
  size_t i = j;
  if (j == lengthA) {
    return rispostaOut(a, r, votoMaxConsentito, lengthA, lengthRisposta);
  } else {
    while (i < lengthA) {
      swap(a, j, i);
      r = risposta(a, r, votoMaxConsentito, j + 1, lengthA, lengthRisposta);
      swap(a, j, i);
      i++;
    }
    return r;
  }
}

/* Per ogni permutazione p degli elementi inizialmente in a[0.. a.length):
 * i) cerca il prefisso q di p piu' lungo il cui votoMaxDistribuito non sia
 * maggiore del votoMaxConsentito; ii) determina la votazione che q assegna;
 * iii) calcola sia la votazioneCorrente ricavabile da q, sia
 * l'attualeMiglioreVotazione, disponibile in risposta[0..risposta.length). iv)
 * Sostituisce risposta[0..risposta.length) con q se attualeMiglioreVotazione <
 * votazioneCorrente.
 */

GenPair *rispostaOut(GenPair *a, GenPair *risposta, size_t votoMaxConsentito,
                     size_t lengthA, size_t lengthRisposta) {
  /* Segmento iniziale di a[0..a.length) il cui voto massimo distribuito,
   * indicato da votoMaxCorrente, non supera votoMaxConsentito.
   * Quindi, il segmento iniziale e' una soluzione.
   */
  size_t votoMaxCorrente = 0;
  bool oltreVotoMax = false;
  size_t lunghezzaSoluzione = 0;
  size_t i;
  float votazioneCorrente = 0.0f;
  float attualeMiglioreVotazione = 0.0f;
  GenPair *nuovaRisposta;

  while (lunghezzaSoluzione < lengthA && !oltreVotoMax) {
    /* Se, votoMaxCorrente sommato al nuovo voto a[lunghezzaSoluzione].pi0()
     * non sfora votoMax, allora aggiorna votoMaxCorrente.
     */
    oltreVotoMax = (votoMaxCorrente + *(size_t *)a[lunghezzaSoluzione].first) >
                   votoMaxConsentito;

    if (!oltreVotoMax) {
      votoMaxCorrente += *(size_t *)a[lunghezzaSoluzione].first;
      lunghezzaSoluzione++;
    }
  }

  /* Il prefisso individuato, cioe' la soluzione, e' a[0..lunghezzaSoluzione).
   */

  /* Votazione che la soluzione a[0..lunghezzaSoluzione) assegna. */

  for (i = 0; i < lunghezzaSoluzione; i++)
    votazioneCorrente += *(float *)a[i].second;

  /* L'attuale migliore votazione e' fornita da risposta[0..risposta.length).
   * La calcoliamo per confrontarla con votazioneCorrente fornita da
   * a[0..lunghezzaSoluzione).
   */

  for (i = 0; i < lengthRisposta; i++)
    attualeMiglioreVotazione += *(float *)risposta[i].second;

  /* Se necessario, sostituisce l'attuale risposta[0..risposta.length)
   * con a[0..lunghezzaSoluzione).
   */
  if (attualeMiglioreVotazione < votazioneCorrente) {
    nuovaRisposta = malloc(sizeof(GenPair) * lunghezzaSoluzione);
    for (i = 0; i < lunghezzaSoluzione; i++)
      nuovaRisposta[i] = a[i];
    risposta = nuovaRisposta;

    printf("%s", spazioStatiOut(risposta, i));
    printf(" ha una nuova risposta in a[0..%ld)\n", lengthRisposta);
  }
  return risposta;
}
