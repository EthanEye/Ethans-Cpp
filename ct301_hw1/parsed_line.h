// parsed_line.h  [PROVIDED]
#ifndef PARSED_LINE_H
#define PARSED_LINE_H

#include <string>
#include <vector>

namespace inv {

struct ParsedLine {
    std::string verb;                 // first token (verb or item TYPE)
    std::vector<std::string> args;    // remaining tokens, in order
    int lineNumber{0};                // 1-based source line, for error messages
};

} // namespace inv
#endif
