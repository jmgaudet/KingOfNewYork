//
//  moderate_strategy.h
//  KingOfNewYork_A3
//
//  Created by Jeremy Gaudet on 2018-11-16.
//  ID: #40045224
//  COMP_345_Section_N
//

#ifndef moderate_strategy_h
#define moderate_strategy_h

#include <iostream>
#include "strategy.h"


class Moderate : public Strategy {
public:
    Moderate();
    ~Moderate() override;
    std::string const see_strategy_name() override { return "Moderate"; };
    void dice_throw(Player* p) override;
    void find_moderate_dice(Player* p);
    void starting_position(Player* p) override;
    void resolve_dice(Player* p, std::vector<Player*> pls) override;
    void moderate_d_attack(int x, Player *p, std::vector<Player *> pls);
    void moderate_d_destruction(int x, Player *p, std::vector<Player *> pls);
    void move(Player* p) override;
    void choose_to_move(Player* p) override;
    bool flee(Player* p, std::string current_loc);
    void buy_cards(Player* p, std::vector<Card>& v, std::stack<Card>& s) override;

};


#endif /* moderate_strategy_h */
