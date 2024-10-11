#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <fstream>
#include "VariadicTable.h"

class Customer {
private:
    int CUSTOMER_ID;
    std::string NAME;
    std::string SURNAME;
    std::string BDAY;
    std::string TAX_CODE;

public:
    // Default constructor
    Customer(void);

    // Specific constructor
    Customer(int _customer_id, const std::string& _name, const std::string& _surname,
        const std::string& _bday, const std::string& _tax_code);

    void print_customer(void) const;

    void add_customer_row(VariadicTable<int, std::string, std::string, std::string, std::string>& vt) const;

    std::string get_name(void) const;

    void set_name(std::string _name);

    std::string get_surname() const;

    void set_surname(std::string _surname);

    void set_bday(std::string _bday);

    std::string get_bday(void) const;

    std::string get_tax_code(void) const;

    void set_taxcode(std::string _tax_code);

    int get_id() const;
    
    bool operator==(const Customer& other) const;

    void write_on_csv(std::ofstream& output_csv_file);

};

struct CustomerHash {
    std::size_t operator()(const std::string& key) const;
};

#endif // CUSTOMER_H