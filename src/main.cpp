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

        build_statement(query);
        std::cout<<"your query: "<< query<<std::endl;
    }
}