//
//  card_exec.cpp
//  KingOfNewYork_A4
//
//  Created by Jeremy Gaudet on 2018-11-26.
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
    std::cout << p->get_monster_name() << " purchased: " << a_card->name << "\nDESC: " << a_card->description << std::endl;
    execute(p);
}

void CardExecution::update() {
    // left empty
}

void CardExecution::execute(Player* p) {
    if (a_card->ID == 14) {
        p->add_victoryPoints(2);
        p->remove_from_hand(*a_card);   // this is discard-type CARD
        a_card = nullptr;
    }
    else if (a_card->ID == 18) {
        // "Whenever you take damage because of rolling OUCH, take 1 less damage."
    }
}




//"id": 18,
//"name": "Bullet Proof",
//"type": "keep",
//"cost": 4,
//"desc": "Whenever you take damage because of rolling OUCH, take 1 less damage."
