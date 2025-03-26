#include "../utility/header/ArrBoolInt.h"
#include <cstdlib>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

/** Propone una riflessione di natura didattica sulla soluzione al
 * problema Subsetsum tramite un algoritmo Least-Cost search.
 *
 * Il problema e' una coppia:
 * < X[0..n) di elementi di cui formare sottoinsiemi
 * , valore S da eguagliare, sommando elementi di un sottoinsieme
 *   X[0..j) di X[0..n), se X[0..j) esiste> .
 *
 * Implementiamo l'euristica Least Cost-search su uno spazio degli
 * stati che rappresenta sottoinsiemi x[0..j) di indici {0..n-1}
 * dell'insieme X[0..n).
 *
 * 1) Definiamo il costo FH(x[0..j)) di costruire x[0..j) come:
 *
 *    FH(x[0..j)) = x[0]*X[0]+..+x[j-1]*X[j-1]
 *
 * in cui x[k]==1 codifica true e x[k]==0 codifica false.
 *
 * 2) Partendo dal valore *noto* FH(x[0..j)), lo scopo e'ottenere S
 * con gli elementi che, alla fine, x[0..j) conterra'. Con uno sforzo
 * computazionale accettabile, possiamo chiederci se sia possibile
 * estendere x[0..j) con elementi opportuni, che esso non contenga
 * ancora, ed approssimare per eccesso, nel modo migliore, il valore S
 * come segue:
 *
 *   S <= FH(x[0..j))+(X[j]+..+X[split-1]+X[split])
 *
 * dato un indice split opportuno. Analogamente, l'esstensione di
 * x[0..j) puo' essere "fermata un passo prima" ed ottenere la migliore
 * approssimazione per difetto di S, come segue:
 *
 *
 *  FH(x[0..j))+(X[j]+..+X[split-1]) <= S  .
 *
 * Se definiamo:
 *
 *       G(x[0..j)) = X[j]+..+X[split-1]+X[split]
 *
 * identificare l'intervallo:
 *
 *      FH(x[0..j))+(X[j]+..+X[split-1])
 *           <= S <= FH(x[0..j))+(X[j]+..+X[split-1]+X[split])
 *
 * equivale a trovare, con costo computazionale oggettivamente poco
 * rilevante, un indice split opportuno per cui:
 *
 *      FH(x[0..j))+G(x[0..j))-X[split-1]
 *                <= S <= FH(x[0..j))+G(x[0..j))  .
 *
 * Invertendo i segni, possiamo usare parte della relazione appena
 * scritta:
 *
 *      -(FH(x[0..j))+G(x[0..j))) <= -S
 *
 * come funzione costo approssimata per scegliere l'eNode,
 * che sara' quello, tra i live nodes, con:
 *
 *      -(FH(x[0..j))+G(x[0..j)))
 *
 * a valore minimo.
 *
 * OSSERVAZIONE
 * Vale la pena insistere sul fatto che l'identificazione di ogni istanza
 * di x[0..j) procede per tentativi e determina la complessita' dell'intero
 * processo di ricerca.
 *
 * Il calcolo di G(X[0..j)) e' molto meno costoso perche' non richiede
 * ricerche, ma aggiunge ad x[0..j) gli elementi fino a "giusto prima", o ad
 * "appena dopo" il valore S.
 *
 * NOTA
 * La definizione della funzione costo approssimata appena sintetizzata
 * non e' tra quelle canoniche che la letteratura offre, volendo risolvere il
 * Subsetsum con un algoritmo LC-search.
 * Pero', la funzione appena definita imposta un discorso che dovrebbe
 * semplificare il passaggio ad algoritmi Branch&Bound per il Knapsack, di cui
 * Subsetsum e' un caso particolare.
 * Inoltre, la funzione appena definita offre spunti per derivare altre funzioni
 * costo e sperimentarne l'efficacia.
 *
 * NOTA
 * Nel codice che segue soluzione[0..j) gioca il ruolo di x[0..j)
 * e insieme[0..n) il ruolo di X[0..n).                                 */
