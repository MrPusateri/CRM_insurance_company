#include "my_template.h"
#include <vector>
#include "CustomerManager.h"
#include "my_functions.h"


void CustomerManager::add_customer(const Customer& _customer, bool from_csv) {
    /*
    Method to add a customer into name_map and surname_map. Moreover,
    in the case the value of the variable from_csv=false the function
    execute the method save_persistent_customer_id.

    Arguments:
    ----------
    * _customer (Customer), customer object of the defined Customer class.
    * from_csv (bool), flag that indecates if the customer to add comes
        from a csv file or not.
    */
    name_map[_customer.get_name()].push_back(_customer);
    surname_map[_customer.get_surname()].push_back(_customer);
    if(!from_csv)
    {
        save_persistent_customer_id();
    }
}

int CustomerManager::get_max_customer_id(void){
    /*
    Method to get the maximum value of the current CUSTOMER_ID in the
    name_map.
    */
    int max_customer_id;
    int current_id;

    // if there are no customer the CUSTOMER_ID is negative
    max_customer_id = -1;
    // find the maximum value of customer id in the current name_map
    for (const auto& pair : name_map) {
        for (const auto& customer : pair.second) {
            current_id = customer.get_id();
            if (current_id>max_customer_id)
            {
                max_customer_id = current_id;
            }
        }
    }
    return max_customer_id;
}

void CustomerManager::save_persistent_customer_id(void){
    /* Method to save next customer_id in a txt file. */

    // path for the persistent customer id
    std::string persistence_customer_id_file_path = "next_customer_id.txt";

    // get the maximum value of customer id in this CustomerManagare
    int current_max_customer_id = this->get_max_customer_id();
    std::ofstream file(persistence_customer_id_file_path);

    if (file.is_open()) {
        file << current_max_customer_id+1;
    }
}

int CustomerManager::get_next_customer_id(void){
    /* Method to get next customer_id from a txt file */
    std::string persistence_customer_id_file_path = "next_customer_id.txt";
    std::ifstream file(persistence_customer_id_file_path);

    // default value if the file does not exist or it is empty
    int next_customer_ID = 0;
    if (file.is_open()) {
        file >> next_customer_ID;
    }
    return next_customer_ID;
}

Customer CustomerManager::ask_customer_infos(void){
    /* Method to ask all the necessary customer information */
    std::string input_name, input_surname, input_bday, input_tax_code;
    int next_customer_id;

    // get info to create a Customer object
    next_customer_id = get_next_customer_id();
    std::cout << "Insert the customer name: " << std::endl;
    std::getline(std::cin, input_name);

    std::cout << "Insert the customer surname: " << std::endl;
    std::getline(std::cin, input_surname);

    std::cout << "Insert the customer birth day (DD/MM/YYYY): " << std::endl;
    std::getline(std::cin, input_bday);

    std::cout << "Insert the customer tax code: " << std::endl;
    std::getline(std::cin, input_tax_code);

    Customer temp_customer(next_customer_id, input_name,
        input_surname, input_bday, input_tax_code);

    std::cout << "\nThe customer you want to add is:" << std::endl;
    // temp_customer.print_customer();
    VariadicTable<int, std::string, std::string, std::string, std::string> vt_customer_add = create_vt_customer_header();
    temp_customer.add_customer_row(vt_customer_add);
    vt_customer_add.print(std::cout);
    
    return temp_customer;
}

std::vector<Customer> CustomerManager::search_customer_by_name(void){
    /* Method to guide an user to search a customer by name */
    std::vector<Customer> found_customers;
    std::string name_to_search;
    bool is_present = false;
    VariadicTable<int, std::string, std::string, std::string, std::string> vt_found_customer = create_vt_customer_header();

    std::cout << "Insert the customer NAME you want to search: ";
    std::getline(std::cin, name_to_search);


    // preprocess the input with the same method to
    // define a customer
    name_to_search = preprocess_string(name_to_search);

    int length = name_to_search.length();
    std::string result(length, '*');

    for(const auto& pair: name_map){
        if (pair.first==name_to_search)
        {
            is_present = true;
            for (const auto& customer: pair.second)
            {
                // customer.print_customer();
                customer.add_customer_row(vt_found_customer);
                found_customers.push_back(customer);
            }
            // the name is the key, hence, there are no more
            // customers to find.
            vt_found_customer.print(std::cout);
            break;
        }            
    }

    if(!is_present)
    {
        std::cout << "**********************************"
            << result << std::endl;
        std::cout << "There are no customers with name: "
            << name_to_search << std::endl;
        std::cout << "**********************************"
            << result << std::endl;
    }

    return found_customers;
}

