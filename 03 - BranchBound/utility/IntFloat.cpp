#include "header/IntFloat.h"

IntFloat::IntFloat(const int a, const float b) : coppia(a, b) {}

int IntFloat::pi0() const { return coppia.pi0(); }

float IntFloat::pi1() const { return coppia.pi1(); }

std::ostream &operator<<(std::ostream &os, const IntFloat &obj) {
  os << "(" << obj.pi0() << ", " << obj.pi1() << ")";
  return os;
}
