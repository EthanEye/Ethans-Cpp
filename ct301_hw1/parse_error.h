// parse_error.h  [PROVIDED]
// Single exception type thrown by the input layer (reader, tokenizer,
// Date::parse, and the factories). The driver catches it per line,
// reports to stderr, and skips the line.
#ifndef PARSE_ERROR_H
#define PARSE_ERROR_H

#include <stdexcept>
#include <string>

namespace inv {

class ParseError : public std::runtime_error {
public:
    explicit ParseError(const std::string& msg) : std::runtime_error(msg) {}
};

} // namespace inv
#endif
