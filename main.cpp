#include <string>
#include <functional>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <regex>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <optional>
#include <ctime>


/********************/
/* DEFINE FUNCTIONS */
/********************/
std::string preprocess_string(const std::string& s);
std::string remove_special_chars(const std::string& input);
bool is_valid_date_layout(const std::string& date);
bool is_valid_date_value(int day, int month, int year);
std::string validate_date(const std::string& date);
bool is_valid_tax_code(const std::string& tax_code);
std::string validate_tax_code(const std::string& tax_code);
bool want_exit_yes_or_no(void);
bool contains(const std::vector<int>& vec, int value);
bool contains(const std::vector<std::string>& vec, std::string value);
std::string preprocess_interaction_type(const std::string& interaction_type);
std::string preprocess_product_type(const std::string& product_type);
int select_integer_value(std::string query, std::vector<int> possible_values);

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
}

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
            std::cout << "\nIt is correct?[y/n]" << std::endl;
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
            while((clean_char = getchar()) !='\n' && clean_char!=EOF);
        }
    }
    return output;
}

/************************************************************************/
/*                            CUSTOMER CLASS                            */
/************************************************************************/
class Customer {
private:
    int CUSTOMER_ID;
    std::string NAME;
    std::string SURNAME;
    std::string BDAY;
    std::string TAX_CODE;

public:
    // Default constructor
    Customer(){
        CUSTOMER_ID=-1;
        NAME = "XXXXXX";
        SURNAME = "XXXXXX";
        BDAY = "00/00/0000";
        TAX_CODE = "XXXXXXXXXXXXXXXX";
    }

    // Specific constructor
    Customer(int _customer_id, const std::string& _name, const std::string& _surname, const std::string& _bday, const std::string& _tax_code)
        : CUSTOMER_ID(_customer_id), NAME(preprocess_string(_name)), SURNAME(preprocess_string(_surname)), BDAY(validate_date(_bday)), TAX_CODE(validate_tax_code(_tax_code)) {}

    void print_customer(void) const {
        /* Method to show the customer information */
        std::cout << "CUSTOMER_ID: " << CUSTOMER_ID << std::endl;
        std::cout << "NAME: " << NAME << std::endl;
        std::cout << "SURNAME: " << SURNAME << std::endl;
        std::cout << "BIRTHDAY: " << BDAY << std::endl;
        std::cout << "TAX CODE: " << TAX_CODE << std::endl;
    }

    std::string get_name(void) const {
        /* Method to get the customer name */
        return NAME;
    }

    void set_name(std::string _name) {
        /* Method to set the customer name */
        NAME = preprocess_string(_name);
    }

    std::string get_surname() const {
        /* Method to get the customer surname */
        return SURNAME;
    }

    void set_surname(std::string _surname) {
        /* Method to set the customer surname */
        SURNAME = preprocess_string(_surname);
    }

    void set_bday(std::string _bday) {
        /* Method to set the customer birthday */
        BDAY = validate_date(_bday);
    }

    void set_taxcode(std::string _tax_code) {
        /* Method to set the customer birthday */
        TAX_CODE = validate_tax_code(_tax_code);
    }

    int get_id() const{
        /* Method to get the customer id */
        return CUSTOMER_ID;
    }
    
    bool operator==(const Customer& other) const {
        return CUSTOMER_ID == other.CUSTOMER_ID; // Supponiamo che l'ID sia unico per ogni Customer
    }

    void write_on_csv(std::ofstream& output_csv_file){
        output_csv_file << CUSTOMER_ID << ","
        << NAME << ","
        << SURNAME << ","
        << BDAY << ","
        << TAX_CODE << std::endl;
    }

};

struct CustomerHash {
    std::size_t operator()(const std::string& key) const {
        return std::hash<std::string>{}(key);
    }
};

class CustomerManager {
private:
    // unordered_map with customer name as key
    std::unordered_map<std::string, std::vector<Customer>, CustomerHash> name_map;
    // unordered_map with customer surname as key
    std::unordered_map<std::string, std::vector<Customer>, CustomerHash> surname_map;

