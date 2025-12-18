
#ifndef INPUT_BUFFER_H
#define INPUT_BUFFER_H

#include <iostream>
#include <string>
#include <sstream>

class InputBuffer{

    std::string input;



    void get_input();

    public: 
        std::string get_buffer();

};

#endif