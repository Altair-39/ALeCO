#include "header/ArrIntArrFloat.h"

ArrIntArrFloat::ArrIntArrFloat(const std::vector<int>& a, const std::vector<float>& b) : coppia(a, b) {}

std::vector<int> ArrIntArrFloat::pi0() const {
    return coppia.pi0();
}

std::vector<float> ArrIntArrFloat::pi1() const {
    return coppia.pi1();
}

std::ostream& operator<<(std::ostream& os, const ArrIntArrFloat& obj) {
    size_t i = 0;
    os << "(";
    
    const auto& intVec = obj.pi0();
    os << "[";
    while (i < intVec.size()) {
        os << intVec[i];
        if (i < intVec.size() - 1) os << ", ";
        i++;
    }
    os << "], ";
    
    const auto& floatVec = obj.pi1();
    os << "[";
    i = 0;
    while (i < floatVec.size()) {
        os << floatVec[i];
        if (i < floatVec.size() - 1) os << ", ";
        i++;
    }
    
    os << ")";
    return os;
}
