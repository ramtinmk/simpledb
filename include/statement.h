
#include "Row.h"


enum class Result{
    SUCCESS,
    UNRECOGNIZED_STATEMENT,
    SYNTAX_ERROR
};



enum class StatementType{
    SELECT,
    INSERT
};


struct Statement{

    StatementType type;
    
    Row row_to_insert;
};
