#include "header/ArrIntFloat.h"

ArrIntFloat::ArrIntFloat(const std::vector<int> &a, float b) : coppia(a, b) {}

std::vector<int> ArrIntFloat::pi0() const { return coppia.pi0(); }

float ArrIntFloat::pi1() const { return coppia.pi1(); }

std::ostream &operator<<(std::ostream &os, const ArrIntFloat &obj) {
  size_t i = 0;
  os << "(";
  const auto &intVec = obj.pi0();
  os << "[";
  while (i < intVec.size()) {
    os << (intVec[i] ? "true" : "false");
    if (i < intVec.size() - 1)
      os << ", ";
    i++;
  }
  os << "], " << obj.pi1() << ")";
  return os;
}
