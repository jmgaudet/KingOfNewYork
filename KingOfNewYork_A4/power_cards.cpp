//
//  power_cards.cpp
//  KingOfNewYork_A3
//
//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//

#include "power_cards.h"
#include "nlohmann/json.hpp"    // I'm using this to import the 66 power cards from a .json file

void initiate_cards(power_cards& fresh_deck) {
    std::ifstream ifs("/Users/jeremygaudet/Documents/Xcode/KingOfNewYork_A2/KingOfNewYork_A2/deck_info/cards.json");
    nlohmann::json j = nlohmann::json::parse(ifs);
    for (std::size_t index = 0; index < NCARDS; ++index) {
        fresh_deck[index].ID = j["cards"][index]["id"];
        fresh_deck[index].name = j["cards"][index]["name"];
        fresh_deck[index].type = j["cards"][index]["type"];
        fresh_deck[index].cost = j["cards"][index]["cost"];
        fresh_deck[index].description = j["cards"][index]["desc"];
    }
}

void card_description(const Card& card) {
    std::cout << "ID: " << card.ID << '\n';
    std::cout << "Name: " << card.name << '\n';
    std::cout << "Type: " << card.type << '\n';
    std::cout << "Cost: " << card.cost << '\n';
    std::cout << "Description: " << card.description << '\n';
}

// random number generator function:
int myrandom (int i) { return std::rand()%i; }

void shuffle_cards(power_cards& deck) {
    std::srand(unsigned(std::time(nullptr)));
    std::random_shuffle(deck + 2, deck + NCARDS, myrandom);     // the "deck + 2" leaves the two important GOAL cards on top
}

void show_cards(const power_cards& deck) {
    for (const auto& card : deck) {
        card_description(card);
        std::cout << std::endl;
    }
    std::cout << "==================================================================================\n" ;
}


