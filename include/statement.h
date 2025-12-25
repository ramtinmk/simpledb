

#ifndef STATEMENT_H
#define STATEMENT_H

#include "Row.h"
#include <regex> 
#include <cctype>
#include <algorithm>

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

size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}

Statement& build_statement(std::string& query){
    
    std::vector<std::string> parts;

    std::string cleaned_query = std::regex_replace(query, std::regex("\\s+"), " ");

    char delimiter = ' ';
    size_t length = split(cleaned_query,parts,delimiter);

    std::cout<<length<<std::endl;

    // for (size_t i =0;i<parts.size();i++)
    // {
    //     std::cout<<parts[i]<<std::endl;
    // }

    std::string virgool = ",";
    
     for (size_t i =0;i<parts.size();i++)
    {
        if (parts[i].find(virgool) == std::string::npos){
            std::transform(parts[i].begin(), parts[i].end(), parts[i].begin(),
            [](unsigned char c){ return std::tolower(c); });  // Use a lambda with unsigned char cast
        }
    }

    Statement* statement = new Statement();

    if (parts[0] == "insert"){

        std::vector<std::string> columns;

        size_t length = split(parts[1],columns,',');

        statement->type = StatementType::INSERT;

        for (size_t i=0;i<columns.size();i++)
        {
            // Check if integer
            if (std::all_of(columns[i].begin(), columns[i].end(), ::isdigit)){
                int value = std::stoi(columns[i]);
                DataField data(value);
                statement->row_to_insert.add_column(data);
            }
            else{
                // It's a string
                // Remove quotes if present
                if (columns[i].front() == '\'' && columns[i].back() == '\''){
                    columns[i] = columns[i].substr(1, columns[i].size() - 2);
                }
                DataField data(columns[i]);
                statement->row_to_insert.add_column(data);
            }
        }

        return *statement;
    }

}


#endif