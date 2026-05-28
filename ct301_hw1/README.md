# CT 301 HW1 — Starter Code (Skeleton)

This is your starting point. The headers (`.h`) and several `.cpp` files are
complete and must not be changed. Your job is to implement every function marked
`[TODO]` in:

    date.cpp        the Date comparison operators and operator<<
    items.cpp       all of Equipment / Consumable / Borrowed
    inventory.cpp   every operation except the worked example (surplus) + helpers
    command.cpp     every command's execute() except the worked example (PRINT)

Each `[TODO]` stub currently returns an empty/placeholder value and has a line
like `(void)x; // remove when you implement this` so the project compiles before
you start. Delete that line when you write the real body.

Things that are PROVIDED (do not modify): all `.h` files, `Date::parse`, the
input layer (`tokenizer`, `file_reader`, `factories`, `parsed_line`,
`parse_error`), `main.cpp`, and the `makefile`. One worked example is left in
each of `inventory.cpp` (`surplus`) and `command.cpp` (`PRINT`); study them.

## Build

    make

(The makefile uses the course toolchain: GCC 15.2, `-std=c++26`, all warnings on,
plus the AddressSanitizer/UndefinedBehaviorSanitizer. On macOS the sanitizers may
not link; if so, build without them:
`make CXXFLAGS="-std=c++26 -Wall -Wextra -Wpedantic -g"`.)

## Run

The program takes THREE file arguments, in this order:

    ./inventory <inventory_file> <transactions_file> <output_file>

- `<inventory_file>`   the starting items, one per line
- `<transactions_file>` the commands to apply, one per line
- `<output_file>`      where the final inventory is written

Anything printed by PRINT / REPORT / GROUP_BY goes to the screen (stdout); the
final state of every item is written to `<output_file>`. Example:

    ./inventory data/appx_inventory.txt data/appx_transactions.txt out.txt

## Sample data and checking your work

The `data/` folder contains:

    appx_inventory.txt, appx_transactions.txt   a small example
    appx_output.txt                             its EXPECTED output file
    appx_stdout.txt                             its EXPECTED console output
    big_inventory.txt, big_transactions.txt     a larger example (no expected
                                                output given -- reason about it
                                                yourself)

Check the small example like this:

    ./inventory data/appx_inventory.txt data/appx_transactions.txt myout.txt > mystdout.txt
    diff myout.txt   data/appx_output.txt
    diff mystdout.txt data/appx_stdout.txt

When both `diff`s print nothing, your output matches for that example. Matching
the small example is necessary but NOT sufficient — you are expected to test the
rest of your code yourself (see below).

## Testing is part of the assignment

`student_tests.cpp` is a small test harness with a few worked example tests and a
list of what else you should cover. Build and run it:

    g++ -std=c++26 -Wall -Wextra -Wpedantic -g student_tests.cpp date.cpp \
        items.cpp inventory.cpp command.cpp tokenizer.cpp file_reader.cpp \
        factories.cpp -o student_tests
    ./student_tests

(Use `-std=c++23` if your compiler does not yet accept `c++26`.) Add your own
tests until you are confident every part works. Your grade depends on correct
behavior across cases you will not have seen, so test thoroughly.
