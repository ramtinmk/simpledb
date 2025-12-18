#ifndef TABLE_H
#define TABLE_H

#include "Row.h"







class Table{

    std::vector<Row> rows;

    public:
        void insert_row(Row& row){

            rows.push_back(row);


        }

        Row& get_row(uint32_t index){

            return rows[index];
        }



        size_t size(){

            return rows.size();
        }

        void print_table(){
            for (uint32_t i=0;i<size();i++){
                rows[i].print();
            }
        }

        void flush_to_disk();

        void open_db_files();
};


#endif