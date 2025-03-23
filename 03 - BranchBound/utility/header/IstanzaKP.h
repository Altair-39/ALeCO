
#ifndef ISTANZAKP_H
#define ISTANZAKP_H

#include "ArrIntArrFloat.h"
#include <iostream>

class IstanzaKP {
private:
  ArrIntArrFloat pairData;  
  int c;  

public:
  IstanzaKP(const std::vector<int> &w, const std::vector<float> &p, int c);

  std::vector<int> getW() const;
  std::vector<float> getP() const;
  int getC() const; 

  friend std::ostream &operator<<(std::ostream &os, const IstanzaKP &obj);
};

#endif  // ISTANZAKP_H

