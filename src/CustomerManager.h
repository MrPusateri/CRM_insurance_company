#ifndef CUSTOMER_MANAGER_H
#define CUSTOMER_MANAGER_H


#include <unordered_map>
#include "Customer.h"


class CustomerManager {
private:
    // unordered_map with customer name as key
    std::unordered_map<std::string, std::vector<Customer>, CustomerHash> name_map;
    // unordered_map with customer surname as key
    std::unordered_map<std::string, std::vector<Customer>, CustomerHash> surname_map;

    // Method to add a customer into name_map and surname_map
    void add_customer(const Customer& _customer, bool from_csv);

    // Method to get the maximum value of the current CUSTOMER_ID in the name_map
    int get_max_customer_id(void);

    // Method to save next customer_id in a txt file
    void save_persistent_customer_id(void);

    // Method to get next customer_id from a txt file
    int get_next_customer_id(void);

    // Method to ask all the necessary customer information
    Customer ask_customer_infos(void);

    // Method to guide an user to search a customer by name
    std::vector<Customer> search_customer_by_name(void);

    // Method to guide an user to search a customer by surname
    std::vector<Customer> search_customer_by_surname(void);

    std::vector<Customer> ask_search_customer_by_name_or_surname(const int& flag_name_surname);

    void delete_customer(Customer customer_to_remove);

public:
    // default constructor
    CustomerManager(void);

    void add_ask_customer(void);
    
    void read_customers_csv(void);

    void write_customers_csv(void);

    std::vector<Customer> search_customer(void);

    std::optional<Customer> get_customer_by_id(void);

    void ask_remove_customer(void);

    void modify_customer(void);

    void print_customers() const;

    bool presence_of_customers(void);
};


#endif // CUSTOMER_MANAGER_H