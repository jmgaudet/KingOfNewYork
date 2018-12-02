//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//

#include <stdio.h>
#include "card_exec.h"

CardExecution::CardExecution() {}

CardExecution::CardExecution(Card* c) {
    a_card = c;
//    a_card->Attach(this);
}

CardExecution::~CardExecution() {
    a_card->Detach(this);
}

void CardExecution::update(Player* p) {
    std::cout << "\n" << p->get_monster_name() << " acquired: " << a_card->name << "\nDESC: " << a_card->description << std::endl;
    execute(p);
}

void CardExecution::update() {
    // left empty
}

void CardExecution::execute(Player* p) {
    if (a_card->ID == 3) {
        // "Heal 1 damage each time you destroy an Infantry."
    }
    
    else if (a_card->ID == 13) {
        // "+1 VICTORY_POINT, +8 ENERGY_POINT and take 3 damage."
        p->add_energy(8);
        p->add_victoryPoints(1);
        p->damage(3);
        // this is discard-type CARD:
        p->remove_from_hand(*a_card);
        delete this;
        a_card = nullptr;
    }
    
    else if (a_card->ID == 14) {
        p->add_victoryPoints(2);
        // this is discard-type CARD:
        p->remove_from_hand(*a_card);
        delete this;
        a_card = nullptr;
    }
    
    else if (a_card->ID == 18) {
        // "Whenever you take damage because of rolling OUCH, take 1 less damage."
    }
    
    else if (a_card->ID == 21) {
        // "Gain 1 VICTORY_POINT each turn you rolled at least 1 CELEBRITY."
    }
    
    else if (a_card->ID == 39) {
        // "Heal 1 damage at the start of your turn."
        // this is found inside of Manhattan_points().
    }
    
}




//"id": 18,
//"name": "Bullet Proof",
//"type": "keep",
//"cost": 4,
//"desc": "Whenever you take damage because of rolling OUCH, take 1 less damage."
