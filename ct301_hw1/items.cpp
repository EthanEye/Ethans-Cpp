// items.cpp  [STUDENT implements every function below]
//
// Each stub returns a placeholder and has a "(void)...; // remove when you
// implement this" line just so the project compiles. Replace each body.
#include "items.h"

#include <format>
#include <sstream>
#include <cmath>

namespace inv
{

    // [PROVIDED] A fixed reference "today" so values are deterministic. Use as "now".
    [[maybe_unused]] static const Date kToday{2026, 6, 1};

    // [PROVIDED] format a Date as YYYY-MM-DD for printing/attributes.
    [[maybe_unused]] static std::string dstr(const Date &d)
    {
        return std::format("{:04d}-{:02d}-{:02d}", d.year(), d.month(), d.day());
    }

    // ============================ Equipment ============================
    // [TODO] If broken_, value is 0.0. Otherwise depreciate 20% of the base value
    // (baseValue()) per FULL year since purchased_ (use kToday as "now"), with a
    // floor of 10% of the base value. The obsolete_ flag and the warranty/support
    // dates do NOT affect value.
    double Equipment::currentValue() const
    {
        if (broken_)
            return 0.0;
        int yearsOwned = kToday.year() - purchased_.year();
        double depreciated = baseValue() - (baseValue() * 0.20 * yearsOwned);
        return std::max(baseValue() * 0.10, depreciated);
    }

    // [TODO] true when kToday is past warrantyEnd_ (no return path).
    bool Equipment::noRMA() const
    {
        return kToday > warrantyEnd_;
    }

    // [TODO] true when the item is broken_ AND noRMA().
    bool Equipment::surplusCandidate() const
    {
        return broken_ && noRMA();
    }

    // [TODO] Answer these keys: brand, model, cpu, date, obsolete, broken,
    // warranty_end, support_end, norma, surplus_candidate. For bools return
    // "true"/"false". For anything else, return baseAttribute(key).
    std::optional<std::string> Equipment::attribute(std::string_view key) const
    {
        if (key == "brand")
            return brand_;
        if (key == "model")
            return model_;
        if (key == "cpu")
            return cpu_;
        if (key == "date")
            return dstr(purchased_);
        if (key == "obsolete")
            return obsolete_ ? "true" : "false";
        if (key == "broken")
            return broken_ ? "true" : "false";
        if (key == "warranty_end")
            return dstr(warrantyEnd_);
        if (key == "support_end")
            return dstr(supportEnd_);
        if (key == "norma")
            return noRMA() ? "true" : "false";
        if (key == "surplus_candidate")
            return surplusCandidate() ? "true" : "false";
        return baseAttribute(key);
    }

    // [TODO] Print one line in the exact sample-output format for Equipment.
    void Equipment::printTo(std::ostream &os) const
    {
        os << id() << " EQUIPMENT " << name() << " " << category() << " "
           << brand_ << " " << model_
           << " cpu=" << cpu_
           << " purchased=" << dstr(purchased_)
           << std::format(" value={:.2f}", currentValue())
           << " obsolete=" << (obsolete_ ? "true" : "false")
           << " broken=" << (broken_ ? "true" : "false")
           << " warranty=" << dstr(warrantyEnd_)
           << " support=" << dstr(supportEnd_)
           << " " << to_string(state());
    }

    // ============================ Consumable ===========================
    // [TODO] value = base value (the per-unit value) * quantity_.
    double Consumable::currentValue() const
    {
        return baseValue() * quantity_;
    }

    // [TODO] Answer: brand, model, quantity. Else baseAttribute(key).
    std::optional<std::string> Consumable::attribute(std::string_view key) const
    {
        if (key == "brand")
            return brand_;
        if (key == "model")
            return model_;
        if (key == "quantity")
            return std::to_string(quantity_);
        return baseAttribute(key);
    }

    // [TODO] Print one line in the exact sample-output format for Consumable.
    void Consumable::printTo(std::ostream &os) const
    {
        os << id() << " CONSUMABLE " << name() << " " << category() << " "
           << brand_ << " " << model_
           << " qty=" << quantity_
           << std::format(" value={:.2f}", currentValue())
           << " " << to_string(state());
    }

    // ============================ Borrowed =============================
    // [TODO] Answer: brand, model, lender, returnby. Else baseAttribute(key).
    std::optional<std::string> Borrowed::attribute(std::string_view key) const
    {
        if (key == "brand")
            return brand_;
        if (key == "model")
            return model_;
        if (key == "lender")
            return lender_;
        if (key == "returnby")
            return dstr(returnBy_);
        return baseAttribute(key);
    }

    // [TODO] Print one line in the exact sample-output format for Borrowed.
    void Borrowed::printTo(std::ostream& os) const {
    os << id() << " BORROWED " << name() << " " << category() << " "
       << brand_ << " " << model_
       << " lender=" << lender_
       << " returnby=" << dstr(returnBy_)
       << std::format(" value={:.2f}", currentValue())
       << " " << to_string(state());
}

} // namespace inv
