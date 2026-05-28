// command.cpp  [STUDENT implements these execute() bodies]
//
// Each Command is one transaction verb. execute() runs it against ctx:
//   ctx.inv        -- the Inventory
//   ctx.selection  -- the current selection (vector<Item*>), carried line to line
//   ctx.out        -- where PRINT / REPORT / GROUP_BY write
//
// PrintCommand is the worked example. Implement the rest in the same shape:
//   - a selection verb SETS ctx.selection from the matching Inventory call
//   - an output verb writes to ctx.out
//   - an action verb runs the Inventory action on ctx.selection and replaces
//     ctx.selection with whatever that action returned (the rejects)
// Each stub has a "(void)ctx; // remove when you implement this" line just so it
// compiles -- delete it when you write the body.
#include "command.h"

namespace inv {

// ---- selection verbs: set ctx.selection ----
// [TODO] ctx.selection = ctx.inv.select_all();
void SelectAllCommand::execute(RunContext& ctx)       { (void)ctx; /* remove when you implement this */ }
// [TODO] ctx.selection = ctx.inv.select_by(key_, value_);
void SelectByCommand::execute(RunContext& ctx)        { (void)ctx; /* remove when you implement this */ }
// [TODO] ctx.selection = ctx.inv.select_in_state(state_);
void SelectInStateCommand::execute(RunContext& ctx)   { (void)ctx; /* remove when you implement this */ }
// [TODO] ctx.selection = ctx.inv.select_older_than(date_);
void SelectOlderThanCommand::execute(RunContext& ctx) { (void)ctx; /* remove when you implement this */ }
// [TODO] ctx.selection = ctx.inv.select_top_by_value(n_);
void TopByValueCommand::execute(RunContext& ctx)      { (void)ctx; /* remove when you implement this */ }

// [TODO] GROUP_BY: build the groups (ctx.inv.group_by(key_)), print them with
// ctx.inv.print(groups, ctx.out), then set ctx.selection to the flattened list
// of every grouped item.
void GroupByCommand::execute(RunContext& ctx)         { (void)ctx; /* remove when you implement this */ }

// ---- output verbs: write to ctx.out ----
// [WORKED EXAMPLE] PRINT shows the current selection on the output stream.
void PrintCommand::execute(RunContext& ctx)  { ctx.inv.print(ctx.selection, ctx.out); }

// [TODO] ctx.inv.report(ctx.out);
void ReportCommand::execute(RunContext& ctx) { (void)ctx; /* remove when you implement this */ }

// ---- action verbs: replace ctx.selection with the rejects ----
// [TODO] ctx.selection = ctx.inv.surplus(ctx.selection);
void SurplusCommand::execute(RunContext& ctx) { (void)ctx; /* remove when you implement this */ }
// [TODO] ctx.selection = ctx.inv.sell(ctx.selection);
void SellCommand::execute(RunContext& ctx)    { (void)ctx; /* remove when you implement this */ }
// [TODO] ctx.selection = ctx.inv.loan(ctx.selection, borrower_, when_);
void LoanCommand::execute(RunContext& ctx)    { (void)ctx; /* remove when you implement this */ }
// [TODO] ctx.selection = ctx.inv.return_items(ctx.selection);
void ReturnCommand::execute(RunContext& ctx)  { (void)ctx; /* remove when you implement this */ }

// [TODO] ctx.inv.add(std::move(item_));
void AddCommand::execute(RunContext& ctx)     { (void)ctx; /* remove when you implement this */ }

} // namespace inv
