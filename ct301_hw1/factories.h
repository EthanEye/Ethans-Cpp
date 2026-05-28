// factories.h  [PROVIDED]
#ifndef FACTORIES_H
#define FACTORIES_H

#include "item.h"
#include "command.h"
#include "parsed_line.h"
#include <memory>

namespace inv {

// Build an Item from an ADD payload (pl.verb is the TYPE, pl.args its fields).
// Throws ParseError on unknown type, wrong field count, or bad field values.
std::unique_ptr<Item> make_item(const ParsedLine& pl);

// Build a Command from a transaction line. Throws ParseError on unknown verb
// or wrong argument count.
std::unique_ptr<Command> make_command(const ParsedLine& pl);

} // namespace inv
#endif