class S3LC {
public:
  void risposte(const vector<int> &insieme, int s,
                list<ArrBoolInt> &liveNodes) {
    while (!liveNodes.empty()) {
      ArrBoolInt node = eNode(insieme, s, liveNodes);

      if (!completo(insieme, s, node)) {
        if (!rifiuta(insieme, s, node, liveNodes)) {
          espande(node, liveNodes);
        } else { // mai percorso
          cout << "R: " << toStringENode(insieme, node) << endl;
        }
      } else {
        if (accetta(insieme, s, node)) {
          cout << "A: " << toStringENode(insieme, node) << endl;
        } else {
          cout << "N: " << toStringENode(insieme, node) << endl;
        }
      }
    }
  }

private:
  /* Restituisce un eNode, estratto in accordo con la politica implementata
   * dal metodo indiceENode. Prima dell'estrazione, stampa la lista dei
   * live nodes.                                                           */
  ArrBoolInt eNode(const vector<int> &insieme, int s,
                   list<ArrBoolInt> &liveNodes) {
    /* Stampa dei live nodes.    */
    cout << "Live nodes: " << toStringLiveNodes(insieme, liveNodes);

    int indice = indiceENode(insieme, s, liveNodes);
    auto it = liveNodes.begin();
    advance(it, indice);
    ArrBoolInt eNode = *it;
    liveNodes.erase(it);

    int fH = fCompostoH(insieme, s, eNode);
    std::cout << " ---> " << toStringENode(insieme, eNode) << " Costo : " << fH
              << ", Difetto: " << stimaCostoPerDifetto(insieme, fH, s, eNode)
              << ", Eccesso: " << stimaCostoPerEccesso(insieme, fH, s, eNode)
              << std::endl;

    return eNode;
  }

  /* Restituisce l'indice al live node con costo minimo
   * e stampa l'eNode estratto con costo e costo stimato.             */
  int indiceENode(const std::vector<int> &insieme, int s,
                  const std::list<ArrBoolInt> &liveNodes) {
    auto it = liveNodes.begin();
    /* Assume che il primo liveNode di liveNodes sia a costo minimo. */
    int indiceLiveNodeCostoMinimo = 0;
    ArrBoolInt liveNode = *it;

    int fH = fCompostoH(insieme, s, liveNode);
    int costoMinimo = -stimaCostoPerEccesso(insieme, fH, s, liveNode);

    int indice = 1;
    /* Cerca il liveNode a costo minimo. */
    for (++it; it != liveNodes.end(); ++it, ++indice) {
      liveNode = *it;

      fH = fCompostoH(insieme, s, liveNode);
      int costoLiveNode = -stimaCostoPerEccesso(insieme, fH, s, liveNode);

      if (costoLiveNode < costoMinimo) {
        indiceLiveNodeCostoMinimo = indice;
        costoMinimo = costoLiveNode;
      }
    }

    return indiceLiveNodeCostoMinimo;
  }

  bool completo(const vector<int> &insieme, int s, const ArrBoolInt &eNode) {
    vector<bool> soluzione = eNode.pi0();
    int j = eNode.pi1();
    return soluzione.size() == j;
  }

  bool rifiuta(const vector<int> &insieme, int somma, const ArrBoolInt &eNode,
               list<ArrBoolInt> &liveNodes) {
    return false;
  }

  /* Estende l'elenco dei liveNodes con due figli di eNode. */
  void espande(const ArrBoolInt &eNode, list<ArrBoolInt> &liveNodes) {
    vector<bool> soluzione = eNode.pi0();
    int j = eNode.pi1();

    for (bool nuovoElementoSoluzione :
         {static_cast<bool>(soluzione[j]), static_cast<bool>(!soluzione[j])}) {
      vector<bool> nuovaSoluzione = soluzione;
      nuovaSoluzione[j] = nuovoElementoSoluzione;
      ArrBoolInt nuovoLiveNode(nuovaSoluzione, j + 1);
      liveNodes.push_back(nuovoLiveNode);
    }
  }

  bool accetta(const vector<int> &insieme, int somma, const ArrBoolInt &eNode) {
    vector<bool> soluzione = eNode.pi0();
    int j = eNode.pi1();

    int sommaENode = 0;
    for (int i = 0; i < j; i++) {
      sommaENode += (soluzione[i]) ? insieme[i] : 0;
    }
    return sommaENode == somma;
  }

