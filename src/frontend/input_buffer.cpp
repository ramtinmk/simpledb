
#include "input_buffer.h"





void InputBuffer::get_input(){

        std::getline(std::cin,input);
    }

     
std::string InputBuffer::get_buffer(){

            get_input();

            return input;
        }