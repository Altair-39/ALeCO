#ifndef ARRBOOLINT_H
#define ARRBOOLINT_H

#include "GenPair.h"
#include <iostream>
#include <vector>

class ArrBoolInt {
private:
  GenPair<std::vector<bool>, int> coppia;

public:
  ArrBoolInt(const std::vector<bool> &a, int b);

  std::vector<bool> pi0() const;
  int pi1() const;

  friend std::ostream &operator<<(std::ostream &os, const ArrBoolInt &obj);
};

#endif // ARRBOOLINT_H
