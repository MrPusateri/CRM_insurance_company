#include "Interaction.h"
#include "my_functions.h"


Interaction::Interaction(void){
    CUSTOMER_ID = -1;
    INTERCTION_TYPE = "XXXXXX";;
    FLAG_INTEREST = false;
    PRODUCT_TYPE = "XXXXXX";
    INTERACTION_DATE = "00/00/0000";
    POLICY_ID = -1;
    QUOTE_ID = -1;
}

Interaction::Interaction(int _customer_id, std::string _interaction_type,
    bool _flag_interest, std::string _produt_type, std::string _interaction_date,
    int _policy_id, int _quotes_id) :
    CUSTOMER_ID(_customer_id), INTERCTION_TYPE(preprocess_interaction_type(_interaction_type)),
    FLAG_INTEREST(_flag_interest), PRODUCT_TYPE(preprocess_product_type(_produt_type)),
    INTERACTION_DATE(validate_date(_interaction_date)), POLICY_ID(_policy_id), QUOTE_ID(_quotes_id) {}

int Interaction::get_customer_id(void) const{
    return CUSTOMER_ID;
}

int Interaction::get_policy_id() const{
    return POLICY_ID;
}

int Interaction::get_quote_id() const{
    return QUOTE_ID;
}

std::string Interaction::get_interaction_type(void) const{
    return INTERCTION_TYPE;
}

bool Interaction::get_falg_interest(void) const{
    return FLAG_INTEREST;
}

std::string Interaction::get_product_type(void) const{
    return PRODUCT_TYPE;
}

std::string Interaction::get_interaction_data(void) const{
    return INTERACTION_DATE;
}

void Interaction::write_on_csv(std::ofstream& output_csv_file){
    output_csv_file << CUSTOMER_ID << ","
    << INTERCTION_TYPE << ","
    << FLAG_INTEREST << ","
    << PRODUCT_TYPE << ","
    << INTERACTION_DATE << ","
    << POLICY_ID << ","
    << QUOTE_ID << std::endl;
}

void Interaction::add_inter_row(VariadicTable<int, std::string, bool, std::string, std::string, long, int>& _vt){
    _vt.addRow(
        CUSTOMER_ID,
        INTERCTION_TYPE,
        FLAG_INTEREST,
        PRODUCT_TYPE,
        INTERACTION_DATE,
        POLICY_ID,
        QUOTE_ID
    );
}

bool Interaction::operator!=(const Interaction& other) const {
    return CUSTOMER_ID != other.CUSTOMER_ID;
}

std::size_t InteractionHash::operator()(const int& key) const {
    return std::hash<int>{}(key);
}