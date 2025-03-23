#include "../utility/ArrBoolInt.cpp"
#include <ctime>
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <string>
#include <vector>
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
 * e insieme[0..n) il ruolo di X[0..n).
 */
using namespace std;

class S3LC {

public:
  void risposte(const vector<int> &insieme, int s,
                list<ArrBoolInt> liveNodes) {
    list<ArrBoolInt>::iterator it = liveNodes.begin();
    while (it != liveNodes.end()) {

      ArrBoolInt node = eNode(insieme, s, liveNodes);
      if (!completo(insieme, s, node)) {
        if (!rifiuta(insieme, s, node, liveNodes))
          liveNodes = espande(node, liveNodes);
        else
          cout << "\nR: " << toStringENode(insieme, node);
      } else {
        if (accetta(insieme, s, node))
          cout << "\nA: " << toStringENode(insieme, node);
        else
          cout << "\nN: " << toStringENode(insieme, node);
      }
      it++;
    }
  }

  /* Restituisce un eNode, estratto in accordo con la politica implementata
   * dal metodo indiceENode. Prima dell'estrazione, stampa la lista dei
   * live nodes.
   */
  ArrBoolInt eNode(const vector<int> &insieme, int s,
                   list<ArrBoolInt> liveNodes) {
    int indiceENode, fH;
    auto it = liveNodes.begin();

    cout << "Live nodes: " << toStringLiveNodes(insieme, liveNodes);

    indiceENode = getIndiceENode(insieme, s, liveNodes);
    advance(it, indiceENode);
    ArrBoolInt eNode = *it;

    liveNodes.erase(it);

    fH = fCompostoH(insieme, s, eNode);

    cout << "---> " << toStringENode(insieme, eNode) << " Costo: " << fH
         << ", Difetto: " << stimaCostoPerDifetto(insieme, fH, s, eNode)
         << ", Eccesso: " << stimaCostoPerEccesso(insieme, fH, s, eNode);
    return eNode;
  }

