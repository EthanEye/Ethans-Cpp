// inventory.cpp
// The three private helpers and ONE worked example (surplus) are provided to
// show the patterns. Everything marked [TODO] is yours to implement. Each stub
// currently returns an empty/default result and has a "(void)...; // remove
// when you implement this" line just to compile cleanly -- delete that line
// when you write the real body.
#include "inventory.h"

#include <algorithm>
#include <format>
#include <numeric>

namespace inv {

// ===================== private helpers (PROVIDED) =====================
// extract: take an item OUT of a list and hand you ownership (the unique_ptr).
//          After this, only the returned unique_ptr keeps the item alive -- if
//          you don't move it into another list, the item is destroyed.
// gather:  copy borrowed (non-owning) Item* pointers of a list into 'out'. The
//          list keeps ownership; you are only borrowing pointers to look.
// owningCollection: find which of the four lists currently owns a given item.

std::unique_ptr<Item>
Inventory::extract(std::vector<std::unique_ptr<Item>>& from, std::string_view id) {
    auto it = std::find_if(from.begin(), from.end(),
                           [&](const std::unique_ptr<Item>& p) { return p->id() == id; });
    if (it == from.end()) return nullptr;
    std::unique_ptr<Item> out = std::move(*it);   // move ownership out
    from.erase(it);
    return out;
}

void Inventory::gather(const std::vector<std::unique_ptr<Item>>& from,
                       std::vector<Item*>& out) {
    for (const std::unique_ptr<Item>& p : from) out.push_back(p.get());
}

std::vector<std::unique_ptr<Item>>* Inventory::owningCollection(const Item* p) {
    auto holds = [&](std::vector<std::unique_ptr<Item>>& v) {
        return std::any_of(v.begin(), v.end(),
                           [&](const std::unique_ptr<Item>& u) { return u.get() == p; });
    };
    if (holds(inStock_)) return &inStock_;
    if (holds(onLoan_))  return &onLoan_;
    if (holds(sold_))    return &sold_;
    if (holds(surplus_)) return &surplus_;
    return nullptr;
}

// ===================== Selection =====================

// [TODO] Return borrowed (non-owning) pointers to EVERY item, across all four
// lists (inStock_, onLoan_, sold_, surplus_). The helper gather() appends a
// list's pointers into an output vector; call it once per list.
std::vector<Item*> Inventory::select_all() {
    return {};
}

// [TODO] Walk every item, ask each one for the given attribute (p->attribute(key)),
// and keep the ones whose value equals 'value'. Return those borrowed pointers.
// This is the pattern that select_in_state / select_older_than also follow.
std::vector<Item*> Inventory::select_by(std::string_view key, std::string_view value) {
    (void)key; (void)value;  // remove when you implement this
    return {};
}

// [TODO] Return borrowed pointers to all items currently in the given state.
// (Hint: gather() the one matching list.)
std::vector<Item*> Inventory::select_in_state(State s) {
    (void)s;  // remove when you implement this
    return {};
}

// [TODO] Return items whose "date" attribute is strictly earlier than d. Items
// that have no "date" attribute do not qualify. (Hint: Date::parse on the
// attribute string, then compare with operator<.)
std::vector<Item*> Inventory::select_older_than(const Date& d) {
    (void)d;  // remove when you implement this
    return {};
}

// [TODO] Return the n most valuable IN-STOCK items, highest value first. If
// fewer than n are in stock, return all of them. (Hint: gather inStock_, sort
// by currentValue() descending, then keep at most n.)
std::vector<Item*> Inventory::select_top_by_value(std::size_t n) {
    (void)n;  // remove when you implement this
    return {};
}

// [TODO] Group ALL items by the given attribute. The map key is the attribute
// value; items that lack the attribute go under the key "(none)". Return the map.
std::map<std::string, std::vector<Item*>> Inventory::group_by(std::string_view key) {
    (void)key;  // remove when you implement this
    return {};
}

// ===================== Aggregation =====================

// [TODO] Return the sum of currentValue() over the given items. (Hint: a simple
// loop, or std::accumulate.)
double Inventory::total_value(const std::vector<Item*>& items) const {
    (void)items;  // remove when you implement this
    return 0.0;
}

// [TODO] Sum currentValue() of IN-STOCK items, grouped by category. Return a
// map<category, total>.
std::map<std::string, double> Inventory::value_by_category() const {
    return {};
}

// [TODO] Return how many items are in each state, as a map<State, count>.
// (All four states should appear, even if their count is 0.)
std::map<State, std::size_t> Inventory::count_by_state() const {
    return {};
}

// ===================== Action =====================

// [TODO] Take ownership of a new item and store it in-stock. Set its state to
// InStock, then move it into inStock_. (Hint: inStock_.push_back(std::move(item)).)
void Inventory::add(std::unique_ptr<Item> item) {
    (void)item;  // remove when you implement this
}

// [WORKED EXAMPLE] The action pattern, study this; sell/loan/return follow it.
// An item can be surplused only if it is InStock AND its type allows it
// (canSurplus()). Anything else is a "reject". For each accepted item: extract
// the owning unique_ptr out of inStock_, update its state, and move it into
// surplus_. Return the list of rejects.
std::vector<Item*> Inventory::surplus(const std::vector<Item*>& items) {
    std::vector<Item*> rejects;
    for (Item* p : items) {
        if (p->state() != State::InStock || !p->canSurplus()) {
            rejects.push_back(p);
            continue;
        }
        std::unique_ptr<Item> owned = extract(inStock_, p->id());
        if (!owned) { rejects.push_back(p); continue; }
        owned->setState(State::Surplus);
        surplus_.push_back(std::move(owned));    // ownership moves to surplus_
    }
    return rejects;
}

// [TODO] Like surplus(), but: an item must be InStock AND canSell(). For each
// accepted item, add its currentValue() to revenue_, set state to Sold, and
// move it into sold_. Return the rejects.
std::vector<Item*> Inventory::sell(const std::vector<Item*>& items) {
    (void)items;  // remove when you implement this
    return {};
}

// [TODO] An item must be InStock AND canLoan(). For each accepted item, set
// state to OnLoan, move it into onLoan_, and record a
// LoanRecord{ id, borrower, when } in loans_. Return the rejects.
std::vector<Item*> Inventory::loan(const std::vector<Item*>& items,
                                   std::string_view borrower, const Date& when) {
    (void)items; (void)borrower; (void)when;  // remove when you implement this
    return {};
}

// [TODO] An item must currently be OnLoan. For each accepted item, set state
// back to InStock, move it into inStock_, and remove its LoanRecord from loans_.
// Return the rejects.
std::vector<Item*> Inventory::return_items(const std::vector<Item*>& items) {
    (void)items;  // remove when you implement this
    return {};
}

// ===================== Output =====================

// [TODO] Sort the given items by id (ascending), then print each one to os,
// one per line, using operator<< (which calls the item's printTo). Do not
// modify the inventory. (Hint: copy the vector, std::sort by id(), then loop.)
void Inventory::print(const std::vector<Item*>& items, std::ostream& os) const {
    (void)items; (void)os;  // remove when you implement this
}

// [TODO] For each group (in map order): print a header line
//   "key (count=N, value=V.VV):"
// then each item in the group, indented two spaces, sorted by id. The value is
// the total_value of that group's items, to 2 decimals. See the sample output.
void Inventory::print(const std::map<std::string, std::vector<Item*>>& groups,
                      std::ostream& os) const {
    (void)groups; (void)os;  // remove when you implement this
}

// [TODO] Print each entry as "key: value\n", with value to 2 decimals, in map
// order. See the sample output.
void Inventory::print(const std::map<std::string, double>& table, std::ostream& os) const {
    (void)table; (void)os;  // remove when you implement this
}

// [TODO] Print the inventory report. Match the sample output EXACTLY:
//   === Inventory Report ===
//   InStock: <n>
//   OnLoan: <n>
//   Sold: <n>
//   Surplus: <n>
//   In-stock value: <sum of currentValue() of in-stock items, 2 decimals>
//   Revenue: <revenue_, 2 decimals>
//   On loan:
//     <id> -> <borrower> (<date>)        (one line per loan, sorted by id)
//   Surplus count: <n>
void Inventory::report(std::ostream& os) const {
    (void)os;  // remove when you implement this
}

// [TODO] Write EVERY item (all four states), sorted by id, one per line via
// operator<<, to os. This is what gets saved to the output file.
void Inventory::write(std::ostream& os) const {
    (void)os;  // remove when you implement this
}

} // namespace inv
