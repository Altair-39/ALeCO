#include "header/ArrBoolInt.h"

ArrBoolInt::ArrBoolInt(const std::vector<bool> &a, int b) : coppia(a, b) {}

std::vector<bool> ArrBoolInt::pi0() const { return coppia.pi0(); }

int ArrBoolInt::pi1() const { return coppia.pi1(); }

std::ostream &operator<<(std::ostream &os, const ArrBoolInt &obj) {
  size_t i = 0;
  os << "(";
  const auto &boolVec = obj.pi0();
  os << "[";
  while (i < boolVec.size()) {
    os << (boolVec[i] ? "true" : "false");
    if (i < boolVec.size() - 1)
      os << ", ";
    i++;
  }
  os << "], " << obj.pi1() << ")";
  return os;
}
