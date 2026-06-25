//
// CT 301 - HW#2 (Summer 2026) - driver.cpp  [you implement and SUBMIT this]
// ----------------------------------------------------------------------------
// Implement each function declared in driver.h. The grader supplies its own
// main() and calls these on its own ct::Vector<int> values, so keep the
// signatures exactly as in driver.h.
//
// total() is done for you as a worked example: walk the vector with a range-for
// (which uses your begin()/end()) and accumulate. The others follow the same
// idea. Write largest, contains, and count_even by hand; sorted_copy may use
// std::sort because your iterators are real random-access iterators.
// ----------------------------------------------------------------------------
#include "driver.h"
#include <algorithm>   // std::sort (allowed in sorted_copy)

// Warning suppressor: lets the unfinished stubs keep named parameters.
// Delete it once every function is implemented.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

namespace ctlab {

// WORKED EXAMPLE.
long long total(const ct::Vector<int>& v) {
    long long sum = 0;
    for (int x : v) sum += x;
    return sum;
}

int largest(const ct::Vector<int>& v) {
    // TODO: return the biggest element. Throw std::out_of_range if v is empty.
    //       Write the loop yourself; do not call std::max_element.
    return 0;
}

bool contains(const ct::Vector<int>& v, int value) {
    // TODO: return true if value appears in v.
    return false;
}

std::size_t count_even(const ct::Vector<int>& v) {
    // TODO: return how many elements are even.
    return 0;
}

ct::Vector<int> sorted_copy(const ct::Vector<int>& v) {
    // TODO: return a sorted (ascending) copy; leave v unchanged.
    //       Hint: copy v, then std::sort(copy.begin(), copy.end()).
    return {};
}

} // namespace ctlab

#pragma GCC diagnostic pop
