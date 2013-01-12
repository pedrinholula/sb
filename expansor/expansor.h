#ifndef EXPANSOR_H_INCLUDED
#define EXPANSOR_H_INCLUDED

#define BEGIN "BEGINMACRO"
#define END "ENDMACRO"

#include <iostream>
#include <map>
#include <utility>

typedef std::string str;

typedef std::pair<str, str> strp;

typedef std::map<str, strp> macro_t;
typedef macro_t::iterator macro_i;


void first_step(str in, macro_t &macro);
void second_step(str in, str out, macro_t &macro);

void print_macro(macro_t macro);
#endif // EXPANSOR_H_INCLUDED
