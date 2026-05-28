// date.cpp  [STUDENT implements the operators; Date::parse is PROVIDED]
#include "date.h"
#include "parse_error.h"

#include <format>
#include <string>

namespace inv {

// [PROVIDED] Robust parse with full validation. Do not change.
Date Date::parse(std::string_view s) {
    if (s.size() != 10 || s[4] != '-' || s[7] != '-')
        throw ParseError("bad date format (need YYYY-MM-DD): " + std::string(s));

    auto digits = [&](std::size_t a, std::size_t b) -> int {
        int v = 0;
        for (std::size_t i = a; i < b; ++i) {
            char c = s[i];
            if (c < '0' || c > '9')
                throw ParseError("non-numeric date field: " + std::string(s));
            v = v * 10 + (c - '0');
        }
        return v;
    };

    int y = digits(0, 4);
    int m = digits(5, 7);
    int d = digits(8, 10);

    if (m < 1 || m > 12) throw ParseError("month out of range: " + std::string(s));
    if (d < 1 || d > 31) throw ParseError("day out of range: " + std::string(s));

    return Date(y, m, d);
}

// ===================== YOUR CODE BELOW =====================
// Compare dates by (year, then month, then day).
// Members available: y_, m_, d_  (and accessors year(), month(), day()).
// Each stub has a "(void)o; // remove when you implement this" line and returns
// a placeholder; replace the whole body with the real comparison.

// [TODO] true when both dates are the same day.
bool Date::operator==(const Date& o) const { (void)o; /* remove when you implement this */ return false; }

// [TODO] true when the dates differ (hint: !(*this == o)).
bool Date::operator!=(const Date& o) const { (void)o; /* remove when you implement this */ return false; }

// [TODO] true when *this is strictly before o (compare year, then month, then day).
bool Date::operator<(const Date& o)  const { (void)o; /* remove when you implement this */ return false; }

// [TODO] the remaining three, in terms of < and ==.
bool Date::operator<=(const Date& o) const { (void)o; /* remove when you implement this */ return false; }
bool Date::operator>(const Date& o)  const { (void)o; /* remove when you implement this */ return false; }
bool Date::operator>=(const Date& o) const { (void)o; /* remove when you implement this */ return false; }

// [TODO] print as YYYY-MM-DD, zero-padded. Hint:
//   os << std::format("{:04d}-{:02d}-{:02d}", d.year(), d.month(), d.day());
std::ostream& operator<<(std::ostream& os, const Date& d) {
    (void)d;  // remove when you implement this
    return os;
}

} // namespace inv
