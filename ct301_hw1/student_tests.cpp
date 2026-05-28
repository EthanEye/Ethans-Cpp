// student_tests.cpp  -- YOUR test harness.
//
// Testing is part of this assignment. A few example tests are written for you
// below to show the pattern; you must add more to cover the rest of your code.
//
// Build and run (from the project root):
//   g++ -std=c++26 -Wall -Wextra -Wpedantic -g student_tests.cpp date.cpp
//       items.cpp inventory.cpp command.cpp tokenizer.cpp file_reader.cpp
//       factories.cpp -o student_tests
//   ./student_tests
//
// (Use -std=c++23 if your compiler does not yet accept c++26.)
#include "inventory.h"
#include "items.h"
#include "date.h"

#include <iostream>
#include <memory>

using namespace inv;

// --- tiny test helper: prints PASS/FAIL and counts failures ---
static int g_failures = 0;
#define CHECK(cond, msg)                                                  \
    do {                                                                  \
        if (cond) {                                                       \
            std::cout << "  PASS: " << (msg) << "\n";                     \
        } else {                                                          \
            std::cout << "  FAIL: " << (msg) << "   (line " << __LINE__   \
                      << ")\n";                                           \
            ++g_failures;                                                 \
        }                                                                 \
    } while (0)

int main() {
    std::cout << "== Date ==\n";
    {
        Date a = Date::parse("2021-01-01");
        Date b = Date::parse("2024-09-01");
        // EXAMPLE tests (provided):
        CHECK(a < b,  "2021-01-01 is before 2024-09-01");
        CHECK(a == Date::parse("2021-01-01"), "equal dates compare equal");
        // [TODO] add tests for: !=, <=, >, >=, and operator<< output format.
    }

    std::cout << "== Equipment value ==\n";
    {
        // base 180, purchased 3 full years before kToday (2026-06-01), working.
        Equipment e("E1", "Kbd", "peripherals", 180.0, Date(2023, 2, 10),
                    "Razer", "BW", "-", false, false,
                    Date(2099, 1, 1), Date(2099, 1, 1));
        // EXAMPLE test (provided): 180 * (1 - 0.20*3) = 72.00
        CHECK(e.currentValue() > 71.99 && e.currentValue() < 72.01,
              "equipment depreciates to 72.00 after 3 years");
        // [TODO] add tests for: broken -> 0; the 10% floor on very old items;
        //        an item less than a year old keeps full value.
    }

    std::cout << "== Consumable value ==\n";
    {
        Consumable c("C1", "Cable", "cables", 8.50, 50, "-", "-");
        // EXAMPLE test (provided): 8.50 * 50 = 425.00
        CHECK(c.currentValue() > 424.99 && c.currentValue() < 425.01,
              "consumable value is unit * quantity");
        // [TODO] add tests for other quantities, and that a consumable is not loanable.
    }

    // [TODO] Add whole sections of your own, for example:
    //   == Inventory actions ==
    //     - loan moves an item to OnLoan and records the borrower
    //     - sell adds to revenue and moves the item to Sold
    //     - return moves an OnLoan item back to InStock
    //   == Invariants (things that must be REFUSED) ==
    //     - a Consumable cannot be loaned
    //     - a broken item cannot be loaned
    //     - an item on loan cannot be sold or surplused
    //     - a Borrowed item cannot be loaned, sold, or surplused
    //   == Selection / grouping / aggregation ==
    //     - select_by, select_in_state, select_older_than, top_by_value
    //     - group_by buckets correctly; total_value / value_by_category sums
    //
    // Construct items, call the Inventory methods, and CHECK the results.

    std::cout << "\n";
    if (g_failures == 0) std::cout << "All tests passed.\n";
    else                 std::cout << g_failures << " test(s) FAILED.\n";
    return g_failures == 0 ? 0 : 1;
}
