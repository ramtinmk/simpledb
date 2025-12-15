#include <iostream>
#include "input_buffer.h"
#include "statement.h"





int main() {

    std::cout<< "Welcome to SimpleDB :)"<< std::endl;

    while (1){
        InputBuffer str;

        std::cout <<"write your query: ";
        std::string query = str.get_buffer();
        std::cout<<"your query: "<< query<<std::endl;
    }
}