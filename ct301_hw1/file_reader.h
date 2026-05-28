// file_reader.h  [PROVIDED]
#ifndef FILE_READER_H
#define FILE_READER_H

#include "parsed_line.h"
#include <string>
#include <vector>

namespace inv {

// Open path and return every non-blank, non-comment line as a ParsedLine.
// Throws ParseError if the file cannot be opened.
std::vector<ParsedLine> read_lines(const std::string& path);

} // namespace inv
#endif
