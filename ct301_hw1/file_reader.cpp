// file_reader.cpp  [PROVIDED]
#include "file_reader.h"
#include "tokenizer.h"
#include "parse_error.h"

#include <fstream>

namespace inv {

std::vector<ParsedLine> read_lines(const std::string& path) {
    std::ifstream in(path);
    if (!in)
        throw ParseError("cannot open file: " + path);

    std::vector<ParsedLine> out;
    std::string raw;
    int n = 0;
    while (std::getline(in, raw)) {
        ++n;
        if (auto pl = tokenize(raw, n); pl.has_value())
            out.push_back(std::move(*pl));
    }
    return out;
}

} // namespace inv
