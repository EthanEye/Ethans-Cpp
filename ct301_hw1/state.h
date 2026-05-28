// state.h  [PROVIDED]
// The four mutually-exclusive states an item can be in.
#ifndef STATE_H
#define STATE_H

#include <string>
#include <string_view>
#include <stdexcept>

namespace inv {

enum class State { InStock, OnLoan, Sold, Surplus };

inline std::string to_string(State s) {
    switch (s) {
        case State::InStock: return "InStock";
        case State::OnLoan:  return "OnLoan";
        case State::Sold:    return "Sold";
        case State::Surplus: return "Surplus";
    }
    return "Unknown";
}

inline State state_from_string(std::string_view s) {
    if (s == "InStock") return State::InStock;
    if (s == "OnLoan")  return State::OnLoan;
    if (s == "Sold")    return State::Sold;
    if (s == "Surplus") return State::Surplus;
    throw std::invalid_argument("unknown state: " + std::string(s));
}

} // namespace inv
#endif
