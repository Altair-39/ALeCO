#ifndef GENPAIR_H
#define GENPAIR_H

template <typename T1, typename T2>
class GenPair {
private:
    T1 pi0_value;
    T2 pi1_value;

public:
    GenPair(T1 pi0, T2 pi1) : pi0_value(pi0), pi1_value(pi1) {}

    T1 pi0() const { return pi0_value; }

    T2 pi1() const { return pi1_value; }
};

#endif // GENPAIR_H
