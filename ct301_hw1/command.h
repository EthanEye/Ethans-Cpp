// command.h  [PROVIDED base; STUDENT implements execute() bodies]
// Each transaction line becomes a Command. Commands run against a RunContext
// that holds the inventory, the current selection, and the output stream.
#ifndef COMMAND_H
#define COMMAND_H

#include "inventory.h"
#include "date.h"
#include "state.h"

#include <memory>
#include <ostream>
#include <string>
#include <vector>

namespace inv {

// Shared state threaded through a run of commands.
struct RunContext {
    Inventory& inv;
    std::vector<Item*> selection;   // the current selection
    std::ostream& out;              // where PRINT / REPORT write
};

class Command {
public:
    virtual ~Command() = default;
    virtual void execute(RunContext& ctx) = 0;
};

// ---- selection commands ----
class SelectAllCommand : public Command {
public:
    void execute(RunContext& ctx) override;
};
class SelectByCommand : public Command {
public:
    SelectByCommand(std::string key, std::string value)
        : key_(std::move(key)), value_(std::move(value)) {}
    void execute(RunContext& ctx) override;
private:
    std::string key_, value_;
};
class SelectInStateCommand : public Command {
public:
    explicit SelectInStateCommand(State s) : s_(s) {}
    void execute(RunContext& ctx) override;
private:
    State s_;
};
class SelectOlderThanCommand : public Command {
public:
    explicit SelectOlderThanCommand(Date d) : d_(d) {}
    void execute(RunContext& ctx) override;
private:
    Date d_;
};
class TopByValueCommand : public Command {
public:
    explicit TopByValueCommand(std::size_t n) : n_(n) {}
    void execute(RunContext& ctx) override;
private:
    std::size_t n_;
};
class GroupByCommand : public Command {
public:
    explicit GroupByCommand(std::string key) : key_(std::move(key)) {}
    void execute(RunContext& ctx) override;
private:
    std::string key_;
};

// ---- output commands ----
class PrintCommand : public Command {
public:
    void execute(RunContext& ctx) override;
};
class ReportCommand : public Command {
public:
    void execute(RunContext& ctx) override;
};

// ---- action commands (operate on the current selection; leave rejects as selection) ----
class SurplusCommand : public Command {
public:
    void execute(RunContext& ctx) override;
};
class SellCommand : public Command {
public:
    void execute(RunContext& ctx) override;
};
class LoanCommand : public Command {
public:
    LoanCommand(std::string borrower, Date when)
        : borrower_(std::move(borrower)), when_(when) {}
    void execute(RunContext& ctx) override;
private:
    std::string borrower_;
    Date when_;
};
class ReturnCommand : public Command {
public:
    void execute(RunContext& ctx) override;
};

// ---- add command (owns the item until executed) ----
class AddCommand : public Command {
public:
    explicit AddCommand(std::unique_ptr<Item> item) : item_(std::move(item)) {}
    void execute(RunContext& ctx) override;
private:
    std::unique_ptr<Item> item_;
};

} // namespace inv
#endif
