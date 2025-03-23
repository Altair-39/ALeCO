#include "header/IstanzaKP.h"

IstanzaKP::IstanzaKP(const std::vector<int> &w, const std::vector<float> &p,
                     int c)
    : pairData(w, p), c(c) {}

std::vector<int> IstanzaKP::getW() const { return pairData.pi0(); }

std::vector<float> IstanzaKP::getP() const { return pairData.pi1(); }

int IstanzaKP::getC() const { return c; }

std::ostream &operator<<(std::ostream &os, const IstanzaKP &obj) {
  os << "(";

  const auto &wVec = obj.getW();
  os << "[";
  for (size_t i = 0; i < wVec.size(); ++i) {
    os << wVec[i];
    if (i < wVec.size() - 1)
      os << ", ";
  }
  os << "], ";

  const auto &pVec = obj.getP();
  os << "[";
  for (size_t i = 0; i < pVec.size(); ++i) {
    os << pVec[i];
    if (i < pVec.size() - 1)
      os << ", ";
  }
  os << "], ";

  os << obj.getC() << ")";

  return os;
}
