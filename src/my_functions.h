#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H

#include <string>
#include "VariadicTable.h"

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
VariadicTable<int, std::string, std::string, std::string, std::string> create_vt_customer_header(void);
VariadicTable<int, std::string, bool, std::string, std::string, long, int> create_vt_interaction_header(void);

#endif // MY_FUNCTIONS_H