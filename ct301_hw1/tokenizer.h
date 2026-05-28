// tokenizer.h  [PROVIDED]
#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "parsed_line.h"
#include <optional>
#include <string>

namespace inv {

// Split one raw line into a ParsedLine.
// - strips a trailing '#' comment
// - trims surrounding whitespace
// - splits on runs of whitespace
// Returns std::nullopt for a blank/comment-only line (caller skips it).
std::optional<ParsedLine> tokenize(const std::string& rawLine, int lineNumber);

} // namespace inv
#endif
