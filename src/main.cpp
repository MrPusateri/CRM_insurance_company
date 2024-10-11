#include "CustomerManager.h"
#include "InteractionManager.h"
#include "my_functions.h"



int main() {
    std::string welcome_msg = "Welcome in the CRM of InsuraPro Solutions.\n\n"\
        "Along the program you can chose actions to perform using the terminal.\n"\
        "There are two methods to interact with the  program  chose  insert  an\n"\
        "integer number related to an action, or  entering  the  character  'y'\n"\
        "(yes) or 'n' (no) for expressing a decision.\n\nYou are ready? Now we start!\n\n"\
        "The possible actions are:\n"\
        "[1] Start a blank CRM.\n"
        "[2] Upload a CSV file that contains a CRM like in the documentation.\n"\
        "[3] End the process.\n";
    std::vector<int> possible_welcome_action = {1,2,3};
    int welcome_action;

    std::string possible_actions_msg = "\nThe possible actions are:\n"\
        " [1] Upload a CSV  file that  contains a  CRM  with the  same structure\n"\
        "     presented in the documentation.\n"\
        " [2] Upload a CSV file that contains interactions with  customers  with\n"\
        "     the same rules in the documentation.\n"\
        " [3] Add a customer.\n"\
        " [4] Display all the customers.\n"\
        " [5] Edit a customer.\n"\
        " [6] Delete a customer.\n"\
        " [7] Search a customer.\n"\
        " [8] Add a new interaction.\n"\
        " [9] Display all the interactions.\n"\
        "[10] Search interactions of a customer.\n"\
        "[11] Save CRM data.\n"\
        "[12] Save interaction data.\n"\
        "[13] Save all and exit.\n"\
        "[14] Exit without saving.\n";
    std::vector<int> possible_std_actions = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    int std_action;
    bool flag_stop_all = false;
    
    welcome_action = select_integer_value(welcome_msg, possible_welcome_action);


    if (welcome_action==3)
    {
        std::cout << "\nSee you next time!" << std::endl;
        return 0;
    }
    
    CustomerManager customer_manager;
    InteractionManager interaction_manager(customer_manager);
    
    if (welcome_action==2)
    {
        customer_manager.read_customers_csv();
        std::cout << "\nThe CRM you uploaded is:\n" <<std::endl;
        customer_manager.print_customers();
    }

    // Select standard actions
    while (!flag_stop_all)
    {
        std_action = select_integer_value(possible_actions_msg, possible_std_actions);
        if (std_action==1)
        {
            // upload CRM
            customer_manager.read_customers_csv();
        }
        else if (std_action==2)
        {
            // upload interactions
            interaction_manager.read_intercations_csv();
        }
        else if (std_action==3)
        {
            // add customer
            customer_manager.add_ask_customer();
        }
        else if (std_action==4)
        {
            // display all customers
            customer_manager.print_customers();
        }
        else if (std_action==5)
        {
            // modify customer information
            customer_manager.modify_customer();
        }
        else if (std_action==6)
        {
            // delete customer
            customer_manager.ask_remove_customer();
        }
        else if (std_action==7)
        {
            // search a customer
            customer_manager.search_customer();
        }
        else if (std_action==8)
        {
            // add a new interaction
            interaction_manager.ask_add_interaction();
        }
        else if (std_action==9)
        {
            // display all interactions
            interaction_manager.show_interactions();
        }
        else if (std_action==10)
        {
            // search interactions of a customer
            interaction_manager.search_interaction_of_customer();
        }
        else if (std_action==11)
        {
            // save CRM data
            customer_manager.write_customers_csv();
        }
        else if (std_action==12)
        {
            // save interactions data
            interaction_manager.write_interactions_csv();
        }
        else if (std_action==13)
        {
            // save CRM data
            customer_manager.write_customers_csv();
            // save interactions data
            interaction_manager.write_interactions_csv();
            // exit
            flag_stop_all = true;
        }
        else if (std_action==14)
        {
            // exit
            flag_stop_all = true;
        }
        
        
    }
    

    return 0;
}