// tokenizer.cpp  [PROVIDED]
#include "tokenizer.h"
#include <cctype>
#include <sstream>

namespace inv {

std::optional<ParsedLine> tokenize(const std::string& rawLine, int lineNumber) {
    // Drop a comment starting at '#'.
    std::string line = rawLine;
    if (auto hash = line.find('#'); hash != std::string::npos)
        line = line.substr(0, hash);

    // Split on whitespace.
    std::istringstream iss(line);
    std::string tok;
    ParsedLine pl;
    pl.lineNumber = lineNumber;
    while (iss >> tok) {
        if (pl.verb.empty()) pl.verb = tok;
        else                 pl.args.push_back(tok);
    }
    if (pl.verb.empty()) return std::nullopt;   // blank or comment-only
    return pl;
}

} // namespace inv
