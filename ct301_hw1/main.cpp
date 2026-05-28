// main.cpp  [PROVIDED driver]
// Usage: ./inventory <inventory_file> <transactions_file> <output_file>
//
// 1. Read the inventory file; each line is an item, loaded as an implicit ADD.
// 2. Read the transactions file; each line becomes a Command.
// 3. Run the commands in order against one Inventory, threading a current
//    selection and writing PRINT/REPORT output to stdout.
// 4. Write the final inventory state to the output file.
//
// Errors on any single line are reported to stderr and that line is skipped;
// the program never crashes on bad input.
#include "inventory.h"
#include "command.h"
#include "factories.h"
#include "file_reader.h"
#include "parse_error.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

int main(int argc, char** argv) {
    using namespace inv;

    if (argc != 4) {
        std::cerr << "usage: " << argv[0]
                  << " <inventory_file> <transactions_file> <output_file>\n";
        return 1;
    }

    Inventory inventory;

    // ---- 1. Load the initial inventory (each line is an item) ----
    try {
        for (const ParsedLine& pl : read_lines(argv[1])) {
            try {
                inventory.add(make_item(pl));
            } catch (const ParseError& e) {
                std::cerr << "ERROR (inventory): " << e.what() << '\n';
            }
        }
    } catch (const ParseError& e) {
        std::cerr << "FATAL: " << e.what() << '\n';
        return 1;
    }

    // ---- 2 + 3. Parse and run transactions ----
    RunContext ctx{inventory, {}, std::cout};
    try {
        for (const ParsedLine& pl : read_lines(argv[2])) {
            try {
                std::unique_ptr<Command> cmd = make_command(pl);
                cmd->execute(ctx);
            } catch (const ParseError& e) {
                std::cerr << "ERROR (transaction): " << e.what() << '\n';
            }
        }
    } catch (const ParseError& e) {
        std::cerr << "FATAL: " << e.what() << '\n';
        return 1;
    }

    // ---- 4. Write final state ----
    std::ofstream out(argv[3]);
    if (!out) {
        std::cerr << "FATAL: cannot open output file: " << argv[3] << '\n';
        return 1;
    }
    inventory.write(out);

    return 0;
}
