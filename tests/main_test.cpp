#include <iostream>
#include "Row.h"
#include "input_buffer.h"

using namespace std;



int main(){

    cout << "Starting to test SimpleDB..." << endl;

    InputBuffer inp;

    std::string input_string = inp.get_buffer();

    std::cout<<input_string<<std::endl;

    std::vector<int> ints = {1,2,3,4,5};

    std::vector<std::string> strings = {"tes","tt","adsa","adsd","dasgsdg"};

    Row r;


    for (int i=0;i<ints.size();i++){

        DataField d(ints[i]);

        r.add_column(d);

        DataField dd(strings[i]);

        // std::cout <<  static_cast<int>(dd.getType()) << static_cast<int>(d.getType()) << std::endl;

        r.add_column(dd);

    }

    r.print();
}