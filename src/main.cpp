#include <iostream>
#include "input_buffer.h"
#include "statement.h"
#include "virtual_machine.h"




int main() {

    std::cout<< "Welcome to SimpleDB :)"<< std::endl;

    while (1){
        InputBuffer str;

        std::cout <<"write your query: ";
        std::string query = str.get_buffer();

        Statement state = build_statement(query);


        state.row_to_insert.print();

        std::cout<<"your query: "<< query<<std::endl;
    }
}