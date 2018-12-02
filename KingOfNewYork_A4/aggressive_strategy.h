//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//

#ifndef aggressive_strategy_h
#define aggressive_strategy_h

#include <iostream>
#include "strategy.h"

class Aggressive : public Strategy {
public:
    Aggressive();
    ~Aggressive() override;
    std::string const see_strategy_name() override { return "Aggressive"; };
    void dice_throw(Player* p) override;
    void starting_position(Player* p) override;
    void find_aggressive_dice(Player* p);
    void resolve_dice(Player *p, std::vector<Player*> pls) override;
    void aggressive_d_attack(int x, Player *p, std::vector<Player *> pls);
    void choose_to_move(Player* p) override;
    void aggressive_d_destruction(int x, Player *p, std::vector<Player *> pls);
    void move(Player* p) override;
    bool flee(Player* p, std::string current_loc);
    void buy_cards(Player* p, std::vector<Card>& v, std::stack<Card>& s) override;


};


#endif /* aggressive_strategy_h */