    void add_customer(const Customer& _customer, bool from_csv) {
        /*
        Function to add a customer to the two private data structures of
        the class CustomerManager. Moreover, in the case the value of
        the variable from_csv=false the function execute the method
        save_persistent_customer_id.

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

    int get_max_customer_id(void){
        /*
        Function to get the maximum value of the current CUSTOMER_ID in the
        name_map of the CustomerManager class.
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

    void save_persistent_customer_id(void){
        /*
        function to save next customer_id in a txt file in order to keep
        it persistent. 
        */

        // path for the persistent customer id
        std::string persistence_customer_id_file_path = "next_customer_id.txt";
        int current_max_customer_id = get_max_customer_id();
        std::ofstream file(persistence_customer_id_file_path);

        if (file.is_open()) {
            file << current_max_customer_id+1;
        }
    }

    int get_next_customer_id(void){
        std::string persistence_customer_id_file_path = "next_customer_id.txt";
        std::ifstream file(persistence_customer_id_file_path);

        // default value if the file does not exist or it is empty
        int next_customer_ID = 0;
        if (file.is_open()) {
            file >> next_customer_ID;
        }
        return next_customer_ID;
    }

    Customer ask_customer_infos(void){
        std::string input_name, input_surname, input_bday, input_tax_code;
        int next_customer_id;

        // get info to create a Customer object
        next_customer_id = get_next_customer_id();
        std::cout << "Insert the customer name: " << std::endl;
        std::cin >> input_name;
        std::cout << "Insert the customer surname: " << std::endl;
        std::cin >> input_surname;
        std::cout << "Insert the customer birth day (DD/MM/YYYY): " << std::endl;
        std::cin >> input_bday;
        std::cout << "Insert the customer tax code: " << std::endl;
        std::cin >> input_tax_code;

        Customer temp_customer(next_customer_id, input_name,
            input_surname, input_bday, input_tax_code);

        std::cout << "The customer you want to add is:\n" << std::endl;
        temp_customer.print_customer();
        
        return temp_customer;
    }

