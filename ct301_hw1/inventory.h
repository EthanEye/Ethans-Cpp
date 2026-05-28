// inventory.h  [PROVIDED interface; STUDENT implements the bodies, except the four worked examples]
#ifndef INVENTORY_H
#define INVENTORY_H

#include "item.h"
#include "items.h"
#include "date.h"
#include "loan_record.h"
#include "state.h"

#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

namespace inv {

class Inventory {
public:
    // ---- Selection: returns non-owning observers into items the inventory still owns ----

    // Every item, in every state.
    std::vector<Item*> select_all();
    // Items whose attribute(key) equals value (e.g. select_by("brand","Razer"),
    // or select_by("id", serial) for a single item). [WORKED EXAMPLE PROVIDED]
    std::vector<Item*> select_by(std::string_view key, std::string_view value);
    // Items currently in the given state.
    std::vector<Item*> select_in_state(State s);
    // Items with a "date" attribute strictly earlier than d (others are skipped).
    std::vector<Item*> select_older_than(const Date& d);
    // The n most valuable in-stock items, most valuable first.
    std::vector<Item*> select_top_by_value(std::size_t n);
    // Group every item by the value of attribute(key): map from value -> members.
    std::map<std::string, std::vector<Item*>> group_by(std::string_view key);

    // ---- Aggregation ----

    // Sum of currentValue() over the given collection. [WORKED EXAMPLE PROVIDED]
    double total_value(const std::vector<Item*>& items) const;
    // In-stock value grouped by category.
    std::map<std::string, double> value_by_category() const;
    // How many items are in each state.
    std::map<State, std::size_t> count_by_state() const;

    // ---- Action: each returns the subset it could NOT act on (the rejects) ----

    // Take ownership of a new item (added InStock).
    void add(std::unique_ptr<Item> item);
    // Surplus in-stock items. [WORKED EXAMPLE PROVIDED]
    std::vector<Item*> surplus(const std::vector<Item*>& items);
    // Sell in-stock items; records revenue at currentValue().
    std::vector<Item*> sell(const std::vector<Item*>& items);
    // Loan loanable in-stock items to a borrower.
    std::vector<Item*> loan(const std::vector<Item*>& items,
                            std::string_view borrower, const Date& when);
    // Return on-loan items to in-stock.
    std::vector<Item*> return_items(const std::vector<Item*>& items);

    // ---- Output ----

    // Print a collection, one item per line, sorted by id. [WORKED EXAMPLE PROVIDED]
    void print(const std::vector<Item*>& items, std::ostream& os) const;
    // Print a grouping: each key with its members, count, and total value.
    void print(const std::map<std::string, std::vector<Item*>>& groups, std::ostream& os) const;
    // Print an aggregate table (e.g. value-by-category).
    void print(const std::map<std::string, double>& table, std::ostream& os) const;
    // Whole-inventory summary: counts by state, in-stock value, revenue,
    // items on loan with borrowers, surplus count.
    void report(std::ostream& os) const;
    // Final state of every item, sorted by id, one per line.
    void write(std::ostream& os) const;

    double revenue() const { return revenue_; }

private:
    // Items are owned here, partitioned by state. Moving an item between
    // states means std::move-ing its unique_ptr between these vectors.
    std::vector<std::unique_ptr<Item>> inStock_;
    std::vector<std::unique_ptr<Item>> onLoan_;
    std::vector<std::unique_ptr<Item>> sold_;
    std::vector<std::unique_ptr<Item>> surplus_;

    std::vector<LoanRecord> loans_;     // parallel to onLoan_ (by itemId)
    double revenue_{0.0};

    // ---- private helpers (PROVIDED) ----
    // Extract (move out) the item with the given id from a collection; nullptr if absent.
    static std::unique_ptr<Item>
        extract(std::vector<std::unique_ptr<Item>>& from, std::string_view id);
    // Append observers of a collection to out.
    static void gather(const std::vector<std::unique_ptr<Item>>& from,
                       std::vector<Item*>& out);
    // The collection that currently owns observer p, or nullptr.
    std::vector<std::unique_ptr<Item>>* owningCollection(const Item* p);
};

} // namespace inv
#endif
