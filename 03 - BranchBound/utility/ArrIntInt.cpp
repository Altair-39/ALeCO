#include "header/ArrIntInt.h"

ArrIntInt::ArrIntInt(const std::vector<int> &a, int b) : coppia(a, b) {}

std::vector<int> ArrIntInt::pi0() const { return coppia.pi0(); }

int ArrIntInt::pi1() const { return coppia.pi1(); }

std::ostream &operator<<(std::ostream &os, const ArrIntInt &obj) {
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
