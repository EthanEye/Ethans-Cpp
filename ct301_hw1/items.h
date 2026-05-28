// items.h  [STUDENT implements; declarations shown as the provided interface]
#ifndef ITEMS_H
#define ITEMS_H

#include "item.h"
#include "date.h"

#include <optional>
#include <string>
#include <string_view>

namespace inv {

// Durable hardware the lab owns. Loanable/sellable/surplusable.
// Depreciates over time and carries independent condition flags.
class Equipment : public Item {
public:
    Equipment(std::string id, std::string name, std::string category, double value,
              Date purchased, std::string brand, std::string model, std::string cpu,
              bool obsolete, bool broken, Date warrantyEnd, Date supportEnd)
        : Item(std::move(id), std::move(name), std::move(category), value),
          purchased_(purchased), brand_(std::move(brand)),
          model_(std::move(model)), cpu_(std::move(cpu)),
          obsolete_(obsolete), broken_(broken),
          warrantyEnd_(warrantyEnd), supportEnd_(supportEnd) {}

    bool canLoan() const override { return !broken_; }   // a broken unit cannot be loaned
    double currentValue() const override;                // 0 if broken, else depreciated
    std::optional<std::string> attribute(std::string_view key) const override;
    void printTo(std::ostream& os) const override;

    // computed conditions
    bool noRMA() const;              // past warranty_end -> no return path
    bool surplusCandidate() const;   // broken AND noRMA

private:
    Date purchased_;
    std::string brand_, model_, cpu_;
    bool obsolete_{false}, broken_{false};
    Date warrantyEnd_{}, supportEnd_{};
};

// Used up; tracked as a bulk lot with a quantity. Not loanable.
class Consumable : public Item {
public:
    Consumable(std::string id, std::string name, std::string category, double value,
               int quantity, std::string brand, std::string model)
        : Item(std::move(id), std::move(name), std::move(category), value),
          quantity_(quantity), brand_(std::move(brand)), model_(std::move(model)) {}

    bool canLoan() const override { return false; }
    double currentValue() const override;
    std::optional<std::string> attribute(std::string_view key) const override;
    void printTo(std::ostream& os) const override;

private:
    int quantity_{0};
    std::string brand_, model_;
};

// Hardware loaned TO the lab by someone else. Not ours, so it cannot be
// loaned out, sold, or surplused; it can only be returned to its lender.
class Borrowed : public Item {
public:
    Borrowed(std::string id, std::string name, std::string category, double value,
             std::string lender, Date returnBy, std::string brand, std::string model)
        : Item(std::move(id), std::move(name), std::move(category), value),
          lender_(std::move(lender)), returnBy_(returnBy),
          brand_(std::move(brand)), model_(std::move(model)) {}

    bool canLoan() const override { return false; }     // not ours to lend
    bool canSell() const override { return false; }     // not ours to sell
    bool canSurplus() const override { return false; }  // not ours to surplus
    double currentValue() const override { return 0.0; }  // no asset value to the lab
    std::optional<std::string> attribute(std::string_view key) const override;
    void printTo(std::ostream& os) const override;

    const std::string& lender() const { return lender_; }

private:
    std::string lender_;
    Date returnBy_;
    std::string brand_, model_;
};

} // namespace inv
#endif
