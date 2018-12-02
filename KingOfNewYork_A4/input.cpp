//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//

#include "input.h"

std::string capture_input() {
    std::cin.clear();
    std::string str;
    std::getline(std::cin, str);
    std::cin.clear();
    return str;
}

bool validate(int c, int l, int u) {
    return c >= l && c <= u;
}

int get_digit(std::string s) {
    int number = -1;
    std::istringstream iss(s);
    iss >> number;
    return number;
}


bool isValid_num(std::string input, int lower, int upper) {
    int choice = -1;
    std::istringstream iss(input);
    iss >> choice >> std::ws;
    return validate(choice, lower, upper) && iss.eof();
}

bool get_yesNo() {
    std::cin.clear();
    std::string yesNo = capture_input();
    return (yesNo == "yes") || (yesNo == "y") || (yesNo == "YES") || (yesNo == "Y");
}




