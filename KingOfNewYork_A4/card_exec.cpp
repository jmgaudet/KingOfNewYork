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
    a_card->Attach(this);
}

CardExecution::~CardExecution() {
    a_card->Detach(this);
}

void CardExecution::update(Player* p) {
    std::cout << "\n\n\nYOU MADE IT HERE\n\n\n";
    std::string aaa = a_card->description;
    std::cout << a_card->description << std::endl;

}

void CardExecution::update() {
    // left empty
}

void CardExecution::execute() {
    
}
