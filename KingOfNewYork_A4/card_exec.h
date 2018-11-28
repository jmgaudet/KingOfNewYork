//
//  card_exec.h
//  KingOfNewYork_A4
//
//  Created by Jeremy Gaudet on 2018-11-26.
//  ID: #40045224
//  COMP_345_Section_N
//

#ifndef card_exec_h
#define card_exec_h


#include "observer.h"
#include "player.h"
#include "power_cards.h"

// CONCRETE OBSERVER

class CardExecution : public Observer {
private:
    Card* a_card;
public:
    CardExecution();
    CardExecution(Card* c);
    virtual ~CardExecution();
    void update() override;
    void update(Player* p) override;
    void execute(Player* p);
};




#endif /* card_exec_h */
