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
#include <random>
#include <iterator>

void initiate_cards(std::vector<Card>& pc) {
    std::ifstream ifs("/Users/jeremygaudet/Documents/Xcode/KingOfNewYork_A2/KingOfNewYork_A2/deck_info/cards.json");
    nlohmann::json j = nlohmann::json::parse(ifs);
    for (std::size_t index = 0; index < NCARDS; ++index) {
        
        Card fresh;
        fresh.ID =j["cards"][index]["id"];
        fresh.name = j["cards"][index]["name"];
        fresh.type = j["cards"][index]["type"];
        fresh.cost = j["cards"][index]["cost"];
        fresh.description = j["cards"][index]["desc"];
        pc.push_back(fresh);
    }
    //    shuffle_cards(fresh_deck);
}

// https://en.cppreference.com/w/cpp/algorithm/random_shuffle
template<class RandomIt, class URBG>
void shuffle(RandomIt first, RandomIt last, URBG&& g)
{
    typedef typename std::iterator_traits<RandomIt>::difference_type diff_t;
    typedef std::uniform_int_distribution<diff_t> distr_t;
    typedef typename distr_t::param_type param_t;
    
    distr_t D;
    diff_t n = last - first;
    for (diff_t i = n-1; i > 0; --i) {
        using std::swap;
        swap(first[i], first[D(g, param_t(0, i))]);
    }
}

void shuffle_cards(std::vector<Card>& pc) {
    std::random_device rd;
    std::mt19937 g(rd());
    
    std::shuffle(pc.begin(), pc.end(), g);
}

void card_description(const Card& card) {
    std::cout << "ID: " << card.ID << '\n';
    std::cout << "Name: " << card.name << '\n';
    std::cout << "Type: " << card.type << '\n';
    std::cout << "Cost: " << card.cost << '\n';
    std::cout << "Description: " << card.description << '\n';
}

void show_cards2(const std::vector<Card>& pc) {
    for (const auto& card : pc) {
        card_description(card);
        std::cout << std::endl;
    }
    std::cout << "==================================================================================\n" ;
}






//void initiate_cards(Card::power_cards& fresh_deck) {
//    std::ifstream ifs("/Users/jeremygaudet/Documents/Xcode/KingOfNewYork_A2/KingOfNewYork_A2/deck_info/cards.json");
//    nlohmann::json j = nlohmann::json::parse(ifs);
//    for (std::size_t index = 0; index < NCARDS; ++index) {
//        fresh_deck[index].ID = j["cards"][index]["id"];
//        fresh_deck[index].name = j["cards"][index]["name"];
//        fresh_deck[index].type = j["cards"][index]["type"];
//        fresh_deck[index].cost = j["cards"][index]["cost"];
//        fresh_deck[index].description = j["cards"][index]["desc"];
//    }
//}

//void shuffle_cards(Card::power_cards& deck) {
//    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//    shuffle(std::begin(deck), std::end(deck), std::default_random_engine(seed));

//    std::srand(unsigned(std::time(nullptr)));
//    std::random_shuffle(std::begin(deck), std::end(deck));
//    shuffle(deck + 2, deck + NCARDS, myrandom);     // the "deck + 2" leaves the two important GOAL cards on top
//}


//void initiate_observer(Card::power_cards& fresh_deck) {
//    for (std::size_t i = 0; i < NCARDS; i++) {
//
//    }
//}


//void show_cards(const Card::power_cards& deck) {
//    for (const auto& card : deck) {
//        card_description(card);
//        std::cout << std::endl;
//    }
//    std::cout << "==================================================================================\n" ;
//}



