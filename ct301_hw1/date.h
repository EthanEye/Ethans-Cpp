// date.h  [STUDENT implements the operators; parse provided]
// A small calendar date value type. Teaches operator overloading.
#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
#include <string_view>

namespace inv {

class Date {
public:
    Date() = default;
    Date(int y, int m, int d) : y_(y), m_(m), d_(d) {}

    // [PROVIDED] Parse "YYYY-MM-DD"; throws ParseError on bad input.
    static Date parse(std::string_view s);

    int year()  const { return y_; }
    int month() const { return m_; }
    int day()   const { return d_; }

    // [STUDENT] Comparison operators.
    bool operator==(const Date& o) const;
    bool operator!=(const Date& o) const;
    bool operator<(const Date& o) const;
    bool operator<=(const Date& o) const;
    bool operator>(const Date& o) const;
    bool operator>=(const Date& o) const;

private:
    int y_{0}, m_{0}, d_{0};
};

// [STUDENT] Stream output: prints YYYY-MM-DD (zero-padded).
std::ostream& operator<<(std::ostream& os, const Date& d);

} // namespace inv
#endif
