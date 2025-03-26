#include "../utility/header/ArrIntInt.h"
#include <cstdio>
#include <cstdlib>
#include <list>
#include <vector>

using namespace std;

class SottoinsiemiIterFIFO {

public:
  int conta = 0;

  /** Genera tutte le permutazioni di una collezione di elementi
   * con un processo iterativo, producendo uno spazio degli stati
   * in accordo con una visita in ampiezza dell'albero che lo
   * rappresenta.
   *
   * La visita in ampiezza segue dall'accodare (politica FIFO)
   * tutti i figli di un eNode alla coda dei liveNodes.         */

  /* Visita iterativamente l'elenco dei liveNodes, finche'
   * non si vuota. La terminazione e' assicurata dalla finitezza
   * dello spazio degli stati. Si assume un elenco iniziale di
   * liveNodes composto da un nodo che corrisponde alla radice
   * dello spazio degli stati.                                    */

  void risposte(list<ArrIntInt> &liveNodes) {
    while (!liveNodes.empty()) {
      ArrIntInt node = eNode(liveNodes);

      if (!completo(node)) {
        if (!rifiuta()) {
          espande(node, liveNodes);
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
  }

private:
  /* Preleva sempre il primo elemento disponibile nello spazio
   * degli stati.                                                */
  ArrIntInt eNode(list<ArrIntInt> &liveNodes) {
    ArrIntInt node = liveNodes.front();
    liveNodes.pop_front();
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
 
void espande(const ArrIntInt& eNode, std::list<ArrIntInt>& liveNodes) {
    vector<int> soluzione = eNode.pi0();
    int j = eNode.pi1();

    int i = j;
    while (i < soluzione.size()) {
        swap(soluzione[i], soluzione[j]);

        vector<int> nuovaSoluzione = soluzione; 
        ArrIntInt nuovoLiveNode(nuovaSoluzione, j + 1);

        liveNodes.push_back(nuovoLiveNode);

        swap(soluzione[i], soluzione[j]);
        i++;
    }
}

  /* Generando tutto lo spazio delle permutazioni, non appena
   * una soluzione e' completa non possiamo far altro che accettare. */
  bool accetta() { return true; }


string toStringENode(const ArrIntInt& node) {
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
    SottoinsiemiIterFIFO generator;
    generator.risposte(liveNodes);
    cout << endl;
}

void testCase2() {
    cout << "Test Case 2: {4, 5}" << endl;
    vector<int> initialSolution = {4, 5};
    ArrIntInt initialNode(initialSolution, 0);
    list<ArrIntInt> liveNodes;
    liveNodes.push_back(initialNode);
    SottoinsiemiIterFIFO generator;
    generator.risposte(liveNodes);
    cout << endl;
}

void testCase3() {
    cout << "Test Case 3: {1, 2, 3, 4}" << endl;
    vector<int> initialSolution = {1, 2, 3, 4};
    ArrIntInt initialNode(initialSolution, 0);
    list<ArrIntInt> liveNodes;
    liveNodes.push_back(initialNode);
    SottoinsiemiIterFIFO generator;
    generator.risposte(liveNodes);
    cout << endl;
}

void testCase4() {
    cout << "Test Case 4: {10, 20, 30}" << endl;
    vector<int> initialSolution = {10, 20, 30};
    ArrIntInt initialNode(initialSolution, 0);
    list<ArrIntInt> liveNodes;
    liveNodes.push_back(initialNode);
    SottoinsiemiIterFIFO generator;
    generator.risposte(liveNodes);
    cout << endl;
}

void testCase5() {
    cout << "Test Case 5: {0, 1, 2, 3, 4}" << endl;
    vector<int> initialSolution = {0, 1, 2, 3, 4};
    ArrIntInt initialNode(initialSolution, 0);
    list<ArrIntInt> liveNodes;
    liveNodes.push_back(initialNode);
    SottoinsiemiIterFIFO generator;
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
