//
//  human_strategy.h
//  KingOfNewYork_A3
//
//  Created by Jeremy Gaudet on 2018-11-17.
//  ID: #40045224
//  COMP_345_Section_N
//

#ifndef human_strategy_h
#define human_strategy_h


#include <iostream>
#include "strategy.h"


class Human : public Strategy {
public:
    Human();
    ~Human() override;
    std::string const see_strategy_name() override { return "Human"; };
    void dice_throw(Player* p) override;
    void starting_position(Player* p) override;
    void resolve_dice(Player *p, std::vector<Player*> pls) override;
//    bool extracted(const std::string &current_loc, Player *p);
    void move(Player* p) override;
    void choose_to_move(Player* p) override;
    bool flee(Player* p, std::string current_loc);
    void buy_cards(Player* p, std::vector<Card>& v, std::stack<Card>& s) override;
};

#endif /* human_strategy_h */
