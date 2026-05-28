// item.h  [PROVIDED base contract + operator<< + formatter; STUDENT writes printTo in derived types]
#ifndef ITEM_H
#define ITEM_H

#include "state.h"

#include <format>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>

namespace inv {

// Abstract base for every inventory item.
class Item {
public:
    Item(std::string id, std::string name, std::string category, double baseValue)
        : id_(std::move(id)), name_(std::move(name)),
          category_(std::move(category)), baseValue_(baseValue) {}

    virtual ~Item() = default;

    // ---- pure virtual contract (STUDENT implements per derived type) ----
    virtual bool canLoan() const = 0;                                   // may this kind be loaned?
    virtual bool canSell() const { return true; }                       // may this kind be sold?
    virtual bool canSurplus() const { return true; }                    // may this kind be surplused?
    virtual double currentValue() const = 0;                            // value now (type-specific)
    virtual std::optional<std::string>
        attribute(std::string_view key) const = 0;                      // generic field query
    virtual void printTo(std::ostream& os) const = 0;                   // render hook for operator<<

    // ---- common accessors (PROVIDED) ----
    const std::string& id()       const { return id_; }
    const std::string& name()     const { return name_; }
    const std::string& category() const { return category_; }
    double baseValue()            const { return baseValue_; }
    State  state()                const { return state_; }
    void   setState(State s)            { state_ = s; }

protected:
    // Helper for derived attribute(): answers the fields common to all items.
    std::optional<std::string> baseAttribute(std::string_view key) const {
        if (key == "id")       return id_;
        if (key == "name")     return name_;
        if (key == "category") return category_;
        if (key == "state")    return to_string(state_);
        return std::nullopt;
    }

    std::string id_, name_, category_;
    double baseValue_{0.0};
    State  state_{State::InStock};
};

// [PROVIDED] One non-member operator<< for the whole hierarchy; dispatches to printTo.
inline std::ostream& operator<<(std::ostream& os, const Item& it) {
    it.printTo(os);
    return os;
}

} // namespace inv

// [PROVIDED] formatter bridge so Item works with std::print / std::println too.
template <>
struct std::formatter<inv::Item> : std::formatter<std::string> {
    auto format(const inv::Item& it, std::format_context& ctx) const {
        std::ostringstream os;
        os << it;                                   // reuse operator<< -> printTo
        return std::formatter<std::string>::format(os.str(), ctx);
    }
};

#endif