std::vector<Customer> CustomerManager::search_customer_by_surname(void){
    /* Method to guide an user to search a customer by surname */
    std::vector<Customer> found_customers;
    std::string surname_to_search;
    bool is_present = false;
    VariadicTable<int, std::string, std::string, std::string, std::string> vt_found_customer = create_vt_customer_header();

    std::cout << "Insert the customer SURNAME you want to search: ";
    std::getline(std::cin, surname_to_search);


    // preprocess the input with the same method to
    // define a customer
    surname_to_search = preprocess_string(surname_to_search);

    int length = surname_to_search.length();
    std::string result(length, '*');

    for(const auto& pair: surname_map){
        if (pair.first==surname_to_search)
        {
            is_present = true;
            for (const auto& customer: pair.second)
            {
                // customer.print_customer();
                customer.add_customer_row(vt_found_customer);
                found_customers.push_back(customer);

                std::cout << std::endl;
                found_customers.push_back(customer);
            }
            // the surname is the key, hence, there are no more
            // customers to find.
            vt_found_customer.print(std::cout);
            break;
        }            
    }

    if(!is_present)
    {
        std::cout << "**********************************"
            << result << std::endl;
        std::cout << "There are no customers with surname: "
            << surname_to_search << std::endl;
        std::cout << "**********************************"
            << result << std::endl;
    }

    return found_customers;
}

