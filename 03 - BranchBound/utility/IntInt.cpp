#include "header/IntInt.h"

IntInt::IntInt(const int a, const int b) : coppia(a, b) {}

int IntInt::pi0() const { return coppia.pi0(); }

int IntInt::pi1() const { return coppia.pi1(); }

std::ostream &operator<<(std::ostream &os, const IntInt &obj) {
  os << "(" << obj.pi0() << ", " << obj.pi1() << ")";
  return os;
}
