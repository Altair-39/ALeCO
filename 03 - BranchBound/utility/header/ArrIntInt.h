#ifndef ARRINTINT_H
#define ARRINTINT_H

#include "GenPair.h"
#include <iostream>
#include <vector>

class ArrIntInt {
private:
  GenPair<std::vector<int>, int> coppia;

public:
  ArrIntInt(const std::vector<int> &a, int b);

  std::vector<int> pi0() const;
  int pi1() const;

  friend std::ostream &operator<<(std::ostream &os, const ArrIntInt &obj);
};

#endif // ARRINTINT_H
