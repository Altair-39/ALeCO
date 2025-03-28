
#ifndef KPFIFOBB_H
#define KPFIFOBB_H

#include "../../utility/header/ArrBoolInt.h"
#include "../../utility/header/IntFloat.h"
#include "../../utility/header/IstanzaKP.h"
#include <iostream>
#include <list>
#include <sstream>

using namespace std;

// The class for solving the Knapsack problem using a FIFO Branch and Bound
// approach
class KPFIFOBB {
public:
  // Main method to process the live nodes and generate the solution
  void risposte(IstanzaKP iKPBB, ArrBoolInt rispostaCorrente,
                list<ArrBoolInt> liveNodes);

protected:
  // Extracts an eNode according to the extraction policy implemented by
  // indiceENode
  ArrBoolInt eNode(IstanzaKP iKPBB, ArrBoolInt rispostaCorrente,
                   list<ArrBoolInt> &liveNodes);

  // Returns the index of the live node with the best estimated profit (lower
  // bound)
  virtual size_t indiceENode(IstanzaKP iKPBB, list<ArrBoolInt> liveNodes);

  // Rejects eNode if it's not a solution (weight exceeds capacity)
  bool rifiuta(IstanzaKP iKPBB, ArrBoolInt rispostaCorrente, ArrBoolInt node);

  // Accepts the eNode if its profit improves the current solution
  bool accetta(IstanzaKP iKPBB, ArrBoolInt rispostaCorrente, ArrBoolInt node);

  // Determines if eNode is complete (reached the end of the state space)
  bool completo(IstanzaKP iKPBB, ArrBoolInt rispostaCorrente, ArrBoolInt node);

  // Calculates the weight and profit of the live node
  IntFloat fH(IstanzaKP iKPBB, ArrBoolInt liveNode);

  // Estimates the profit for the live node, including both certain and possible
  // profits
  float stimaCostoPerEccesso(IstanzaKP iKPBB, IntFloat fHLiveNode,
                             ArrBoolInt liveNode);

  // Expands the live node by generating two child nodes
  void espande(ArrBoolInt node, list<ArrBoolInt> &liveNodes);

  // Converts solution information to a formatted string
  string toStringValori(string intestazione, IstanzaKP iKPBB, ArrBoolInt stato);

  // Converts eNode information to a formatted string
  string toStringENode(IstanzaKP iKPBB, ArrBoolInt stato);
};

#endif // KPFIFOBB_H
