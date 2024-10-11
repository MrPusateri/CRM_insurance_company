/**********************************************************
Program to collect the CRM function for pre-processing
variables and to perform other operations.
**********************************************************/
#include "my_functions.h"
#include <regex>
#include <sstream>
#include <vector>

std::string preprocess_string(const std::string& s) {
    /*
    Function to pre-process a string creating only uppercase characters
    and removing special characters.

    Arguments:
    ----------
    * s (std::string), string to pre-process.
    */
    std::string output = s;

    // Convert to uppercase
    std::transform(output.begin(), output.end(), output.begin(), ::toupper);

    // remove special characters
    output = remove_special_chars(output);

    return output;
}

std::string remove_special_chars(const std::string& input) {
    /*
    Function that removes characters that are not aplphanumeric
    from a std::string object.

    Arguments:
    ----------
    * input (std::string), string to process.
    */
    std::string result;
    result.reserve(input.size());

    // Copy only spaces and alphanumeric characters
    std::copy_if(input.begin(), input.end(), std::back_inserter(result), [](char c) {
        return std::isalpha(static_cast<unsigned char>(c)) || std::isspace(static_cast<unsigned char>(c));
    });

    return result;
}

bool is_valid_date_layout(const std::string& date) {
    /*
    Function to check that the date has the correct layout.
    DD/MM/YYYY.

    Arguments:
    * date (std::string), date as string.
    */
    std::regex datePattern(R"(^\d{2}/\d{2}/\d{4}$)");
    return std::regex_match(date, datePattern);
}

