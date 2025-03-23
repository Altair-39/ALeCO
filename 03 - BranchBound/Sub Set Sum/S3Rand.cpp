#include "../utility/header/ArrBoolInt.h"
#include <ctime>
#include <iostream>
#include <iterator>
#include <list>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/** Offre il nucleo di un algoritmo iterativo che genera un spazio
 * degli stati a sottoinsiemi, risolvere Subsetsum in accordo con
 * diverse politiche di gestione dei live nodes e di scelta dell'eNode.
 *
 * Il problema e' una coppia:
 * < X[0..n) di elementi di cui formare sottoinsiemi
 * , valore S da eguagliare, sommando elementi di un sottoinsieme
 *   X[0..j) di X[0..n), se X[0..j) esiste> .
 *
 * In particolare, definisce le funzioni su cui basare una LC-search,
 * per Subsetsum, la cui misura, relativa ad un nodo x[0..j), fornisce
 * la migliore approssimazione per difetto e per eccesso del valore S.
 */

class S3Rand {

public:
  void risposte(const vector<int> &insieme, int s, list<ArrBoolInt> &liveNodes) {
    list<ArrBoolInt>::iterator it = liveNodes.begin();
    while (it != liveNodes.end()) {
      ArrBoolInt node = eNode(insieme, s, liveNodes);
      if (!completo(insieme, s, node)) {
        if (!rifiuta(insieme, s, node, liveNodes))
          liveNodes = espande(node, liveNodes);
        else
          cout << "R: " << toStringENode(insieme, node);
      } else {
        if (accetta(insieme, s, node))
          cout << "A: " << toStringENode(insieme, node);
        else
          cout << "N: " << toStringENode(insieme, node);
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

    cout << "Live nodes: " + toStringLiveNodes(insieme, liveNodes);

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
        costoLiveNode += insieme[i] < s;
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

  /* L'eNode e' estratto a caso dai live nodes.  */
  int getIndiceENode(const vector<int> &insieme, int s,
                             list<ArrBoolInt> liveNodes) {
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> distrib(0, liveNodes.size() - 1);

    auto it = liveNodes.begin();
    advance(it, distrib(gen));

    return distance(liveNodes.begin(), it);
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