  string toStringENode(const vector<int> &insieme, const ArrBoolInt &eNode) {
    vector<bool> soluzione = eNode.pi0();
    int j = eNode.pi1();
    int i = 0;
    string stringa = "[";
    while (i < j) {
      stringa += (soluzione[i]) ? " " + to_string(insieme[i]) + ","
                                : "!" + to_string(insieme[i]) + ",";
      i++;
    }

    if (stringa.back() == ',') {
      stringa.pop_back();
    }
    return stringa + "]";
  }

  /* Restituisce il costo noto di soluzione[0..j) in liveNode, ovvero
   * l'analogo di FH(soluzione[0..j)).                                       */

  int fCompostoH(const vector<int> &insieme, int s,
                 const ArrBoolInt &liveNode) {
    vector<bool> soluzione = liveNode.pi0();
    int j = liveNode.pi1();
    int i = 0;

    int fCompostoH = 0;
    while (i < j) {
      fCompostoH += (soluzione[i]) ? insieme[i] : 0;
      i++;
    }

    return fCompostoH;
  }

  /* Restituisce il valore G(soluzione[0..j))-insieme[split],
   * cioe' somma a soluzione[0..j) tutti gli elementi in
   * insieme[j..split)
   * dove split e' il minimo indice per cui
   * aggiungendo insieme[j..split) non si supera S, mentre
   * aggiungendo insieme[j..split] si ottiene almeno S.
   *
   * E' ispirato all'Algoritmo 8.1 di Horowitz di nome UBound. */
  int stimaCostoPerDifetto(const vector<int> &insieme, int fH, int s,
                           const ArrBoolInt &liveNode) {
    int j = liveNode.pi1();

    int costoLiveNode = fH;
    int i = j;
    bool incrementa = true;
    while (i < insieme.size() && incrementa) {
      incrementa = (costoLiveNode + insieme[i] < s);
      if (incrementa) {
        costoLiveNode += insieme[i];
        i++;
      }
    }

    return costoLiveNode;
  }

  /* Restituisce il valore G(soluzione[0..j)), cioe' somma
   * a soluzione[0..j) tutti gli elementi in insieme[j..split]
   * dove split e' il minimo indice per cui
   * aggiungendo insieme[j..split) non si supera S, mentre
   * aggiungendo insieme[j..split] ottiene almeno S.
   *
   * E' ispirato all'Algoritmo 7.11 di Horowitz di nome Bound.
   * La differenza e' che non si fa alcun rilassamento lineare
   * perche' conosciamo il limite S da ottenere.                */
  int stimaCostoPerEccesso(const vector<int> &insieme, int fH, int s,
                           const ArrBoolInt &liveNode) {
    int j = liveNode.pi1();

    int costoLiveNode = fH;
    int i = j;
    bool incrementa = true;
    while (i < insieme.size() && incrementa) {
      incrementa = (costoLiveNode < s);
      if (incrementa) {
        costoLiveNode += insieme[i];
        i++;
      }
    }
    return costoLiveNode;
  }

  string toStringLiveNodes(const vector<int> &insieme,
                           const list<ArrBoolInt> &liveNodes) {
    string stringa = "{";

    for (const auto &liveNode : liveNodes) {
      stringa += toStringENode(insieme, liveNode);
    }

    return stringa + "}";
  }
};

vector<bool> initSoluzione(size_t size) { return vector<bool>(size, false); }

void testErickson() {
  vector<int> insieme = {8, 6, 7, 5, 3, 10, 9};
  int somma = 15;

  list<ArrBoolInt> liveNodes;
  vector<bool> soluzione = initSoluzione(insieme.size());
  ArrBoolInt radice(soluzione, 0);
  liveNodes.push_back(radice);

  S3LC s3LC;
  s3LC.risposte(insieme, somma, liveNodes);
  cout << "%---------------------------------" << endl;
}

void testHorowitz() {
  vector<int> insieme = {24, 11, 13, 7};
  int somma = 31;

  list<ArrBoolInt> liveNodes;
  vector<bool> soluzione = initSoluzione(insieme.size());
  ArrBoolInt radice(soluzione, 0);
  liveNodes.push_back(radice);

  S3LC s3LC;
  s3LC.risposte(insieme, somma, liveNodes);
  cout << "%---------------------------------" << endl;
}

int main() {
  testErickson();
  testHorowitz();
  return EXIT_SUCCESS;
}
