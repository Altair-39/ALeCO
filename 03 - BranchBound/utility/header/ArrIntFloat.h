#ifndef ARRINTFLOAT_H
#define ARRINTFLOAT_H

#include "GenPair.h"
#include <iostream>
#include <vector>

class ArrIntFloat {
private:
  GenPair<std::vector<int>, float> coppia;

public:
  ArrIntFloat(const std::vector<int> &a, float b);

  std::vector<int> pi0() const;
  float pi1() const;

  friend std::ostream &operator<<(std::ostream &os, const ArrIntFloat &obj);
};

#endif // ARRINTFLOAT_H
