//
//  input.h
//  KingOfNewYork_A3
//
//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//

#ifndef input_h
#define input_h

#include <iostream>
#include <sstream>
#include <string>


//int get_testing_choice();
std::string capture_input();
bool isValid_num(std::string input, int lower, int upper);
int get_digit(std::string s);
bool get_yesNo();



#endif /* input_h */
