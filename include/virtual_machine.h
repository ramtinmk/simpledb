#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H

#include "statement.h"
#include "Table.h"





enum class ExecutionResult{
    SUCSESS,
    TABLE_FULL
};


ExecutionResult execute_statement(Statement* statement,Table* table);


#endif