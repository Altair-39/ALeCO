#include "../utility/header/ArrBoolInt.h"
#include <cstdlib>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

/** Risolve il problema Subsetsum aggiungendo una gestione a
 * coda dei live nodes, partendo dall'algoritmo per Subsetsum
 * in S3Rand.
 *
 * Il problema e' una coppia:
 * < X[0..n) di elementi di cui formare sottoinsiemi
 * , valore S da eguagliare, sommando elementi di un sottoinsieme
 *   X[0..j) di X[0..n), se X[0..j) esiste> .                      */
class S3FIFO {
public:
  void risposte(const vector<int> &insieme, int s,
                list<ArrBoolInt> &liveNodes) {
    while (!liveNodes.empty()) {
      ArrBoolInt node = eNode(insieme, s, liveNodes);

      if (!completo(insieme, s, node)) {
        if (!rifiuta(insieme, s, node, liveNodes)) {
          espande(node, liveNodes);
        } else { // mai percorso
          cout << "R: " << toStringENode(insieme, node) << std::endl;
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

  /* L'eNode e' estratto a caso dai live nodes.  */
  int indiceENode(const vector<int> &insieme, int s,
                  list<ArrBoolInt> &liveNodes) {
    return 0;
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
      liveNodes.push_front(nuovoLiveNode);
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

  S3FIFO s3FIFO;
  s3FIFO.risposte(insieme, somma, liveNodes);
  cout << "%---------------------------------" << std::endl;
}

void testHorowitz() {
  vector<int> insieme = {24, 11, 13, 7};
  int somma = 31;

  list<ArrBoolInt> liveNodes;
  vector<bool> soluzione = initSoluzione(insieme.size());
  ArrBoolInt radice(soluzione, 0);
  liveNodes.push_back(radice);

  S3FIFO s3FIFO;
  s3FIFO.risposte(insieme, somma, liveNodes);
  cout << "%---------------------------------" << std::endl;
}

int main() {
  testErickson();
  testHorowitz();
  return EXIT_SUCCESS;
}
