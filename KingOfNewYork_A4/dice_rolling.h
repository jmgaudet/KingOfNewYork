//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//

#ifndef dice_rolling_h
#define dice_rolling_h

#include <array>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <random>
#include <set>
#include "input.h"
#include "subject.h"

//const int NUMBER_OF_DICE = 8;
const int NUM_DICE_FACES = 6;
const int MIN_DICE = 1;

class Dice : public Subject {
private:
    int member_num_of_dice = 6;     // this is set to "6", as it is the default number of dice being rolled
    std::vector<int> m_collection;
    bool special_roll = false;

public:
    void display_dice();
    void set_specialRoll(bool setting);
    int count_attack(std::vector<int> * v);
    Dice();
    ~Dice();
    void roll_dice();
    void roll_dice_again(const std::vector<int>& change_list);
    void other_dice_rolls();
    void tester();
    int get_random();
    std::vector<int>* get_collection();
    bool validate_change(const std::vector<int>& change_list);
};


static std::array<std::string, NUM_DICE_FACES> dice_names = {"ENERGY", "ATTACK", "DESTRUCTION", "HEAL", "CELEBRITY", "OUCH"};

#endif /* dice_rolling_h */
