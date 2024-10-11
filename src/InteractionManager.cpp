#include "my_template.h"
#include "InteractionManager.h"


// PRIVATE: Method to get the maximum value of customer_id
int InteractionManager::get_max_interaction_id(void){
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

// PRIVATE: Method to get the maximum value of policy_id
int InteractionManager::get_max_policy_id(void){
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

// PRIVATE: Method to get the maximum value of quote_id
int InteractionManager::get_max_quote_id(void){
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

// PRIVATE: Method to save the maximum value of interaction
void InteractionManager::save_persistent_interaction_id(void){
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

// PRIVATE: Method to save the maximum value of policy_id
void InteractionManager::save_persistent_policy_id(void){
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

// PRIVATE: Method to save the maximum value of quote_id
void InteractionManager::save_persistent_quote_id(void){
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

// PRIVATE: Method to get the next value of policy_id
int InteractionManager::get_next_policy_id(void){
    std::string persistence_policy_id_file_path = "next_policy_id.txt";
    std::ifstream file(persistence_policy_id_file_path);

    // default value if the file does not exist or it is empty
    int next_policy_ID = 0;
    if (file.is_open()) {
        file >> next_policy_ID;
    }
    return next_policy_ID;
}

// PRIVATE: Method to get the next value of quote_id
int InteractionManager::get_next_quote_id(void){
    std::string persistence_quote_id_file_path = "next_quote_id.txt";
    std::ifstream file(persistence_quote_id_file_path);

    // default value if the file does not exist or it is empty
    int next_quote_ID = 0;
    if (file.is_open()) {
        file >> next_quote_ID;
    }
    return next_quote_ID;
}
        
// PRIVATE: Method to add and interaction
void InteractionManager::add_interaction(const Interaction& _interaction, bool from_csv){
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
        this->save_persistent_policy_id();
        this->save_persistent_quote_id();
    }
}

// PRIVATE: Method to asks infos about an interaction
Interaction InteractionManager::ask_interaction_info(void){

    // arguments to define an interaction
    int customer_id;
    int policy_id=-1;
    int quote_id=-1;
    std::string interaction_type, product_type, interaction_date;
    bool flag_interest;

    bool correct_input=false;
    char input_y_n, clean_char;

    // customer associated to the interaction
    auto get_customer_result = CUSTOMER_MANAGER.get_customer_by_id();
    Customer customer_target;

    // interaction type from user
    std::string query_int_type = "\nEnter the number in brackets " \
    "that corresponds to the interaction you wish to add:\n" \
    "[1] APPOINTMENT.\n" \
    "[2] QUOTE.\n" \
    "[3] SIGN.\n";
    std::vector<int> possible_int_user_input = {1,2,3};
    int interaction_type_user_input;
    std::vector<std::string> possible_interactions = {"APPOINTMENT", "QUOTE", "SIGN"};

    // product type from user
    std::string query_prod_type = "\nEnter the number in brackets " \
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
        customer_id = customer_target.get_id();

        interaction_type_user_input = select_integer_value(query_int_type, possible_int_user_input);
        interaction_type = possible_interactions[interaction_type_user_input-1];

        if (interaction_type=="SIGN") {
            flag_interest = true;
            policy_id = this->get_next_policy_id();
        }
        else {
            while (!correct_input)
            {
                std::cout << "\nThe customer shown interest during the interaction?[y/n] ";
                std::cin >> input_y_n;                

                if (std::tolower(input_y_n)=='y') {
                    flag_interest = true;
                    correct_input = true;
                }
                else if (std::tolower(input_y_n)=='n') {
                    flag_interest = false;
                    correct_input = true;
                }
                else {
                    std::cout << "You type: " << input_y_n
                    << "\nYou must type 'y' or 'n'. Try again.\n"
                    << std::endl;
                }
                // clean buffer
                while((clean_char = getchar()) !='\n' && clean_char!=EOF);
            }
        }

        // ask product type information
        prod_type_user_input = select_integer_value(query_prod_type, possible_prod_user_input);
        product_type = possible_products[prod_type_user_input-1];
        
        // ask interaction date information
        std::cout << "Insert the interation date (DD/MM/YYYY): ";
        std::getline(std::cin, interaction_date);
        
        if (interaction_type=="QUOTE") {
            quote_id = this->get_next_quote_id();
        }
        
        // build the interaction requested
        Interaction new_interaction(
            customer_id,
            interaction_type,
            flag_interest,
            product_type,
            interaction_date,
            policy_id,
            quote_id
        );

        std::cout << "\nThe interaction you want to add is\n" << std::endl;

        VariadicTable<int, std::string, bool, std::string, std::string, long, int> vt_inter_header = create_vt_interaction_header();
        new_interaction.add_inter_row(vt_inter_header);
        vt_inter_header.print(std::cout);
        return new_interaction;
    }
    else{
        Interaction null_interaction;
        std::cout << "\nIt is not possible to add an interaction not linked to a customer.";
        return null_interaction;
    }
}

// PUBLIC: Specific constructor
InteractionManager::InteractionManager(CustomerManager& cm):CUSTOMER_MANAGER(cm) {
    this->save_persistent_interaction_id();
    this->save_persistent_policy_id();
    this->save_persistent_quote_id();
}

// PUBLIC: Method to ask and add an interaction
void InteractionManager::ask_add_interaction(void){
    if (CUSTOMER_MANAGER.presence_of_customers())
    {
        try
        {
            // Bind the member function to the current instance
            auto bound_ask_interaction_infos = std::bind(&InteractionManager::ask_interaction_info, this);
            
            // temporary customer
            auto temp_interaction = yes_or_no_choice(bound_ask_interaction_infos);
            
            if (temp_interaction.has_value()) {
                Interaction _temp_interaction = temp_interaction.value();
                Interaction null_interaction;
                if(_temp_interaction!=null_interaction){
                    this->add_interaction(_temp_interaction, false);
                }
            } else {
                std::cout << "Customer addition cancelled." << std::endl;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    else{
        std::cout << "The CRM is empty! It is not possible to add interactions." << std::endl;
    }
}

// PUBLIC: Method to show in standard out the interaction table
void InteractionManager::show_interactions(void){
    VariadicTable<int, std::string, bool, std::string, std::string, long, int> vt(
        {
            "CUSTOMER_ID", "INTERCTION_TYPE", "FLAG_INTEREST", "PRODUCT_TYPE",
            "INTERACTION_DATE", "POLICY_ID", "QUOTE_ID"});

    for(const auto& pair: interaction_map){
        for(const auto& interaction: pair.second){
            vt.addRow(
                interaction.get_customer_id(),
                interaction.get_interaction_type(),
                interaction.get_falg_interest(),
                interaction.get_product_type(),
                interaction.get_interaction_data(),
                interaction.get_policy_id(),
                interaction.get_quote_id()
            );
        }
    }

    vt.print(std::cout);
}

// PUBLIC: Method to save interaction map in a CSV
void InteractionManager::write_interactions_csv(void){
    std::string filename;
    
    std::cout << "Insert the customers CSV file name: ";
    std::getline(std::cin, filename);
    
    write_csv(
        filename,
        interaction_map,
        [this](std::ofstream& output_file){
            output_file << "CUSTOMER_ID,INTERCTION_TYPE,FLAG_INTEREST,"
                << "PRODUCT_TYPE,INTERACTION_DATE,POLICY_ID,QUOTE_ID"
                << std::endl;
        },
        true
    );
}

// PUBLIC: Method to upload an interaction CSV to the interaction map
void InteractionManager::read_intercations_csv(void){
    if (CUSTOMER_MANAGER.presence_of_customers())
    {
        // initialization of filename
        std::string filename;

        // get the filename
        std::cout << "Insert the interactions CSV file name: ";
        std::getline(std::cin, filename);
        
        read_csv(filename, [this](std::vector<std::string> fields) {
            // check the number of fileds
            if (fields.size() == 7) {
                try {
                    // try to extract the each filed with the correct data type
                    int _customer_id = std::stoi(fields[0]);
                    std::string _interction_type = fields[1];
                    bool _flag_interest = fields[2]!="0";
                    std::string _product_type = fields[3];
                    std::string _interaction_date = fields[4];
                    int _policy_id = std::stoi(fields[5]);
                    int _quote_id = std::stoi(fields[6]);

                    // create a temporary customer
                    Interaction _temp_interaction(
                        _customer_id,
                        _interction_type,
                        _flag_interest,
                        _product_type,
                        _interaction_date,
                        _policy_id,
                        _quote_id    
                    );

                    // add temporary customer
                    this->add_interaction(_temp_interaction, true);
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Conversion erorr for the record: " <<
                        fields[0] << ", " << fields[1] << ", " << fields[2] <<
                        ", " << fields[3] << ", " << fields[4] << ", " <<
                        fields[5] << ", " << fields[6] << std::endl;
                } catch (const std::out_of_range& e) {
                    // to manage errors due to a row with less fields than expected
                    std::cerr << "Out of range value for the record: " <<
                        fields[0] << ", " << fields[1] << ", " << fields[2] <<
                        ", " << fields[3] << ", " << fields[4] << ", " <<
                        fields[5] << ", " << fields[6] << std::endl;
                }
            } else {
                // to manage errors due to a row with different numbers of fields than expected
                std::cerr << "Wrong number of fields for the record: " << fields.size() << std::endl;
            }
        });

        // save the maximum value of customer_id the csv file
        this->save_persistent_interaction_id();
        this->save_persistent_policy_id();
        this->save_persistent_quote_id();
    }
    else{
        std::cout << "The CRM is empty! It is not possible to add interactions." << std::endl;
    }
}

// PUBLIC: Method to search interactions of a customer
void InteractionManager::search_interaction_of_customer(void){
    /*
    Method to search the interactions linked to a customer.
    */
    int customer_id;
    auto get_customer_result = CUSTOMER_MANAGER.get_customer_by_id();
    VariadicTable<int, std::string, bool, std::string, std::string, long, int> vt(
        {
            "CUSTOMER_ID", "INTERCTION_TYPE", "FLAG_INTEREST", "PRODUCT_TYPE",
            "INTERACTION_DATE", "POLICY_ID", "QUOTE_ID"});

    if(get_customer_result.has_value()){
        Customer _customer = get_customer_result.value();
        customer_id = _customer.get_id();

        for(const auto& interaction: interaction_map[customer_id]){
            vt.addRow(
                interaction.get_customer_id(),
                interaction.get_interaction_type(),
                interaction.get_falg_interest(),
                interaction.get_product_type(),
                interaction.get_interaction_data(),
                interaction.get_policy_id(),
                interaction.get_quote_id()
            );
        }

        vt.print(std::cout);
    }
    else{
        std::cout << "No customers that correspond to the research." << std::endl;
    }
}