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
#include "date.h"
#include "inventory.h"
#include "items.h"

#include <iostream>
#include <memory>

using namespace inv;

// --- tiny test helper: prints PASS/FAIL and counts failures ---
static int g_failures = 0;
#define CHECK(cond, msg)                                                       \
  do {                                                                         \
    if (cond) {                                                                \
      std::cout << "  PASS: " << (msg) << "\n";                                \
    } else {                                                                   \
      std::cout << "  FAIL: " << (msg) << "   (line " << __LINE__ << ")\n";    \
      ++g_failures;                                                            \
    }                                                                          \
  } while (0)

int main() {
  std::cout << "== Date ==\n";
  {
    Date a = Date::parse("2021-01-01");
    Date b = Date::parse("2024-09-01");
    // EXAMPLE tests (provided):
    CHECK(a < b, "2021-01-01 is before 2024-09-01");
    CHECK(a == Date::parse("2021-01-01"), "equal dates compare equal");
    // [TODO] add tests for: !=, <=, >, >=, and operator<< output format.

    CHECK(a != b, "2021-01-01 does not equal 2024-09-01");

    CHECK(a <= b, "2021-01-01 is less than or equal to 2024-09-01");

    CHECK(b > a, "2024-09-01 is greater than 2021-01-01");

    CHECK(b >= a, "2024-09-01 is greater than or equal to 2021-01-01");

    std::ostringstream oss;
    oss << a;
    CHECK(oss.str() == "2021-01-01", "operator<< formats date correctly");
  }

  std::cout << "== Equipment value ==\n";
  {
    // base 180, purchased 3 full years before kToday (2026-06-01), working.
    Equipment e("E1", "Kbd", "peripherals", 180.0, Date(2023, 2, 10), "Razer",
                "BW", "-", false, false, Date(2099, 1, 1), Date(2099, 1, 1));
    // EXAMPLE test (provided): 180 * (1 - 0.20*3) = 72.00
    CHECK(e.currentValue() > 71.99 && e.currentValue() < 72.01,
          "equipment depreciates to 72.00 after 3 years");
    // [TODO] add tests for: broken -> 0; the 10% floor on very old items;
    //        an item less than a year old keeps full value.

    Equipment broken("E2", "Kbd", "peripherals", 180.0, Date(2023, 2, 10),
                     "Razer", "BW", "-", false, true, Date(2099, 1, 1),
                     Date(2099, 1, 1));
    CHECK(broken.currentValue() < 0.01, "broken equipment has zero value");

    Equipment old("E3", "Kbd", "peripherals", 180.0, Date(2000, 1, 1), "Razer",
                  "BW", "-", false, false, Date(2099, 1, 1), Date(2099, 1, 1));
    CHECK(old.currentValue() > 17.99 && old.currentValue() < 18.01,
          "very old equipment hits 10% floor");

    Equipment new_item("E4", "Kbd", "peripherals", 180.0, Date(2026, 1, 1),
                       "Razer", "BW", "-", false, false, Date(2099, 1, 1),
                       Date(2099, 1, 1));
    CHECK(new_item.currentValue() > 179.99 && new_item.currentValue() < 180.01,
          "equipment less than a year old keeps full value");
  }

  std::cout << "== Consumable value ==\n";
  {
    Consumable c("C1", "Cable", "cables", 8.50, 50, "-", "-");
    // EXAMPLE test (provided): 8.50 * 50 = 425.00
    CHECK(c.currentValue() > 424.99 && c.currentValue() < 425.01,
          "consumable value is unit * 50");
    // [TODO] add tests for other quantities, and that a consumable is not
    // loanable.
    Consumable c2("C2", "Cable", "cables", 8.00, 20, "-", "-");

    CHECK(c2.canLoan() == false, "consumable is not loanable");
    CHECK(c2.currentValue() > 159.99 && c2.currentValue() < 160.01,
          "consumable value is unit * 20");
    Consumable c3("C3", "Pen", "supplies", 1.50, 100, "-", "-");
    CHECK(c3.currentValue() > 149.99 && c3.currentValue() < 150.01,
          "consumable 1.50 * 100 = 150.00");

    Consumable c4("C4", "Tape", "supplies", 5.00, 1, "-", "-");
    CHECK(c4.currentValue() > 4.99 && c4.currentValue() < 5.01,
          "consumable with quantity 1");

    Consumable c5("C5", "Paper", "supplies", 3.00, 0, "-", "-");
    CHECK(c5.currentValue() < 0.01,
          "consumable with zero quantity has zero value");
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

  std::cout << "== Inventory actions ==\n";
  {
    Inventory inv;
    auto *raw = new Equipment("E1", "Kbd", "peripherals", 180.0,
                              Date(2023, 2, 10), "Razer", "BW", "-", false,
                              false, Date(2099, 1, 1), Date(2099, 1, 1));
    Item *ptr = raw;
    inv.add(std::unique_ptr<Item>(raw));

    // loan
    auto rejects = inv.loan({ptr}, "Ethan", Date(2026, 6, 1));
    CHECK(rejects.empty(), "loan accepted the item");
    auto onLoan = inv.select_in_state(State::OnLoan);
    CHECK(onLoan.size() == 1, "item is now OnLoan");

    // return
    rejects = inv.return_items(onLoan);
    CHECK(rejects.empty(), "return accepted the item");
    auto inStock = inv.select_in_state(State::InStock);
    CHECK(inStock.size() == 1, "item is back InStock");

    // sell
    rejects = inv.sell(inStock);
    CHECK(rejects.empty(), "sell accepted the item");
    auto sold = inv.select_in_state(State::Sold);
    CHECK(sold.size() == 1, "item is now Sold");
    CHECK(inv.revenue() > 71.99, "sell added to revenue");
  }

  std::cout << "== Invariants ==\n";
  {
    Inventory inv;

    // consumable cannot be loaned
    auto *c = new Consumable("C1", "Cable", "cables", 8.50, 50, "-", "-");
    Item *cp = c;
    inv.add(std::unique_ptr<Item>(c));
    auto rejects = inv.loan({cp}, "Ethan", Date(2026, 6, 1));
    CHECK(rejects.size() == 1, "consumable cannot be loaned");

    // broken item cannot be loaned
    auto *broken = new Equipment("E1", "Kbd", "peripherals", 180.0,
                                 Date(2023, 2, 10), "Razer", "BW", "-", false,
                                 true, Date(2099, 1, 1), Date(2099, 1, 1));
    Item *bp = broken;
    inv.add(std::unique_ptr<Item>(broken));
    rejects = inv.loan({bp}, "Ethan", Date(2026, 6, 1));
    CHECK(rejects.size() == 1, "broken item cannot be loaned");

    // item on loan cannot be sold
    auto *e = new Equipment("E2", "Mouse", "peripherals", 50.0,
                            Date(2024, 1, 1), "Logitech", "G502", "-", false,
                            false, Date(2099, 1, 1), Date(2099, 1, 1));
    Item *ep = e;
    inv.add(std::unique_ptr<Item>(e));
    inv.loan({ep}, "Ethan", Date(2026, 6, 1));
    rejects = inv.sell({ep});
    CHECK(rejects.size() == 1, "on-loan item cannot be sold");

    // item on loan cannot be surplused
    rejects = inv.surplus({ep});
    CHECK(rejects.size() == 1, "on-loan item cannot be surplused");
  }

  std::cout << "== Selection / grouping / aggregation ==\n";
  {
    Inventory inv;

    auto *e1 = new Equipment("E1", "Kbd", "peripherals", 180.0,
                             Date(2023, 2, 10), "Razer", "BW", "-", false,
                             false, Date(2099, 1, 1), Date(2099, 1, 1));
    auto *e2 = new Equipment("E2", "Mouse", "peripherals", 50.0,
                             Date(2025, 1, 1), "Logitech", "G502", "-", false,
                             false, Date(2099, 1, 1), Date(2099, 1, 1));
    auto *c1 = new Consumable("C1", "Cable", "cables", 8.50, 50, "-", "-");



    inv.add(std::unique_ptr<Item>(e1));
    inv.add(std::unique_ptr<Item>(e2));
    inv.add(std::unique_ptr<Item>(c1));

    // select_all
    auto all = inv.select_all();
    CHECK(all.size() == 3, "select_all returns all 3 items");

    // select_by
    auto razers = inv.select_by("brand", "Razer");
    CHECK(razers.size() == 1, "select_by brand=Razer finds 1");

    auto byId = inv.select_by("id", "E1");
    CHECK(byId.size() == 1, "select_by id=E1 finds 1");

    // select_in_state
    auto inStock = inv.select_in_state(State::InStock);
    CHECK(inStock.size() == 3, "all 3 items are InStock");

    auto onLoan = inv.select_in_state(State::OnLoan);
    CHECK(onLoan.empty(), "no items on loan yet");

    // select_older_than
    auto old = inv.select_older_than(Date(2024, 1, 1));
    CHECK(old.size() == 1, "only E1 is older than 2024-01-01");

    // select_top_by_value
    auto top = inv.select_top_by_value(2);
    CHECK(top.size() == 2, "top 2 returns 2 items");
    CHECK(top[0]->currentValue() >= top[1]->currentValue(),
          "top_by_value is sorted descending");

    // group_by
    auto groups = inv.group_by("category");
    CHECK(groups.count("peripherals") == 1, "peripherals group exists");
    CHECK(groups["peripherals"].size() == 2, "2 items in peripherals");
    CHECK(groups.count("cables") == 1, "cables group exists");
    CHECK(groups["cables"].size() == 1, "1 item in cables");

    // total_value
    double total = inv.total_value(inStock);
    CHECK(total > 0.0, "total_value is positive");

    // value_by_category
    auto valByCat = inv.value_by_category();
    CHECK(valByCat.count("peripherals") == 1, "peripherals has a value");
    CHECK(valByCat.count("cables") == 1, "cables has a value");
    CHECK(valByCat["cables"] > 424.99 && valByCat["cables"] < 425.01,
          "cables value is 8.50 * 50 = 425.00");
  }

  std::cout << "\n";
  if (g_failures == 0)
    std::cout << "All tests passed.\n";
  else
    std::cout << g_failures << " test(s) FAILED.\n";
  return g_failures == 0 ? 0 : 1;
}
