//
//  tokens.h
//  KingOfNewYork_A3
//
//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//

#ifndef tokens_h
#define tokens_h

#include <string>
#include <stack>

constexpr std::size_t NWEB = 13;
constexpr std::size_t NJINX = 13;
constexpr std::size_t NSOUVENIR = 5;
constexpr std::size_t NCARAPACE = 15;

struct Web_T {
    std::string def = "WEB_TOKEN: When you deal damage to Monsters, give them a Web token. "
                      "A Monster has one fewer reroll on his turn for each Web token he has. "
                      "A Monster can choose to use an ATTACK to discard a Web token instead of using it to attack.";
};
struct Jinx_T {
    std::string def = "CURSE_TOKEN: When you deal damage to Monsters, give each a Curse token. "
                      "Each time a Monster wants to reroll OUCH, he must spend 1 ENERGY_POINT for each Curse token he has. "
                      "A Monster may use a HEART to discard a Curse token instead of using it to heal.";
};
struct Souvenir_T {
    std::string def = "SOUVENIR_TOKEN: Place a Souvenir token in your current borough, "
                      "and in each borough you enter that does not already have a Souvenir token. "
                      "Gain 1 VICTORY_POINT and 1 ENERGY_POINT each time you place a Souvenir token.";
};
struct Carapace_T {
    std::string def = "CARAPACE_TOKEN: Your HEART_POINT maximum is increased by 2 as long as you have this card. "
                      "For each OUCH you roll, place a Carapace token on this card. "
                      "You can discard this card to heal 1 damage for each Carapace token on it.";
};

void init_tokens(std::stack<Web_T>& w, std::stack<Jinx_T>& j, std::stack<Souvenir_T>& s, std::stack<Carapace_T>& c);


//using web_tokens = std::stack<Web_T>;
//using jinx_tokens = Jinx_T[NJINX];
//using souvenir_tokens = Souvenir_T[NSOUVENIR];
//using carapace_tokens = Carapace_T[NCARAPACE];


#endif /* tokens_h */
