
#ifndef S3LC_H
#define S3LC_H

#include "../../utility/header/ArrBoolInt.h"
#include "S3Rand.h"

#include <list>
#include <vector>
using namespace std;

class S3LC : public S3Rand {
public:
  /* Restituisce l'indice al live node con costo minimo
   * e stampa l'eNode estratto con costo e costo stimato.
   */
  int getIndiceENode(vector<int> insieme, int s, list<ArrBoolInt> liveNodes);

  // Constructor (if necessary)
  S3LC() = default;

  // Destructor (if necessary)
  ~S3LC() = default;

  // Other public methods can be declared here if needed
};

#endif // S3LC_H
