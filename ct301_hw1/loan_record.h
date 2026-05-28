// loan_record.h  [PROVIDED]
#ifndef LOAN_RECORD_H
#define LOAN_RECORD_H

#include "date.h"
#include <string>

namespace inv {

struct LoanRecord {
    std::string itemId;
    std::string borrower;
    Date        when;
};

} // namespace inv
#endif
