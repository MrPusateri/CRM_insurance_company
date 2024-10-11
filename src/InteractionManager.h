#ifndef INTERACTION_MANAGER_H
#define INTERACTION_MANAGER_H

#include "CustomerManager.h"
#include "Interaction.h"

class InteractionManager{
    private:
        std::unordered_map<int, std::vector<Interaction>, InteractionHash> interaction_map;
        CustomerManager& CUSTOMER_MANAGER;
    
        // Method to get the maximum value of customer_id
        int get_max_interaction_id(void);

        // Method to get the maximum value of policy_id
        int get_max_policy_id(void);

        // Method to get the maximum value of quote_id
        int get_max_quote_id(void);

        // Method to save the maximum value of interaction
        void save_persistent_interaction_id(void);

        // Method to save the maximum value of policy_id
        void save_persistent_policy_id(void);

        // Method to save the maximum value of quote_id
        void save_persistent_quote_id(void);

        // Method to get the next value of policy_id
        int get_next_policy_id(void);

        // Method to get the next value of quote_id
        int get_next_quote_id(void);
        
        // Method to add and interaction
        void add_interaction(const Interaction& _interaction, bool from_csv);

        // Method to asks infos about an interaction
        Interaction ask_interaction_info(void);
    
    public:
        // Specific constructor
        InteractionManager(CustomerManager& cm);

        // PUBLIC: Method to ask and add an interaction
        void ask_add_interaction(void);

        // PUBLIC: Method to show in standard out the interaction table
        void show_interactions(void);

        // PUBLIC: Method to save interaction map in a CSV
        void read_intercations_csv(void);

        // PUBLIC: Method to upload an interaction CSV to the interaction map
        void write_interactions_csv(void);

        // Method to search interactions of a customer
        void search_interaction_of_customer(void);
};


#endif // INTERACTION_MANAGER_H