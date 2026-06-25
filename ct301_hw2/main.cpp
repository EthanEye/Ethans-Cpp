//
// CT 301 - HW#2 (Summer 2026) - main.cpp  [provided sandbox, do not submit]
// ----------------------------------------------------------------------------
// A place to play. Build it with the makefile (make main), run ./main, and try
// things out as you implement your vector and your driver functions. The grader
// uses its own main(), so nothing here is graded.
// ----------------------------------------------------------------------------
#include "ctvector.h"
#include "driver.h"
#include "fixtures.h"
#include <iostream>

int main() {
    using namespace ctlab;

    // Start small: a vector you can verify by hand.
    ct::Vector<int> small = {3, 1, 2};
    std::cout << "small total      = " << total(small) << "   (expect 6)\n";
    std::cout << "small largest    = " << largest(small) << "   (expect 3)\n";

    // A fun fixture: World Cup titles {5,4,4,3,2,2,1,1}.
    ct::Vector<int> cups = world_cup_titles();
    std::cout << "titles total     = " << total(cups) << "   (expect 22)\n";
    std::cout << "most by one team = " << largest(cups) << "   (expect 5)\n";
    std::cout << "even title counts= " << count_even(cups) << "   (expect 4)\n";
    std::cout << "anyone with 3?   = " << (contains(cups, 3) ? "yes" : "no") << "\n";

    // Go big: 1..1000 grows the buffer through many reallocations.
    ct::Vector<int> big = make_sequence(1000);
    std::cout << "1..1000 total    = " << total(big) << "   (expect 500500)\n";

    // Enlarge a fixture and recompute.
    ct::Vector<int> p = powers_of_two();
    extend_powers(p, 4);                       // append 2048, 4096, 8192, 16384
    std::cout << "powers total     = " << total(p) << "\n";

    return 0;
}