    std::vector<Customer> search_customer_by_name(void){
        /*
        Function that guide the user to search a customer by name.
        */
        std::vector<Customer> found_customers;
        std::string name_to_search;
        bool is_present = false;

        std::cout << "Insert the customer NAME you want to search: ";
        std::cin >> name_to_search;

        // preprocess the input with the same method to
        // define a customer
        name_to_search = preprocess_string(name_to_search);

        int length = name_to_search.length();
        std::string result(length, '*');

        for(const auto& pair: name_map){
            if (pair.first==name_to_search)
            {
                is_present = true;
                std::cout << "*************************"
                    << result << std::endl;
                std::cout << "The customers with name: "
                    << name_to_search << std::endl;
                std::cout << "*************************"
                    << result << std::endl;
                for (const auto& customer: pair.second)
                {
                    customer.print_customer();
                    std::cout << std::endl;
                    found_customers.push_back(customer);
                }
                // the name is the key, hence, there are no more
                // customers to find.
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

    std::vector<Customer> search_customer_by_surname(void){
        /*
        Function that guide the user to search a customer by surname.
        */
        std::vector<Customer> found_customers;
        std::string surname_to_search;
        bool is_present = false;

        std::cout << "Insert the customer SURNAME you want to search: ";
        std::cin >> surname_to_search;

        // preprocess the input with the same method to
        // define a customer
        surname_to_search = preprocess_string(surname_to_search);

        int length = surname_to_search.length();
        std::string result(length, '*');

        for(const auto& pair: surname_map){
            if (pair.first==surname_to_search)
            {
                is_present = true;
                std::cout << "*************************"
                    << result << std::endl;
                std::cout << "The customers with surname: "
                    << surname_to_search << std::endl;
                std::cout << "*************************"
                    << result << std::endl;
                for (const auto& customer: pair.second)
                {
                    customer.print_customer();
                    std::cout << std::endl;
                    found_customers.push_back(customer);
                }
                // the surname is the key, hence, there are no more
                // customers to find.
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

    std::vector<Customer> ask_search_customer_by_name(void){
        /*
        Function that drive the user to find a customer in the
        CustomerManager class by name. It use the template yes_or_no_choice
        to allow the user to decide if the result is correct or not.
        */
        std::vector<Customer> output;

        try
        {
            // Bind the member function to the current instance
            auto bound_ask_search_customer_by_name = std::bind(&CustomerManager::search_customer_by_name, this);
            
            // temporary customer
            auto temp_found_customers = yes_or_no_choice(bound_ask_search_customer_by_name);
            if (temp_found_customers.has_value()) {
                output = temp_found_customers.value();
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';

        }

        return output;
    }

    std::vector<Customer> ask_search_customer_by_surname(void){
        /*
        Function that drive the user to find a customer in the
        CustomerManager class by surname. It use the template yes_or_no_choice
        to allow the user to decide if the result is correct or not.
        */
        std::vector<Customer> output;

        try
        {
            // Bind the member function to the current instance
            auto bound_ask_search_customer_by_surname = std::bind(&CustomerManager::search_customer_by_surname, this);
            
            // temporary customer
            auto temp_found_customers = yes_or_no_choice(bound_ask_search_customer_by_surname);
            if (temp_found_customers.has_value()) {
                output = temp_found_customers.value();
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';

        }

        return output;
    }

    void delete_customer(Customer customer_to_remove){
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


public:
    // default constructor
    CustomerManager(void){
        /*
        The first operation is to save the customer_id of the CustomerManager
        class. When a user initialize for the first time the CustomerManager
        there are no customers in the library. Hence, the customer_id will be
        -1.
        */
        save_persistent_customer_id();
    }

    void add_ask_customer(void){
        /*
        Function that asks to the user to inser the customer information
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
    
    void read_customers_csv() {
        /*
        Function to read the CUSTOMERS CSV file. A customer csv must have 5
        fields that are in order: CUSTOMER_ID, NAME, SURNAME, BDAY, TAX_CODE. In fact, they are the
        required parameters for a Customer object.

        Arguments:
        ----------
        * filename (std::string), it is the name of the file to read as customers file.
        */

        std::string filename;

        std::cout << "Insert the customers CSV file name: ";
        std::cin >> filename;


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
        save_persistent_customer_id();
    }

    void write_customers_csv(void){

        std::string filename;

        std::cout << "Insert the customers CSV file name: ";
        std::cin >> filename;

        write_csv(
            filename,
            name_map,
            [this](std::ofstream& output_file){
                output_file << "CCUSTOMER_ID,NAME,SURNAME,BDAY,TAX_CODE"
                    << std::endl;
            },
            true
        );
    }

    std::vector<Customer> search_customer(void){
        /*
        Function that drive the user to search a customer by name or
        surname. And return a vector with the customers that match the
        research.
        */
        std::string query_search_customer = "Enter the number of the action you want to execute:\n" \
        "[1] Search customer by NAME.\n" \
        "[2] Search customer by SURNAME.\n" \
        "[3] Exit.";
        std::vector<int> possible_values = {1, 2, 3};
        int user_action;
        std::vector<Customer> temp_found_customers;

        user_action = select_integer_value(query_search_customer, possible_values);
        
        if(user_action==1) {
            temp_found_customers = ask_search_customer_by_name();
        }
        else if(user_action==2) {
            temp_found_customers = ask_search_customer_by_surname();
        }

        return temp_found_customers;
    }

    std::optional<Customer> get_customer_by_id(void){
        /*
        Function to get a customer by id. In particular, the first process
        is to find a customer by name or surname and the 
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
                std::cin >> cmd_input;

                std::cout << "\n" << std::endl;

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

    void ask_remove_customer(void){

        std::string query_rmv_customer = "Enter the number of the action you want to execute:\n" \
        "[1] Remove the customer.\n" \
        "[2] Exit.";
        std::vector<int> possible_values = {1, 2};
        int user_action;

        auto get_customer_result = get_customer_by_id();
        
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

    void modify_customer(void){

        std::string query_mod_customer = "Enter the number of the action you want to execute:\n" \
        "[1] Modify the customer NAME.\n" \
        "[2] Modify the customer SURNAME.\n" \
        "[3] Modify the customer BDAY.\n" \
        "[4] Modify the customer TAX_CODE.\n" \
        "[5] Modify all the customer information.\n" \
        "[6] Exit.";
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
                std::cout << "Enter the customer NAME: "
                    << std::endl;
                std::cin >> new_name;
                customer_to_modify.set_name(new_name);
            }
            else if(user_action==2)
            {
                std::string new_surname;
                std::cout << "Enter the customer SURNAME: "
                    << std::endl;
                std::cin >> new_surname;
                customer_to_modify.set_surname(new_surname);
            }
            else if(user_action==3)
            {
                std::string new_bday;
                std::cout << "Enter the customer BDAY: "
                    << std::endl;
                std::cin >> new_bday;
                customer_to_modify.set_bday(new_bday);
            }
            else if(user_action==4)
            {
                std::string new_tax_code;
                std::cout << "Enter the customer TAX_CODE: "
                    << std::endl;
                std::cin >> new_tax_code;
                customer_to_modify.set_taxcode(new_tax_code);
            }
            else if(user_action==5)
            {
                std::string new_name;
                std::string new_surname;
                std::string new_bday;
                std::string new_tax_code;

                std::cout << "Enter the customer NAME: "
                    << std::endl;
                std::cin >> new_name;
                customer_to_modify.set_name(new_name);

                std::cout << "Enter the customer SURNAME: "
                    << std::endl;
                std::cin >> new_surname;
                customer_to_modify.set_surname(new_surname);

                std::cout << "Enter the customer BDAY: "
                    << std::endl;
                std::cin >> new_bday;
                customer_to_modify.set_bday(new_bday);

                std::cout << "Enter the customer TAX_CODE: "
                    << std::endl;
                std::cin >> new_tax_code;
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

    void print_customers() const {
        /*
        Function to print alle the customer in the CustomerManager class by name.
        */
        for (const auto& pair : name_map) {
            std::cout << "NAME: " << pair.first << std::endl;
            for (const auto& customer : pair.second) {
                customer.print_customer();
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }
};

class Interaction{
    private:
        int CUSTOMER_ID;
        std::string INTERCTION_TYPE;
        bool FLAG_INTEREST;
        std::string PRODUCT_TYPE;
        std::string INTERACTION_DATE;
        int POLICY_ID;
        int QUOTE_ID;
    
    public:
        Interaction(void){
            CUSTOMER_ID = -1;
            INTERCTION_TYPE = "XXXXXX";;
            FLAG_INTEREST = false;
            PRODUCT_TYPE = "XXXXXX";
            INTERACTION_DATE = "00/00/0000";
            POLICY_ID = -1;
            QUOTE_ID = -1;
        }

        Interaction(int _customer_id, std::string _interaction_type, bool _flag_interest, std::string _produt_type, std::string _interaction_date, int _policy_id, int _quotes_id) : CUSTOMER_ID(_customer_id), INTERCTION_TYPE(preprocess_interaction_type(_interaction_type)), FLAG_INTEREST(_flag_interest), PRODUCT_TYPE(preprocess_product_type(_produt_type)), INTERACTION_DATE(validate_date(_interaction_date)), POLICY_ID(_policy_id), QUOTE_ID(_quotes_id) {}

        int get_customer_id(void) const{
            return CUSTOMER_ID;
        }

        int get_policy_id() const{
            return POLICY_ID;
        }

        int get_quote_id() const{
            return QUOTE_ID;
        }
};

struct InteractionHash {
    std::size_t operator()(const int& key) const {
        return std::hash<int>{}(key);
    }
};

class InteractionManager: public CustomerManager {
    private:
        std::unordered_map<int, std::vector<Interaction>, InteractionHash> interaction_map;
    
        int get_max_interaction_id(void){
            /*
            Function to get the maximum value of the current CUSTOMER_ID in the
            name_map of the CustomerManager class.
            */
            int max_customer_id;
            int current_id;

            // if there are no customer the CUSTOMER_ID is negative
            max_customer_id = -1;
            // find the maximum value of customer id in the current name_map
            for (const auto& pair : interaction_map) {
                current_id = pair.first;
                if (current_id>max_customer_id)
                {
                    max_customer_id = current_id;
                }
            }
            return max_customer_id;
        }

        int get_max_policy_id(void){
            /*
            Function to get the maximum value of the current POLICY_ID in the
            name_map of the CustomerManager class.
            */
            int max_id;
            int current_id;

            // if there are no customer the POLICY_ID is negative
            max_id = -1;
            // find the maximum value of customer id in the current name_map
            for (const auto& pair : interaction_map) {
                for (const auto& interaction : pair.second) {
                    current_id = interaction.get_policy_id();
                    if (current_id>max_id)
                    {
                        max_id = current_id;
                    }
                }
            }
            return max_id;
        }

        int get_max_quote_id(void){
            /*
            Function to get the maximum value of the current QUOTE_ID in the
            name_map of the CustomerManager class.
            */
            int max_id;
            int current_id;

            // if there are no customer the QUOTE_ID is negative
            max_id = -1;
            // find the maximum value of customer id in the current name_map
            for (const auto& pair : interaction_map) {
                for (const auto& interaction : pair.second) {
                    current_id = interaction.get_quote_id();
                    if (current_id>max_id)
                    {
                        max_id = current_id;
                    }
                }
            }
            return max_id;
        }

        void save_persistent_interaction_id(void){
            /*
            function to save next interaction_id in a txt file in order to keep
            it persistent. 
            */

            // path for the persistent customer id
            std::string persistence_interaction_id_file_path = "next_interaction_id.txt";
            int current_max_interaction_id = get_max_interaction_id();
            std::ofstream file(persistence_interaction_id_file_path);

            if (file.is_open()) {
                file << current_max_interaction_id+1;
            }
        }

        void save_persistent_policy_id(void){
            /*
            function to save next policy_id in a txt file in order to keep
            it persistent. 
            */

            // path for the persistent customer id
            std::string persistence_policy_id_file_path = "next_policy_id.txt";
            int current_max_policy_id = get_max_policy_id();
            std::ofstream file(persistence_policy_id_file_path);

            if (file.is_open()) {
                file << current_max_policy_id+1;
            }
        }

        void save_persistent_quote_id(void){
            /*
            function to save next quote_id in a txt file in order to keep
            it persistent. 
            */

            // path for the persistent customer id
            std::string persistence_quote_id_file_path = "next_quote_id.txt";
            int current_max_quote_id = get_max_quote_id();
            std::ofstream file(persistence_quote_id_file_path);

            if (file.is_open()) {
                file << current_max_quote_id+1;
            }
        }

        void add_interaction(const Interaction& _interaction, bool from_csv){
            /*
            Function to add a customer to the two private data structures of
            the class CustomerManager. Moreover, in the case the value of
            the variable from_csv=false the function execute the method
            save_persistent_customer_id.

            Arguments:
            ----------
            * _customer (Customer), customer object of the defined Customer class.
            * from_csv (bool), flag that indecates if the customer to add comes
                from a csv file or not.
            */
            interaction_map[_interaction.get_customer_id()].push_back(_interaction);
            if(!from_csv)
            {
                this->save_persistent_interaction_id();
            }
        }

        Interaction ask_interaction_info(void){

            // arguments to define an interaction
            int customer_id, policy_id, quotes_id;
            std::string interaction_type, product_type, interaction_date;
            bool flag_interest;

            // customer associated to the interaction
            auto get_customer_result = CustomerManager::get_customer_by_id();
            Customer customer_target;

            // interaction type from user
            std::string query_int_type = "\nEnter the number in brackets" \
            "that corresponds to the interaction you wish to add:\n" \
            "[1] APPOINTMENT.\n" \
            "[2] QUOTE.\n" \
            "[3] SIGN.\n";
            std::vector<int> possible_int_user_input = {1,2,3};
            int interaction_type_user_input;
            std::vector<std::string> possible_interactions = {"APPOINTMENT", "QUOTE", "SIGN"};

            // product type from user
            std::string query_prod_type = "\nEnter the number in brackets" \
            "that corresponds to the product related to the interaction:\n" \
            "[1] CAR.\n" \
            "[2] HEALTH.\n" \
            "[3] HOME.\n";
            std::vector<int> possible_prod_user_input = {1,2,3};
            int prod_type_user_input;
            std::vector<std::string> possible_products = {"CAR", "HEALTH", "HOME"};

            if (get_customer_result.has_value())
            {
                Customer customer_target = get_customer_result.value();

                interaction_type_user_input = select_integer_value(query_int_type, possible_int_user_input);
                interaction_type = possible_interactions[interaction_type_user_input-1];

                std::cout << "Insert the interation date (DD/MM/YYYY): ";
                std::cin >> interaction_date;
            }

            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;

            // X CUSTOMER_ID
            // X INTERCTION_TYPE
            //   FLAG_INTEREST
            //   PRODUCT_TYPE
            //   INTERACTION_DATE
            // X POLICY_ID
            // X QUOTE_ID
            return;
        }
    
    public:
        InteractionManager(void){
            this->save_persistent_interaction_id();
            this->save_persistent_policy_id();
            this->save_persistent_quote_id();
        }

        void ask_add_interaction(void){


            

        }

};

/**********/
/** MAIN **/
/**********/
int main() {
    // CustomerManager customer_manager;
    // // customer_manager.add_ask_customer();
    // // std::string filename;
    // Customer customer;

    // // std::cout << "Insert the customers file name: ";
    // // std::cin >> filename;

    // customer_manager.read_customers_csv();
    // // std::vector<Customer> customers = customer_manager.search_customer();
    // // auto get_customer_result = customer_manager.get_customer_by_id();
    // // if(get_customer_result.has_value()){
    // //     Customer customer = get_customer_result.value();
    // //     customer.print_customer();
    // // }
    // customer_manager.modify_customer();
    // customer_manager.print_customers();

    // customer_manager.ask_remove_customer();

    // customer_manager.print_customers();
    // customer_manager.write_customers_csv();
    // int final_output;
    // final_output = yes_or_no_choice(ask_sums);

    // std::cout << "Final output: " << final_output << std::endl;

    InteractionManager interaction_manager;

    return 0;
}

/*****************************************/
/* INITIALIZATION USER DEFINED FUNCTIONS */
/*****************************************/
std::string preprocess_string(const std::string& s) {
    std::string output = s;

    // Convert to uppercase
    std::transform(output.begin(), output.end(), output.begin(), ::toupper);

    output = remove_special_chars(output);

    return output;
}

std::string remove_special_chars(const std::string& input) {
    std::string result;
    result.reserve(input.size()); // Riserva spazio per migliorare l'efficienza

    // Copia solo i caratteri alfanumerici e gli spazi
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
        std::cout << "Birthday must be in the format DD/MM/YYYY.\n"
                  << "The base missing date is: 00/00/0000 " << std::endl;
        return "00/00/0000";
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
    std::regex tax_code_pattern(R"(^[A-Z0-9]+$)");
    return std::regex_match(tax_code, tax_code_pattern);
}

std::string validate_tax_code(const std::string& tax_code) {
    std::string upper_tax_code = tax_code;
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
        std::cout << "Do you want to stop the process?[y/n]" << std::endl;
        std::cin >> input_y_n;
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
        while((clean_char = getchar()) !='\n' && clean_char!=EOF);
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
    * vec (std::vector<int>), vector with the possible std::string values.
    * value (int), integer value to check.
    */
    auto it = std::find(vec.begin(), vec.end(), value);
    // If the iterator is not equalt to vec.end(), the value is
    // contained in vec
    return it != vec.end();
}

std::string preprocess_interaction_type(const std::string& interaction_type){
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
    bool correct_input = false;
    std::string cmd_input;
    int user_action;

    while (!correct_input)
    {
        std::cout << query << std::endl;
        std::cin >> cmd_input;
        std::cout << "\n" << std::endl;
        try {
                user_action = std::stoi(cmd_input);
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