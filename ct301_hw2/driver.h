#ifndef CT301_DRIVER_H
#define CT301_DRIVER_H
//
// CT 301 - HW#2 (Summer 2026) - Driver contract
// ----------------------------------------------------------------------------
// FIXED FILE - do not modify. You implement each function below in driver.cpp.
//
// Our grading program supplies its own main(), includes this header, builds
// its own test vectors, and calls your functions. Your signatures must match
// these EXACTLY (names, parameter types, return types, const-qualification).
//
// The point of this piece is to use the vector you built: walk it with its
// iterators, read it with size()/operator[], and lean on the fact that your
// iterators are real random-access iterators (so the standard algorithms work
// on them). A couple of these you write by hand; one lets you use std::sort.
// ----------------------------------------------------------------------------
#include <cstddef>
#include "ctvector.h"

namespace ctlab {

// Return the largest element of v.
// Precondition: v is non-empty. If v is empty, throw std::out_of_range.
// Write this yourself - do NOT call std::max_element.
int largest(const ct::Vector<int>& v);

// Return the sum of all elements of v. The return type is wide enough that the
// provided fixtures will not overflow. A simple loop is fine.
long long total(const ct::Vector<int>& v);

// Return true iff value appears in v. Walk v with its iterators.
bool contains(const ct::Vector<int>& v, int value);

// Return how many elements of v are even.
std::size_t count_even(const ct::Vector<int>& v);

// Return a sorted (ascending) copy of v; the original is left unchanged.
// Hint: copy v, then std::sort(copy.begin(), copy.end()) - this works precisely
// because your iterators are random-access pointers.
ct::Vector<int> sorted_copy(const ct::Vector<int>& v);

} // namespace ctlab

#endif // CT301_DRIVER_H
