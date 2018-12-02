//
//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//

#ifndef strategy_h
#define strategy_h

#include <string>
#include "resolve.h"

class Strategy {
public:
    virtual ~Strategy();
    virtual void dice_throw(Player* p) = 0;
    virtual void starting_position(Player* p) = 0;
    virtual std::string const see_strategy_name() = 0;
    virtual void resolve_dice(Player* p, std::vector<Player *> pls) = 0;
    virtual void move(Player* p) = 0;
    virtual void choose_to_move(Player* p) = 0;
    virtual void buy_cards(Player* p, std::vector<Card>& v, std::stack<Card>& s) = 0;

protected:
    Strategy();
};


#endif /* strategy_h */
