#ifndef ARRINTARRFLOAT_H
#define ARRINTARRFLOAT_H

#include "GenPair.h"
#include <iostream>
#include <vector>

class ArrIntArrFloat {
private:
  GenPair<std::vector<int>, std::vector<float>> coppia;

public:
  ArrIntArrFloat(const std::vector<int> &a, const std::vector<float> &b);

  std::vector<int> pi0() const;
  std::vector<float> pi1() const;

  friend std::ostream &operator<<(std::ostream &os, const ArrIntArrFloat &obj);
};

#endif // ARRINTARRFLOAT_H
