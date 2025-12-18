
#ifndef ROW_H
#define ROW_H

#include <cstdint>
#include <vector>
#include <cstring>
#include <string>
#include <stdexcept>
#include <iostream>

enum class DataType{
    INT,
    VARCHAR
};


class DataField{

    private:

        DataType type;

        std::vector<uint8_t> data;

    public:
        DataField(int value): type(DataType::INT){

            data.resize(sizeof(int));

            std::memcpy(data.data(),&value,sizeof(int));
        }

        DataField(const std::string &s): type(DataType::VARCHAR){

            data.assign(s.begin(),s.end());

        }

        DataField() = delete;

        int getInt() const {

            if (type != DataType::INT){
                throw std::runtime_error("DataField: not an INT");
            }

            int value;

            std::memcpy(&value,data.data(),sizeof(int));

            return value;
        }

        std::string getString() const {

            if (type!= DataType::VARCHAR)
                throw std::runtime_error("DataField: not an VARCHAR");

            return std::string(data.begin(),data.end());
        }

        DataType getType() const{

            return type;
        }
     
};

class Row{

    private:
    
        std::vector<DataField> values;

    public: 

        void add_column(DataField& data){

            values.push_back(data);
        }

        DataField& get_column(uint16_t index){

            return values[index];
        }

        void print(){

            for (size_t i=0;i<values.size();i++)
            {
                switch ((get_column(i)).getType()) {
                case DataType::INT:
                    std::cout <<" "<< values[i].getInt() << " |";
                    break;

                case DataType::VARCHAR:
                    std::cout <<" "<< values[i].getString() << " |";
                    break;

                default:
                    std::cout << "Unknown type\n";
                }

            }
            std::cout<<"\n";
        }

};


#endif