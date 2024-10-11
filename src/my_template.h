#ifndef MY_TEMPLATE_H
#define MY_TEMPLATE_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <optional>
#include <cctype>
#include <cstdio>
#include "my_functions.h"


/************/
/* TEMPLATE */
/************/
template<typename WriteHeader, typename UnorderedMapToWrite>
void write_csv(const std::string& filename, UnorderedMapToWrite map, WriteHeader write_header, bool flag_header=false){
    std::ofstream output_csv(filename);

    if(!output_csv.is_open()){
        std::cerr << "\nError in opening the file: " << filename << std::endl;
    }
    else{
        if (flag_header)
        {
            write_header(output_csv);
        }

        for(auto& pair: map){
            for (auto& object: pair.second)
            {
                object.write_on_csv(output_csv);
            }
            
        }
        output_csv.close();
    }
};

template<typename ProcessRowFunc>
void read_csv(const std::string& filename, ProcessRowFunc process_row, bool flag_header=true) {
    /*
    Tamplate to read a CSV file.

    Arguments:
    ----------
    * filename (std::string), path of the file to read.
    * process_row (ProcessRowFunc), it has to be a function (also lambda)     
        that is able to process a row of the csv in the right manner.
    * flag_header (bool), if it is true it skip the first row since it 
        is the header.
    */
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "\nError in opening the file: " << filename << std::endl;
    }

    std::string line;
    // flag to skip the first row that is the header for the csv file
    while (std::getline(file, line)) {
        if (flag_header) {
            flag_header = false;
            continue;
        }
        std::istringstream s(line);
        std::vector<std::string> fields;
        std::string field;

        while (std::getline(s, field, ',')) {
            fields.push_back(field);
        }

        // invoce callback function to process the row
        process_row(fields);
    }

    file.close();
};

template<typename action>
auto yes_or_no_choice(action a) -> std::optional<decltype(a())> {
    /*
    Template to drive the user in a yes or no decision. It accepts collable
    objects in order to use different functions with the template.

    The function return std::nullopt if the user want to stop the action a.
    You need to use std of c++17.

    Arguments:
    ----------
    * a (action), it must be a callable object that return a result.
    */
    bool flag_yn = false;
    bool is_correct_choice;
    char input_y_n, clean_char;
    decltype(a()) output;
    
    while (not flag_yn)
    {
        is_correct_choice = false;
        output = a();

        while(not is_correct_choice)
        {
            std::cout << "\nIt is correct?[y/n] ";
            std::cin >> input_y_n;
            if (std::tolower(input_y_n)=='y')
            {
                flag_yn = true;
                is_correct_choice = true;
            }
            else if (std::tolower(input_y_n)=='n')
            {
                is_correct_choice = true;
                if (want_exit_yes_or_no())
                {
                    // return no value if user don't want to continue
                    return std::nullopt;
                }
            }
            else
            {
                std::cout << "You type: " << input_y_n
                    << "\nYou must type 'y' or 'n'. Try again.\n"
                    << std::endl;
            }
            // clean buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return output;
};

#endif // MY_TEMPLATE_H