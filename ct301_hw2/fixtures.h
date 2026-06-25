#ifndef CT_FIXTURES_H
#define CT_FIXTURES_H
//
// CT 301 - HW#2 (Summer 2026) - fixtures.h  [provided, do not submit]
// ----------------------------------------------------------------------------
// A few fun ct::Vector<int> data sets and some generators, so the driver and
// your own tests have something interesting to compute on. Everything here is
// built FROM your vector, so a fixture only works once the parts of your vector
// it uses are implemented (the initializer-list constructor, push_back, etc.).
//
// Tip: while you are still implementing, test on SMALL vectors first (three or
// four elements you can check by hand). Once those pass, switch to the big
// generators below and watch your buffer grow through many reallocations.
// ----------------------------------------------------------------------------
#include "ctvector.h"

namespace ctlab {

// Men's World Cup titles through 2022, most to fewest:
//   Brazil 5, Germany 4, Italy 4, Argentina 3, France 2, Uruguay 2,
//   England 1, Spain 1.   (Their total is 22, the number of World Cups played.)
inline ct::Vector<int> world_cup_titles() {
    return {5, 4, 4, 3, 2, 2, 1, 1};
}

// Goals scored in each men's World Cup tournament, 1930 .. 2022 (22 numbers).
inline ct::Vector<int> world_cup_goals() {
    return {70, 70, 84, 88, 140, 126, 89, 89, 95, 97, 102,
            146, 132, 115, 141, 171, 161, 147, 145, 171, 169, 172};
}

// Powers of two. This data doubles the same way your vector's capacity doubles.
inline ct::Vector<int> powers_of_two() {
    return {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
}

// Fibonacci numbers.
inline ct::Vector<int> fibonacci() {
    return {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
}

// Generator: 1, 2, 3, ..., n. Great for a big vector that grows many times.
inline ct::Vector<int> make_sequence(int n) {
    ct::Vector<int> v;
    for (int i = 1; i <= n; ++i) v.push_back(i);
    return v;
}

// Generator: the first n perfect squares (1, 4, 9, 16, ...).
inline ct::Vector<int> squares(int n) {
    ct::Vector<int> v;
    for (int i = 1; i <= n; ++i) v.push_back(i * i);
    return v;
}

// Enlarge an existing vector by appending k more powers of two onto its end,
// so you can grow a fixture and recompute on the bigger version.
inline void extend_powers(ct::Vector<int>& v, int k) {
    int next = v.empty() ? 1 : v.back() * 2;
    for (int i = 0; i < k; ++i) {
        v.push_back(next);
        next *= 2;
    }
}

} // namespace ctlab

#endif // CT_FIXTURES_H
