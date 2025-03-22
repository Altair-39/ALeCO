#include "header/ValutazioniSot.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

/**
 * Dato un array a, stampa tutte le sue permutazioni senza
 * alcuna ripetizione di elementi.
 * La forma dell'algoritmo e' orientata a costituire
 * il punto di partenza per realizzare algoritmi di backtracking
 * con strutture uniformi.
 *
 * In generale, al fine di applicare il algoritmi di backtracking,
 * la risposta (answer) cercata deve essere un tupla (x1,...,xn)
 * dove ogni xi e' scelto in un insieme finito Si che esprime una
 * istanza del problema da risolvere.
 *
 * Spesso, il problema su cui si applica un algoritmo di
 * backtrackingla richiede la ricerca di un vettore che massimizza
 * (minimizza, soddisfa) una funzione di accettazione della soluzione
 * che, proprio perche' accettata, diventa "risposta" (xi, ..., xn).
 * Altre volte, e' possible dover cercare tutte le risposte
 * disponibili nello spazio degli stati.
 */

void valutazioni(GenPair *a, int votoMaxConsentito, bool *risp, bool *soluzione,
                 int j, int lengthSoluzione, int lengthRisposta, int lengthA) {
  if (!completa(lengthSoluzione, j)) {
    if (!rifiuta(a, votoMaxConsentito, soluzione, j)) {
      valutazioni(a, votoMaxConsentito, risp, soluzione, j + 1,
                  lengthSoluzione, lengthRisposta, lengthA);
      soluzione[j] = true;
      valutazioni(a, votoMaxConsentito, risp, soluzione, j + 1,
                  lengthSoluzione, lengthRisposta,lengthA);
      soluzione[j] = !soluzione[j];
    }
  } else {
    if (accetta(a, votoMaxConsentito, risp, soluzione, j))
      risposta(a, votoMaxConsentito, risp, soluzione, j, lengthRisposta,
               lengthA);
  }
}

/* Restituisce true quando soluzione[0..j) puo' essere
 * una soluzione.
 */

bool completa(int lengthSoluzione, int j) { return j == lengthSoluzione; }

/* La precondizione di utilizzo e' che la nuova potenziale soluzione
 * non sia ancora in soluzione[0..j), cioe' j < soluzione.length.
 *
 * In tal caso, se il voto massimo distribuibile da soluzione[0..j)
 * e' gia' superiore a votoMaxConsentito, e' inutile continuare
 * ad estendere soluzione[0..j), restituendo true.
 */

bool rifiuta(GenPair *a, int votoMaxConsentito, bool *soluzione, int j) {
  size_t i = 0;
  float votoMaxCorrente = 0.0f;
  /* Voto massimo assegnato da soluzione[0..j). */
  while (i < j) {
    votoMaxCorrente += (soluzione[i] ? *(float *)a[i].first : 0.0f);
    i++;
  }
  return votoMaxCorrente > votoMaxConsentito;
}

/* La precondizione di utilizzo e' che la nuova potenziale soluzione sia in
 * soluzione[0..j) && j == soluzione.length.
 *
 * Nel caso in esame, soluzione[0..j) e' accettata, cioe' e' una risposta,
 * se il votoMaxCorrente che puo' assegnare non supera votoMaxConsentito
 * e la votazioneCorrente che soluzione[0..j) assegna e' superiore alla
 * miglioreVotazioneAttuale offerta da risposta[0..risposta.length).
 */

bool accetta(GenPair *a, int votoMaxConsentito, bool *risp, bool *soluzione,
             int j) {
  size_t i = 0;
  /* Voto massimo che soluzione[0..j) assegnerebbe. */
  int votoMaxCorrente = 0;
  /* Voto che soluzione[0..j) assegna. */
  float votazioneCorrente = 0.0f;
  /* Migliore votazione trovata sinora data da risposta[0..j). */
  float miglioreVotazioneAttuale = 0.0f;

  while (i < j) {
    votoMaxCorrente += soluzione[i] ? *(int *)a[i].first : 0;
    votazioneCorrente += soluzione[i] ? *(float *)a[i].second : 0;
    miglioreVotazioneAttuale += risp[i] ? *(float *)a[i].second : 0;
    i++;
  }

  /* Trovata nuova soluzione? */
  return votoMaxCorrente <= votoMaxConsentito &&
         miglioreVotazioneAttuale < votazioneCorrente;
}

/* Aggiorna la soluzione. La stampa anche a titolo didattico. */
void risposta(GenPair *a, int votoMaxConsentito, bool *risp, bool *soluzione,
              int j, int lengthRisposta, int lengthA) {
  size_t i = 0;

  /* Aggiorna risposta con quella migliore in
   * sottoinsieme[0..sottoinsieme.length). */
  while (i < lengthRisposta) {
    risp[i] = soluzione[i];
    i++;
  }

  i = 0;

  /* Stampa la nuova solution migliore, appena trovata. */
  printf("[");

  while (i < lengthA) {
    if (risp[i])
      printf("(%d,%f)", *(int *)a[i].first, *(float *)a[i].second);
    i++;
  }

  printf("]\n");
}
