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
        delete a_card;
        a_card = nullptr;
    }
}