std::vector<Customer> CustomerManager::ask_search_customer_by_name_or_surname(const int& flag_name_surname){
    /*
    Method that drive the user to find a customer in the CustomerManager
    class by name. It use the template yes_or_no_choice to allow the user
    to decide if the result is correct or not.
    */
    std::vector<Customer> output;

    try
    {
        if (flag_name_surname==1)
        {
            // Bind the member function to the current instance
            auto bound_ask_search_customer = std::bind(&CustomerManager::search_customer_by_name, this);
            // temporary customer
            auto temp_found_customers = yes_or_no_choice(bound_ask_search_customer);
            if (temp_found_customers.has_value()) {
                output = temp_found_customers.value();
            }
        }
        else if (flag_name_surname==2)
        {
            // Bind the member function to the current instance
            auto bound_ask_search_customer = std::bind(&CustomerManager::search_customer_by_surname, this);
            // temporary customer
            auto temp_found_customers = yes_or_no_choice(bound_ask_search_customer);
            if (temp_found_customers.has_value()) {
                output = temp_found_customers.value();
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';

    }

    return output;
}

void CustomerManager::delete_customer(Customer customer_to_remove){
    /*
    Method to delete a customer from the CustomerManager.
    */
    auto it_name_map = name_map.find(customer_to_remove.get_name());
    auto it_surname_map = surname_map.find(customer_to_remove.get_surname());
    if(it_name_map!=name_map.end()){
        auto& customer_name_map_vector = it_name_map->second;
        auto& customer_surname_map_vector = it_surname_map->second;

        auto customer_name_it = std::find(
            customer_name_map_vector.begin(),
            customer_name_map_vector.end(),
            customer_to_remove
        );
        auto customer_surname_it = std::find(
            customer_surname_map_vector.begin(),
            customer_surname_map_vector.end(),
            customer_to_remove
        );

        if (customer_name_it!=customer_name_map_vector.end())
        {
            customer_name_map_vector.erase(customer_name_it);
            customer_surname_map_vector.erase(customer_surname_it);

            if (customer_name_map_vector.empty())
            {
                name_map.erase(it_name_map);
                surname_map.erase(it_surname_map);
            }
            
        }
        else
        {
            std::cerr << "Customer not found in the vector" << std::endl;
        }            
    }
    else{
        std::cerr << "Key not found in the map" << std::endl;
    }
}

CustomerManager::CustomerManager(void){
    /*
    Default constructor of the class CustomerManager.

    The first operation is to save the customer_id of the CustomerManager
    class. When a user initialize for the first time the CustomerManager
    there are no customers in the library. Hence, the customer_id will be
    -1.
    */
    this->save_persistent_customer_id();
}

void CustomerManager::add_ask_customer(void){
    /*
    Method that asks to the user to insert the customer information
    and add the new customer if it is all right.
    */
    try
    {
        // Bind the member function to the current instance
        auto bound_ask_customer_infos = std::bind(&CustomerManager::ask_customer_infos, this);
        
        // temporary customer
        auto temp_customer = yes_or_no_choice(bound_ask_customer_infos);
        
        if (temp_customer.has_value()) {
            this->add_customer(temp_customer.value(), false);
        } else {
            std::cout << "Customer addition cancelled." << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void CustomerManager::read_customers_csv(void) {
    /*
    Method to read the CUSTOMERS CSV file. A customer csv must have 5
    fields that are in order: CUSTOMER_ID, NAME, SURNAME, BDAY,
    TAX_CODE. In fact, they are the required parameters for a Customer
    object.
    */

    std::string filename;

    // get the filename
    std::cout << "Insert the customers CSV file name: ";
    std::getline(std::cin, filename);


    read_csv(filename, [this](std::vector<std::string> fields) {
        // check the number of fileds
        if (fields.size() == 5) {
            try {
                // try to extract the each filed with the correct data type
                int _customer_id = std::stoi(fields[0]);
                std::string _name = fields[1];
                std::string _surname = fields[2];
                std::string _bday = fields[3];
                std::string _tax_code = fields[4];

                // create a temporary customer
                Customer _temp_customer(_customer_id, _name, _surname, _bday, _tax_code);

                // add temporary customer
                this->add_customer(_temp_customer, true);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Conversion erorr for the record: " <<
                    fields[0] << ", " << fields[1] << ", " << fields[2] <<
                    ", " << fields[3] << ", " << fields[4] << std::endl;
            } catch (const std::out_of_range& e) {
                // to manage errors due to a row with less fields than expected
                std::cerr << "Out of range value for the record: " <<
                    fields[0] << ", " << fields[1] << ", " << fields[2] <<
                    ", " << fields[3] << ", " << fields[4] << std::endl;
            }
        } else {
            // to manage errors due to a row with different numbers of fields than expected
            std::cerr << "Wrong number of fields for the record: " << fields.size() << std::endl;
        }
    });

    // save the maximum value of customer_id the csv file
    this->save_persistent_customer_id();
}

void CustomerManager::write_customers_csv(void){
    /*
    Method write all the information of the CustomerManager in
    a specific CSV file.
    */

    std::string filename;

    std::cout << "Insert the customers CSV file name: ";
    std::getline(std::cin, filename);
    

    write_csv(
        filename,
        name_map,
        [this](std::ofstream& output_file){
            output_file << "CUSTOMER_ID,NAME,SURNAME,BDAY,TAX_CODE"
                << std::endl;
        },
        true
    );
}

std::vector<Customer> CustomerManager::search_customer(void){
    /*
    Method that drive the user to search a customer by name or surname.
    It returns a vector with the customers that match the research.
    */
    std::string query_search_customer = "Enter the number of the action you want to execute:\n" \
    "[1] Search customer by NAME.\n" \
    "[2] Search customer by SURNAME.\n" \
    "[3] Exit.\n";
    std::vector<int> possible_values = {1, 2, 3};
    int user_action;
    std::vector<Customer> temp_found_customers;

    user_action = select_integer_value(query_search_customer, possible_values);
    
    if(user_action==1 | user_action==2) {
        temp_found_customers = this->ask_search_customer_by_name_or_surname(user_action);
    }

    return temp_found_customers;
}

std::optional<Customer> CustomerManager::get_customer_by_id(void){
    /*
    Method to get a customer by id. In particular, the first process is
    to find a customer by name or surname. After in the standard output
    the program shows the founded customers with the relative
    CUSTOMER_ID and the last operation for the user is to enter the
    CUSTOMER_ID of the customer the user want to chose.
    */
    std::vector<Customer> found_costumers = search_customer();
    std::vector<int> possible_customer_id;
    Customer customer;
    int id_to_search;
    std::string cmd_input;
    bool correct_input = false;

    if(!found_costumers.empty())
    {
        while (!correct_input)
        {
            std::cout << "Enter the CUSTOMER_ID of the customer you want to select: ";
            std::getline(std::cin, cmd_input);
            std::cout << std::endl;

            try
            {
                id_to_search = std::stoi(cmd_input);
                correct_input = true;
            }
            catch(const std::invalid_argument& e) {
                std::cerr << "Conversion erorr for the input: "
                    << cmd_input << "\nEnter an integer value." << std::endl;
            }
        }

        for (const auto& customer : found_costumers) {
            if (customer.get_id() == id_to_search) {
                return customer;
            }
        }
        std::cout << "No customer found with the given ID." << std::endl;
    }

    return std::nullopt;
}

void CustomerManager::ask_remove_customer(void){
    /*
    Method that drives the user to select the customer to remove.
    */

    std::string query_rmv_customer = "Enter the number of the action you want to execute:\n" \
    "[1] Remove the customer.\n" \
    "[2] Exit.\n";
    std::vector<int> possible_values = {1, 2};
    int user_action;

    auto get_customer_result = this->get_customer_by_id();
    
    if(get_customer_result.has_value()){
        Customer customer_to_rmv = get_customer_result.value();
        
        user_action = select_integer_value(query_rmv_customer, possible_values);

        if(user_action==1){
            this->delete_customer(customer_to_rmv);
        }
        else if(user_action==2) {
            std::cout << "Exit from the process." << std::endl;
        }
    }
    else{
        std::cout << "No customers to remove." << std::endl;
    }

}

void CustomerManager::modify_customer(void){
    /*
    Method that drives the user to modify a customer.
    */

    std::string query_mod_customer = "Enter the number of the action you want to execute:\n" \
    "[1] Modify the customer NAME.\n" \
    "[2] Modify the customer SURNAME.\n" \
    "[3] Modify the customer BDAY.\n" \
    "[4] Modify the customer TAX_CODE.\n" \
    "[5] Modify all the customer information.\n" \
    "[6] Exit.\n";
    std::vector<int> possible_values = {1, 2, 3, 4, 5, 6};
    int user_action;

    auto get_customer_result = get_customer_by_id();
    
    if(get_customer_result.has_value()) {
        Customer customer_to_modify = get_customer_result.value();

        user_action = select_integer_value(query_mod_customer, possible_values);
        
        if(user_action!=6) {
            this->delete_customer(customer_to_modify);
        }

        if(user_action==1){
            std::string new_name;
            std::cout << "Enter the customer NAME: ";
            std::getline(std::cin, new_name);
            customer_to_modify.set_name(new_name);
        }
        else if(user_action==2)
        {
            std::string new_surname;
            std::cout << "Enter the customer SURNAME: ";
            std::getline(std::cin, new_surname);
            customer_to_modify.set_surname(new_surname);
        }
        else if(user_action==3)
        {
            std::string new_bday;
            std::cout << "Enter the customer BDAY: ";
            std::getline(std::cin, new_bday);
            customer_to_modify.set_bday(new_bday);
        }
        else if(user_action==4)
        {
            std::string new_tax_code;
            std::cout << "Enter the customer TAX_CODE: ";
            std::getline(std::cin, new_tax_code);
            customer_to_modify.set_taxcode(new_tax_code);
        }
        else if(user_action==5)
        {
            std::string new_name;
            std::string new_surname;
            std::string new_bday;
            std::string new_tax_code;

            std::cout << "Enter the customer NAME: ";
            std::getline(std::cin, new_name);
            customer_to_modify.set_name(new_name);

            std::cout << "Enter the customer SURNAME: ";
            std::getline(std::cin, new_surname);
            customer_to_modify.set_surname(new_surname);

            std::cout << "Enter the customer BDAY: ";
            std::getline(std::cin, new_bday);
            customer_to_modify.set_bday(new_bday);

            std::cout << "Enter the customer TAX_CODE: ";
            std::getline(std::cin, new_tax_code);
            customer_to_modify.set_taxcode(new_tax_code);
        }
        else if(user_action==6)
        {
            std::cout << "Exit from the process." << std::endl;
        }

        if(user_action!=6){
            this->add_customer(customer_to_modify, false);
        }
    }
}

void CustomerManager::print_customers() const {
    /*
    Method to print alle the customer in the CustomerManager class by name.
    */
    VariadicTable<int, std::string, std::string, std::string, std::string> vt(
        {
            "CUSTOMER_ID", "NAME", "SURNAME", "BDAY", "TAX_CODE"});

    for(const auto& pair: name_map){
        for(const auto& customer: pair.second){
            vt.addRow(
                customer.get_id(),
                customer.get_name(),
                customer.get_surname(),
                customer.get_bday(),
                customer.get_tax_code()
            );
        }
    }

    vt.print(std::cout);
}

// PUBLIC: Method to check if there are customers
bool CustomerManager::presence_of_customers(void){
    return !name_map.empty();
}