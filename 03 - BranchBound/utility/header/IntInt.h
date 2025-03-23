#ifndef INTINT
#define INTINT

#include "GenPair.h"
#include <iostream>
#include <vector>

class IntInt {
private:
  GenPair<int, int> coppia;

public:
  IntInt(const int a, const int b);

  int pi0() const;
  int pi1() const;

  friend std::ostream &operator<<(std::ostream &os, const IntInt &obj);
};

#endif // INTINT