bool is_valid_date_value(int day, int month, int year) {
    /*
    Function that verify if a date is in a valid range.

    Arguments:
    ----------
    * day (int), day integer value.
    * month (int), month integer value.
    * year (int), year integer value.
    */
    if (month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    // Build a tm struct with the given data
    std::tm time_struct = {};
    time_struct.tm_mday = day;
    time_struct.tm_mon = month - 1;
    time_struct.tm_year = year - 1900;

    // mktime to normalize the time_struct (pointer in the memory)
    std::time_t time = std::mktime(&time_struct);
    if (time == -1) {
        return false;
    }

    // verify that the date structure not change after the normalization
    if (time_struct.tm_mday == day && time_struct.tm_mon == month - 1 && time_struct.tm_year == year - 1900) {
        return true;
    } else {
        return false;
    }
}

std::string validate_date(const std::string& date) {
    /*
    Function to validate a date value in the format DD/MM/YYYY.

    Arguments:
    ----------
    * date (std::string), date to check if it is valid or not.
    */
    if (!is_valid_date_layout(date)) {
        std::cout << "A date must be in the format DD/MM/YYYY.\n"
                  << "The base missing date is: 00/00/0000 " << std::endl;
        return "00/00/0000";
    }
    else if (date=="00/00/0000")
    {
        // it is already corrected
        return date;
    }
    
    else
    {
        int day, month, year;
        std::string temp; // temporary string to get parts of a date
        // build string stream object
        std::stringstream ss(date);        
        
        // get day value
        std::getline(ss, temp, '/');
        day = std::stoi(temp);

        // get month value
        std::getline(ss, temp, '/');
        month = std::stoi(temp);

        // get year value
        std::getline(ss, temp, '/');
        year = std::stoi(temp);

        if (!is_valid_date_value(day, month, year))
        {
            std::cout << "The date is not valid.\n"
                  << "The base missing date is: 00/00/0000" << std::endl;
            return "00/00/0000";
        }
    }
    return date;
}

bool is_valid_tax_code(const std::string& tax_code) {
    /*
    Function to check if a std::string has only uppercase letters
    and digits.

    Arguments:
    ----------
    * tax_code (std::string), string that represent the tax_code.
    */
    std::regex tax_code_pattern(R"(^[A-Z0-9]+$)");
    return std::regex_match(tax_code, tax_code_pattern);
}

std::string validate_tax_code(const std::string& tax_code) {
    /*
    Function to validate a std::string with the tax_code constraints.

    Arguments:
    ----------
    * tax_code (std::string), string that represent the tax_code.
    */
    std::string upper_tax_code = tax_code;

    // convert to uppercase
    std::transform(upper_tax_code.begin(), upper_tax_code.end(), upper_tax_code.begin(), ::toupper);

    if (!is_valid_tax_code(upper_tax_code)) {
        std::cout << "Tax code must be composed by numbers and letters only.\n"
                  << "The base missing tax code is: XXXXXXXXXXXXXXXX" << std::endl;
        return "XXXXXXXXXXXXXXXX";
    }
    return upper_tax_code;
}

bool want_exit_yes_or_no(void){
    /*
    Function that ask to the user if he or she wants to stop a process.
    */
    bool output_flag, is_correct_choice;
    char input_y_n, clean_char;

    is_correct_choice = false;

    while (not is_correct_choice)
    {
        std::cout << "Do you want to stop the process?[y/n] ";
        std::cin >> input_y_n;
        // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (std::tolower(input_y_n)=='y')
        {
            output_flag = true;
            is_correct_choice = true;
        }
        else if (std::tolower(input_y_n)=='n')
        {
            output_flag = false;
            is_correct_choice = true;
        }
        else
        {
            // wrong input by the user
            std::cout << "You type: " << input_y_n
                << "\nYou must type 'y' or 'n'. Try again.\n"
                << std::endl;
        }
        // clean buffer
        // while((clean_char = getchar()) !='\n' && clean_char!=EOF);
    }
    return output_flag;
}

bool contains(const std::vector<int>& vec, int value) {
    /*
    Function that check if a integer value is contained into a vector.

    Arguments:
    ----------
    * vec (std::vector), vector with the possible values.
    * value (int), integer value to check.
    */
    auto it = std::find(vec.begin(), vec.end(), value);

    // If the iterator is not equalt to vec.end(), the value is
    // contained in vec
    return it != vec.end();
}

bool contains(const std::vector<std::string>& vec, std::string value) {
    /*
    Function that check if a std::string value is contained into a vector
    of std::string values.

    Arguments:
    ----------
    * vec (std::vector<std::string>), vector with the possible std::string values.
    * value (std::string), string value to check.
    */
    auto it = std::find(vec.begin(), vec.end(), value);
    // If the iterator is not equalt to vec.end(), the value is
    // contained in vec
    return it != vec.end();
}

std::string preprocess_interaction_type(const std::string& interaction_type){
    /*
    Function to pre-process a std::string that represent an interaction type

    Arguments:
    ----------
    * interaction_type (std::string), string that represent an interaction type.
    */
    std::string output_interaction_type = interaction_type;
    std::vector<std::string> possible_interaction_values = {"APPOINTMENT", "QUOTE", "SIGN"};

    if (contains(possible_interaction_values, output_interaction_type))
    {
        return output_interaction_type;
    }
    else{
        return "XXXXXX";
    }
}

std::string preprocess_product_type(const std::string& product_type){
    /*
    Function to pre-process a std::string that represent an product type

    Arguments:
    ----------
    * product_type (std::string), string that represent an product type.
    */
    std::string output_product_type = product_type;
    std::vector<std::string> possible_interaction_values = {"CAR", "HEALTH", "HOME"};

    if (contains(possible_interaction_values, output_product_type))
    {
        return output_product_type;
    }
    else{
        return "XXXXXX";
    }
}

int select_integer_value(std::string query, std::vector<int> possible_values){
    /*
    Function to select get the integer value selected by the use in order to
    get make a decision based on the query proposed.

    Arguments:
    ----------
    * query (std::string), string that represent the query to propose to the user
    * possible_values(std::vector<int>), vector that represent has the values of
        a possible choice of the user.
    */
    bool correct_input = false;
    std::string cmd_input;
    int user_action;

    while (!correct_input)
    {
        // get user input
        std::cout << query
            << "You chose: " ;
        std::cin >> cmd_input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << std::endl;
        try {
                // try to convert string to integer value
                user_action = std::stoi(cmd_input);

                // check if user_action is a possible value
                if (contains(possible_values, user_action)) {
                    correct_input = true;
                }
                else {
                    std::ostringstream oss;
                    oss << "[";
                    
                    for (size_t i = 0; i < possible_values.size(); ++i) {
                        oss << possible_values[i];
                        if (i < possible_values.size() - 1) {
                            oss << ", ";
                        }
                    }
    
                    oss << "]";
                    
                    std::string output = oss.str();

                    std::cout << "The integer value you insert is not valid.\n"
                        << "You must insert a value in the following list: "
                        << output << "\nTry again.\n" << std::endl;
                }
        }
        catch(const std::invalid_argument& e) {
            std::cerr << "Conversion erorr for the input: "
                << cmd_input << "\nEnter an integer value." << std::endl;
        }
    }

    return user_action;
}

VariadicTable<int, std::string, std::string, std::string, std::string> create_vt_customer_header(void){
    /*
    Function to create a VariadicTable with the fields of a customers table structure.
    */
    VariadicTable<int, std::string, std::string, std::string, std::string> vt(
        {
            "CUSTOMER_ID", "NAME", "SURNAME", "BDAY", "TAX_CODE"});
    return vt;
}

VariadicTable<int, std::string, bool, std::string, std::string, long, int> create_vt_interaction_header(void){
    /*
    Function to create a VariadicTable with the fields of a interactions table structure.
    */
    VariadicTable<int, std::string, bool, std::string, std::string, long, int> vt(
        {
            "CUSTOMER_ID", "INTERCTION_TYPE", "FLAG_INTEREST", "PRODUCT_TYPE",
            "INTERACTION_DATE", "POLICY_ID", "QUOTE_ID"});
        return vt;
}