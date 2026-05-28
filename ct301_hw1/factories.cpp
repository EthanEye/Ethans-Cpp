// factories.cpp  [PROVIDED]
#include "factories.h"
#include "items.h"
#include "date.h"
#include "state.h"
#include "parse_error.h"

#include <charconv>
#include <string>

namespace inv {

namespace {

// Strict numeric parsers that throw ParseError (so all input errors share one path).
double to_double(const std::string& s, const ParsedLine& pl) {
    try {
        std::size_t pos = 0;
        double v = std::stod(s, &pos);
        if (pos != s.size()) throw std::invalid_argument("trailing");
        return v;
    } catch (...) {
        throw ParseError("line " + std::to_string(pl.lineNumber) +
                         ": expected a number, got '" + s + "'");
    }
}

int to_int(const std::string& s, const ParsedLine& pl) {
    try {
        std::size_t pos = 0;
        int v = std::stoi(s, &pos);
        if (pos != s.size()) throw std::invalid_argument("trailing");
        return v;
    } catch (...) {
        throw ParseError("line " + std::to_string(pl.lineNumber) +
                         ": expected an integer, got '" + s + "'");
    }
}

bool to_bool(const std::string& s, const ParsedLine& pl) {
    if (s == "true")  return true;
    if (s == "false") return false;
    throw ParseError("line " + std::to_string(pl.lineNumber) +
                     ": expected true/false, got '" + s + "'");
}

void require(const ParsedLine& pl, std::size_t n, const std::string& what) {
    if (pl.args.size() < n)
        throw ParseError("line " + std::to_string(pl.lineNumber) +
                         ": " + what + " needs " + std::to_string(n) +
                         " fields, got " + std::to_string(pl.args.size()));
}

} // namespace

std::unique_ptr<Item> make_item(const ParsedLine& pl) {
    const std::string& type = pl.verb;
    const auto& a = pl.args;

    if (type == "EQUIPMENT") {
        require(pl, 12, "EQUIPMENT");
        // serial name category value date brand model cpu obsolete broken warranty_end support_end
        return std::make_unique<Equipment>(
            a[0], a[1], a[2], to_double(a[3], pl),
            Date::parse(a[4]), a[5], a[6], a[7],
            to_bool(a[8], pl), to_bool(a[9], pl),
            Date::parse(a[10]), Date::parse(a[11]));
    }
    if (type == "CONSUMABLE") {
        require(pl, 7, "CONSUMABLE");
        // id name category value quantity brand model
        return std::make_unique<Consumable>(
            a[0], a[1], a[2], to_double(a[3], pl),
            to_int(a[4], pl), a[5], a[6]);
    }
    if (type == "BORROWED") {
        require(pl, 8, "BORROWED");
        // id name category value lender returnby brand model
        return std::make_unique<Borrowed>(
            a[0], a[1], a[2], to_double(a[3], pl),
            a[4], Date::parse(a[5]), a[6], a[7]);
    }
    throw ParseError("line " + std::to_string(pl.lineNumber) +
                     ": unknown item type '" + type + "'");
}

std::unique_ptr<Command> make_command(const ParsedLine& pl) {
    const std::string& v = pl.verb;
    const auto& a = pl.args;

    if (v == "ADD") {
        require(pl, 1, "ADD");
        ParsedLine itemLine;
        itemLine.verb = a[0];
        itemLine.args.assign(a.begin() + 1, a.end());
        itemLine.lineNumber = pl.lineNumber;
        return std::make_unique<AddCommand>(make_item(itemLine));
    }

    // selection
    if (v == "ALL")          return std::make_unique<SelectAllCommand>();
    if (v == "BY")         { require(pl, 2, "BY");          return std::make_unique<SelectByCommand>(a[0], a[1]); }
    if (v == "IN_STATE")   { require(pl, 1, "IN_STATE");    return std::make_unique<SelectInStateCommand>(state_from_string(a[0])); }
    if (v == "OLDER_THAN") { require(pl, 1, "OLDER_THAN");  return std::make_unique<SelectOlderThanCommand>(Date::parse(a[0])); }
    if (v == "TOP_BY_VALUE"){ require(pl, 1, "TOP_BY_VALUE");return std::make_unique<TopByValueCommand>(static_cast<std::size_t>(to_int(a[0], pl))); }
    if (v == "GROUP_BY")   { require(pl, 1, "GROUP_BY");    return std::make_unique<GroupByCommand>(a[0]); }

    // output
    if (v == "PRINT")        return std::make_unique<PrintCommand>();
    if (v == "REPORT")       return std::make_unique<ReportCommand>();

    // action
    if (v == "SURPLUS")      return std::make_unique<SurplusCommand>();
    if (v == "SELL")         return std::make_unique<SellCommand>();
    if (v == "LOAN")       { require(pl, 2, "LOAN");        return std::make_unique<LoanCommand>(a[0], Date::parse(a[1])); }
    if (v == "RETURN")       return std::make_unique<ReturnCommand>();

    throw ParseError("line " + std::to_string(pl.lineNumber) +
                     ": unknown verb '" + v + "'");
}

} // namespace inv