  /* Restituisce il valore G(soluzione[0..j))-insieme[split],
   * cioe' somma a soluzione[0..j) tutti gli elementi in
   * insieme[j..split)
   * dove split e' il minimo indice per cui
   * aggiungendo insieme[j..split) non si supera S, mentre
   * aggiungendo insieme[j..split] si ottiene almeno S.
   *
   * E' ispirato all'Algoritmo 8.1 di Horowitz di nome UBound.
   */
  int stimaCostoPerDifetto(const vector<int> &insieme, int fH, int s,
                           ArrBoolInt liveNode) {
    int j = liveNode.pi1();
    int i = j;
    int costoLiveNode = fH;
    bool incrementa = true;

    while (i < (int)insieme.size() && incrementa) {
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
   * perche' conosciamo il limite S da ottenere.
   */

  int stimaCostoPerEccesso(const vector<int> &insieme, int fH, int s,
                           ArrBoolInt liveNode) {
    int j = liveNode.pi1();
    int i = j;
    int costoLiveNode = fH;
    bool incrementa = false;

    while (i < (int)insieme.size() && incrementa) {
      incrementa = costoLiveNode < s;
      if (incrementa) {
        costoLiveNode += insieme[i];
        i++;
      }
    }
    return costoLiveNode;
  }

  /* Restituisce il costo noto di soluzione[0..j) in liveNode, ovvero
   * l'analogo di FH(soluzione[0..j)).
   */
  int fCompostoH(const vector<int> &insieme, int s, ArrBoolInt liveNodes) {
    vector<bool> soluzione = liveNodes.pi0();
    int j = liveNodes.pi1();
    int fCompostH = 0;
    int i = 0;

    while (i < j) {
      fCompostH += (soluzione[i]) ? insieme[i] : 0;
      i++;
    }

    return fCompostH;
  }

  /* Estende l'elenco dei liveNodes con due figli di eNode. */
  list<ArrBoolInt> espande(ArrBoolInt node, list<ArrBoolInt> liveNodes) {
    vector<bool> soluzione = node.pi0();
    int j = node.pi1();
    bool val = soluzione[j];

    for (bool nuovoElementoSoluzione : {val, !val}) {
      vector<bool> nuovaSoluzione = soluzione;
      nuovaSoluzione[j] = nuovoElementoSoluzione;

      ArrBoolInt nuovoLiveNode(nuovaSoluzione, j + 1);
      liveNodes.push_back(nuovoLiveNode); /* FIFO */
    }
    return liveNodes;
  }

  int getIndiceENode(vector<int> insieme, int s, list<ArrBoolInt> liveNodes) {
    int indiceLiveNodeCostoMinimo = 0;
    auto it = next(liveNodes.begin(), indiceLiveNodeCostoMinimo);
    ArrBoolInt liveNode = *it;
    int fH = fCompostoH(insieme, s, liveNode);
    int costoMinimo = -stimaCostoPerEccesso(insieme, fH, s, liveNode);
    int costoLiveNode = 0;
    int indice = 1;

    while (indice < (int)liveNodes.size()) {
      auto it = next(liveNodes.begin(), indice);
      liveNode = *it;
      fH = fCompostoH(insieme, s, liveNode);

      costoLiveNode = -stimaCostoPerEccesso(insieme, fH, s, liveNode);

      if (costoLiveNode < costoMinimo) {
        indiceLiveNodeCostoMinimo = indice;
        costoMinimo = costoLiveNode;
      }
      indice++;
    }
    it = next(liveNodes.begin(), indiceLiveNodeCostoMinimo);
    liveNode = *it;

    return indiceLiveNodeCostoMinimo;
  }

  bool completo(vector<int> insieme, int s, ArrBoolInt node) {
    int soluzioneLength = node.pi0().size();
    int j = node.pi1();
    return soluzioneLength == j;
  }

  bool rifiuta(vector<int> insieme, int somma, ArrBoolInt node,
               list<ArrBoolInt> liveNodes) {
    return false;
  }

  bool accetta(vector<int> insieme, int somma, ArrBoolInt node) {
    vector<bool> soluzione = node.pi0();
    int j = node.pi1();
    int i = 0, sommaNode = 0;

    while (i < j) {
      sommaNode += (soluzione[i]) ? insieme[i] : 0;
      i++;
    }
    return sommaNode == somma;
  }

private:
  string intToString(int num) {
    ostringstream oss;
    oss << num;
    return oss.str();
  }

  string toStringENode(const vector<int> &insieme, ArrBoolInt eNode) {
    vector<bool> soluzione = eNode.pi0();
    int j = eNode.pi1();

    string stringa = "[";
    int i = 0;

    while (i < j) {
      if (soluzione[i]) {
        stringa += " " + intToString(insieme[i]) + ",";
      } else {
        stringa += "!" + intToString(insieme[i]) + ",";
      }
      i++;
    }

    if (!stringa.empty() && stringa.back() == ',') {
      stringa = stringa.substr(0, stringa.length() - 1);
    }

    stringa += "]";
    return stringa;
  }

  string toStringLiveNodes(const vector<int> &insieme,
                           const list<ArrBoolInt> &liveNodes) {
    string stringa = "{";

    for (auto it = liveNodes.begin(); it != liveNodes.end(); ++it) {
      ArrBoolInt liveNode = *it;
      stringa += toStringENode(insieme, liveNode);
    }

    stringa += "}";
    return stringa;
  }
};

/*-------------------------------------------------------------*/
vector<bool> initSoluzione(int n) {
  vector<bool> soluzione;
  size_t i = 0;
  while (i < soluzione.size()) {
    soluzione[i] = true;
    i++;
  }
  return soluzione;
}

void testErickson() { /* 289 */
  vector<int> insieme = {8, 6, 7, 5, 3, 10, 9};
  int somma = 15;
  list<ArrBoolInt> liveNodes;
  vector<bool> soluzione = initSoluzione(insieme.size());
  ArrBoolInt radice = ArrBoolInt(soluzione, 0);
  S3LC s3LC;

  liveNodes.push_front(radice);

  s3LC.risposte(insieme, somma, liveNodes);

  cout << "\n%---------------------------------\n";
}

int main(int argc, char *argv[]) {

  testErickson();

  return EXIT_SUCCESS;
}
