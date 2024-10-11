#ifndef INTERACTION_H
#define INTERACTION_H

#include "VariadicTable.h"
#include <string>
#include <fstream>

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
        Interaction(void);

        Interaction(int _customer_id, std::string _interaction_type, bool _flag_interest,
            std::string _produt_type, std::string _interaction_date, int _policy_id, int _quotes_id);

        int get_customer_id(void) const;

        int get_policy_id() const;

        int get_quote_id() const;

        std::string get_interaction_type(void) const;

        bool get_falg_interest(void) const;

        std::string get_product_type(void) const;

        std::string get_interaction_data(void) const;

        void write_on_csv(std::ofstream& output_csv_file);

        void add_inter_row(VariadicTable<int, std::string, bool, std::string, std::string, long, int>& _vt);

        bool operator!=(const Interaction& other) const;

};

struct InteractionHash {
    std::size_t operator()(const int& key) const;
};

#endif // INTERACTION_H