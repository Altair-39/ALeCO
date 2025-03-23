#ifndef INTFLOAT
#define INTFLOAT

#include "GenPair.h"
#include <iostream>
#include <vector>

class IntFloat {
private:
  GenPair<int, float> coppia;

public:
  IntFloat(const int a, const float b);

  int pi0() const;
  float pi1() const;

  friend std::ostream &operator<<(std::ostream &os, const IntFloat &obj);
};

#endif // INTFLOAT
