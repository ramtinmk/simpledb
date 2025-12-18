#include "virtual_machine.h"



ExecutionResult execute_statement(Statement* statement,Table* table){

    switch (statement->type)
    {
    case INSERT:
        
        table->insert_row(statement->row_to_insert);

        break;
    case SELECT:
        
        break;
    default:
        break;
    }

}


