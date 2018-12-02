//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//


#include "dice_rolling.h"

Dice::Dice() : m_collection(member_num_of_dice) {};
Dice::~Dice() {}

void Dice::roll_dice() {
    for (int i = 0; i < member_num_of_dice; i++)
        m_collection[i] = get_random();
    Notify();
}

std::vector<int>* Dice::get_collection() {
    return &m_collection;
}

int Dice::count_attack(std::vector<int> *v) {
    int a = 0;
    for (int e : *v) {
        if (e == 2)
            a++;
    }
    return a;
}



void Dice::set_specialRoll(const bool setting) {
    if (setting != 0) {
        member_num_of_dice = 8;
        m_collection.resize(static_cast<unsigned long>(member_num_of_dice));
    }
    if (setting == 0) {
        member_num_of_dice = 6;
        m_collection.resize(static_cast<unsigned long>(member_num_of_dice));
    }
}



void Dice::other_dice_rolls() {
    int turns = 1;
    std::cout << "Do you want to roll the dice again?" << std::endl;
    bool answer = get_yesNo();
    while (answer && (turns <= 2)) {
        std::cout << "Which dice you want to *CHANGE* ?\n(Specify an index between 1 and 6, separated by a spaces):" << std::endl;
        std::string line = capture_input();
        std::istringstream os(line);
        std::istream_iterator<int> begin(os), end;
        std::vector<int> values(begin, end);
        if (validate_change(values))
            roll_dice_again(values);
        else{
            std::cout << "ERROR: Incorrect input -- those dice cannot be rolled. Try again." << std::endl;
            continue;
        }
        Notify();
        turns++;
        if (turns <= 2) {
            std::cout << "\n\nDo you want to roll again? ";
            answer = get_yesNo();
        }
    }
}

void Dice::roll_dice_again(const std::vector<int>& change_list) {
    for (int i = 0; i < member_num_of_dice; i++) {
        for (int j : change_list) {
            if (j == (i+1))
                m_collection[i] = get_random();
        }
    }
}

void Dice::display_dice() {
//    std::cout << "Dice codes: [ ";
//    for (int j = 0; j < member_num_of_dice; j++) {
//        std::cout << m_collection[j] << " ";
//    }
    std::cout << "-----------\n";
    for (int k = 0; k < member_num_of_dice; k++) {
        std::cout << (k+1) << ".\t" << dice_names[(m_collection[k])-1] << " \n";
    }
}

bool Dice::validate_change(const std::vector<int>& change_list) {
    if (change_list.size() > 6) {
        return false;
    }
    for (int i : change_list) {
        if (i < 1 || i > 6)
            return false;
    }
    return true;
}

void Dice::tester() {
    int one = 0, two = 0, three = 0, four = 0, five = 0, six = 0;
    std::cout << "Testing the randomness of the dice rolls by rolling 1,000,000 times:\n";
    for (int k = 0; k < 1000000; k++) {
        int roll;
        roll = get_random();
        if (roll==1)
            one++;
        else if (roll==2)
            two++;
        else if (roll==3)
            three++;
        else if (roll==4)
            four++;
        else if (roll==5)
            five++;
        else if (roll==6)
            six++;
    }
    std::cout << "Dice count: [ " << one << ", " << two << ", " << three << ", " << four << ", " << five << ", " << six << " ]\n\n";
}

int Dice::get_random() {
    int roll = rand() % (NUM_DICE_FACES - MIN_DICE + 1) + MIN_DICE;
    return roll;
}

