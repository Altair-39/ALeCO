#include "../utility/header/ArrIntInt.h"
#include <cstdlib>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

/* Visita ricorsivamente l'elenco dei liveNodes, finche'
 * non si vuota. La terminazione e' assicurata dalla finitezza
 * dello spazio degli stati. Si assume un elenco iniziale di
 * liveNodes composto da un nodo che corrisponde alla radice
 * dello spazio degli stati.                                    */
class PermutazioniRicRptLIFO {
public:
  void risposte(list<ArrIntInt> &spazioStati) {
    ArrIntInt node = eNode(spazioStati);

    if (!completo(node)) {
      if (!rifiuta()) {
        espande(node, spazioStati);
        while (!spazioStati.empty()) {
          risposte(spazioStati);
        }
      } else {
        cout << "R: " << toStringENode(node) << endl;
      }
    } else {
      if (accetta()) {
        cout << "A: " << toStringENode(node) << endl;
      } else {
        cout << "N: " << toStringENode(node) << endl;
      }
    }
  }

private:
  /* Preleva sempre il primo elemento disponibile nello spazio
   * degli stati.                                                */
  ArrIntInt eNode(list<ArrIntInt> &liveNodes) {
    ArrIntInt node = liveNodes.front();
    liveNodes.pop_back(); // LIFO
    return node;
  }

  /* Un eNode corrisponde and una soluzione completa se, la
   * sua componente, corrispondente ad una soluzione, e',
   * appunto, completa.                                        */
  bool completo(const ArrIntInt &eNode) {
    vector<int> soluzione = eNode.pi0();
    int j = eNode.pi1();
    return soluzione.size() == j;
  }

  /* Generando tutto lo spazio delle permutazioni, non
   * si rifiuta mai . */
  bool rifiuta() { return false; }

  /* Implementa l'invariante di una visita in ampiezza dello spazio
   * degli stati. In particolare, tratta l'elenco dei liveNodes
   * come una coda, accodando i figli dell'attuale eNode.          */

  void espande(const ArrIntInt &eNode, list<ArrIntInt> &spazioStati) {
    vector<int> soluzione = eNode.pi0();
    int j = eNode.pi1();

    int i = 0;
    while (i < soluzione.size()) {
      swap(soluzione[i], soluzione[j]);

      vector<int> soluzioneFiglio = soluzione;
      ArrIntInt nuovoLiveNode(soluzioneFiglio, j + 1);

      spazioStati.push_front(nuovoLiveNode);

      swap(soluzione[i], soluzione[j]);
      i++;
    }
  }

  /* Generando tutto lo spazio delle permutazioni, non appena
   * una soluzione e' completa non possiamo far altro che accettare. */
  bool accetta() { return true; }

  string toStringENode(const ArrIntInt &node) {
    vector<int> soluzione = node.pi0();
    int j = node.pi1();

    string result = "{ ";
    for (size_t i = 0; i < soluzione.size(); i++) {
      result += to_string(soluzione[i]);
      if (i < soluzione.size() - 1)
        result += ", ";
    }
    result += " } (j = " + to_string(j) + ")";
    return result;
  }
};

void testCase1() {
  cout << "Test Case 1: {1, 2, 3}" << endl;
  vector<int> initialSolution = {1, 2, 3};
  ArrIntInt initialNode(initialSolution, 0);
  list<ArrIntInt> liveNodes;
  liveNodes.push_back(initialNode);
  PermutazioniRicRptLIFO generator;
  generator.risposte(liveNodes);
  cout << endl;
}

void testCase2() {
  cout << "Test Case 2: {4, 5}" << endl;
  vector<int> initialSolution = {4, 5};
  ArrIntInt initialNode(initialSolution, 0);
  list<ArrIntInt> liveNodes;
  liveNodes.push_back(initialNode);
  PermutazioniRicRptLIFO generator;
  generator.risposte(liveNodes);
  cout << endl;
}

void testCase3() {
  cout << "Test Case 3: {1, 2, 3, 4}" << endl;
  vector<int> initialSolution = {1, 2, 3, 4};
  ArrIntInt initialNode(initialSolution, 0);
  list<ArrIntInt> liveNodes;
  liveNodes.push_back(initialNode);
  PermutazioniRicRptLIFO generator;
  generator.risposte(liveNodes);
  cout << endl;
}

void testCase4() {
  cout << "Test Case 4: {10, 20, 30}" << endl;
  vector<int> initialSolution = {10, 20, 30};
  ArrIntInt initialNode(initialSolution, 0);
  list<ArrIntInt> liveNodes;
  liveNodes.push_back(initialNode);
  PermutazioniRicRptLIFO generator;
  generator.risposte(liveNodes);
  cout << endl;
}

void testCase5() {
  cout << "Test Case 5: {0, 1, 2, 3, 4}" << endl;
  vector<int> initialSolution = {0, 1, 2, 3, 4};
  ArrIntInt initialNode(initialSolution, 0);
  list<ArrIntInt> liveNodes;
  liveNodes.push_back(initialNode);
  PermutazioniRicRptLIFO generator;
  generator.risposte(liveNodes);
  cout << endl;
}

int main() {
  testCase1();
  testCase2();
  testCase3();
  testCase4();
  testCase5();
  return EXIT_SUCCESS;
}
