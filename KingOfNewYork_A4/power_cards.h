//
//  power_cards.h
//  KingOfNewYork_A3
//
//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//

#ifndef power_cards_h
#define power_cards_h

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>        // std::random_shuffle
#include <ctime>            // std::time
#include <cstdlib>          // std::rand, std::srand
#include "subject.h"

constexpr std::size_t NCARDS = 66;

class Card : public Subject {
public:
    int ID;
    std::string name;
    std::string type;
    int cost;
    std::string description;
    
    using power_cards = Card[NCARDS];
//    void initiate_cards(power_cards& fresh_deck);
//    void card_description(const Card& card);
//    void show_cards(const power_cards& deck);
//    void shuffle_cards(power_cards& deck);
};

//using power_cards = Card[NCARDS];
void initiate_cards(Card::power_cards& fresh_deck);
void card_description(const Card& card);
void show_cards(const Card::power_cards& deck);
void shuffle_cards(Card::power_cards& deck);

#endif /* power_cards_h */
