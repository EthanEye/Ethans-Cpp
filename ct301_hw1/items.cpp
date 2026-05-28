// items.cpp  [STUDENT implements every function below]
//
// Each stub returns a placeholder and has a "(void)...; // remove when you
// implement this" line just so the project compiles. Replace each body.
#include "items.h"

#include <format>
#include <sstream>

namespace inv {

// [PROVIDED] A fixed reference "today" so values are deterministic. Use as "now".
[[maybe_unused]] static const Date kToday{2026, 6, 1};

// [PROVIDED] format a Date as YYYY-MM-DD for printing/attributes.
[[maybe_unused]] static std::string dstr(const Date& d) {
    return std::format("{:04d}-{:02d}-{:02d}", d.year(), d.month(), d.day());
}

// ============================ Equipment ============================
// [TODO] If broken_, value is 0.0. Otherwise depreciate 20% of the base value
// (baseValue()) per FULL year since purchased_ (use kToday as "now"), with a
// floor of 10% of the base value. The obsolete_ flag and the warranty/support
// dates do NOT affect value.
double Equipment::currentValue() const {
    return 0.0;
}

// [TODO] true when kToday is past warrantyEnd_ (no return path).
bool Equipment::noRMA() const {
    return false;
}

// [TODO] true when the item is broken_ AND noRMA().
bool Equipment::surplusCandidate() const {
    return false;
}

// [TODO] Answer these keys: brand, model, cpu, date, obsolete, broken,
// warranty_end, support_end, norma, surplus_candidate. For bools return
// "true"/"false". For anything else, return baseAttribute(key).
std::optional<std::string> Equipment::attribute(std::string_view key) const {
    (void)key;  // remove when you implement this
    return std::nullopt;
}

// [TODO] Print one line in the exact sample-output format for Equipment.
void Equipment::printTo(std::ostream& os) const {
    (void)os;  // remove when you implement this
}

// ============================ Consumable ===========================
// [TODO] value = base value (the per-unit value) * quantity_.
double Consumable::currentValue() const {
    return 0.0;
}

// [TODO] Answer: brand, model, quantity. Else baseAttribute(key).
std::optional<std::string> Consumable::attribute(std::string_view key) const {
    (void)key;  // remove when you implement this
    return std::nullopt;
}

// [TODO] Print one line in the exact sample-output format for Consumable.
void Consumable::printTo(std::ostream& os) const {
    (void)os;  // remove when you implement this
}

// ============================ Borrowed =============================
// [TODO] Answer: brand, model, lender, returnby. Else baseAttribute(key).
std::optional<std::string> Borrowed::attribute(std::string_view key) const {
    (void)key;  // remove when you implement this
    return std::nullopt;
}

// [TODO] Print one line in the exact sample-output format for Borrowed.
void Borrowed::printTo(std::ostream& os) const {
    (void)os;  // remove when you implement this
}

} // namespace inv
