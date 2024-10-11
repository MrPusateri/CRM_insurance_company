#include "Customer.h"
#include "my_functions.h"

// Default constructor
Customer::Customer(){
    CUSTOMER_ID=-1;
    NAME = "XXXXXX";
    SURNAME = "XXXXXX";
    BDAY = "00/00/0000";
    TAX_CODE = "XXXXXXXXXXXXXXXX";
}

// Specific constructor
Customer::Customer(int _customer_id, const std::string& _name, const std::string& _surname,
        const std::string& _bday, const std::string& _tax_code)
        : CUSTOMER_ID(_customer_id), NAME(preprocess_string(_name)),
            SURNAME(preprocess_string(_surname)), BDAY(validate_date(_bday)),
            TAX_CODE(validate_tax_code(_tax_code)) {}

// Method to show the customer information
void Customer::print_customer(void) const {
    std::cout << "CUSTOMER_ID: " << CUSTOMER_ID << std::endl;
    std::cout << "NAME: " << NAME << std::endl;
    std::cout << "SURNAME: " << SURNAME << std::endl;
    std::cout << "BIRTHDAY: " << BDAY << std::endl;
    std::cout << "TAX CODE: " << TAX_CODE << std::endl;
}

// Method to add a customer row into a VariadicTable
void Customer::add_customer_row(VariadicTable<int, std::string, std::string, std::string, std::string>& vt) const{
    vt.addRow(CUSTOMER_ID, NAME, SURNAME, BDAY, TAX_CODE);
}

// Method to get the customer name
std::string Customer::get_name(void) const {
    return NAME;
}

// Method to set the customer name
void Customer::set_name(std::string _name) {
    NAME = preprocess_string(_name);
}

// Method to get the customer surname
std::string Customer::get_surname() const {
    return SURNAME;
}

// Method to set the customer surname
void Customer::set_surname(std::string _surname) {
    SURNAME = preprocess_string(_surname);
}

// Method to set the customer birthday
void Customer::set_bday(std::string _bday) {
    BDAY = validate_date(_bday);
}

// Method to get the customer birthday
std::string Customer::get_bday(void) const{
    return BDAY;
}

// Method to get the customer tex code
std::string Customer::get_tax_code(void) const {
    return TAX_CODE;
}

// Method to set the customer birthday
void Customer::set_taxcode(std::string _tax_code) {
    TAX_CODE = validate_tax_code(_tax_code);
}

// Method to get the customer id
int Customer::get_id() const{
    return CUSTOMER_ID;
}

// Method to check if a customer is equal to another one
bool Customer::operator==(const Customer& other) const {
    return CUSTOMER_ID == other.CUSTOMER_ID;
}

// Method to write on a CSV file the customer fields
void Customer::write_on_csv(std::ofstream& output_csv_file){
    output_csv_file << CUSTOMER_ID << ","
    << NAME << ","
    << SURNAME << ","
    << BDAY << ","
    << TAX_CODE << std::endl;
}


std::size_t CustomerHash::operator()(const std::string& key) const {
    return std::hash<std::string>{}(key);
}