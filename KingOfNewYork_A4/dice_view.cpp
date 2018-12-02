//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//

#include <stdio.h>
#include "dice_view.h"

DiceView::DiceView(Dice* d) {
    _dice = d;
}

DiceView::~DiceView() {
    _dice->Detach(this);
}


void DiceView::update(Player* p) {
    // left empty
}


void DiceView::update() {
    display();
}

void DiceView::display() {
    std::cout << "-----------\n";
    for (int k = 0; k < _dice->get_collection()->size(); k++) {
        std::cout << (k+1) << ".\t" << dice_names[(_dice->get_collection()->at(k))-1] << std::endl;
//        std::cout << (k+1) << ".\t" << dice_names[(m_collection[k])-1] << " \n";
    }
}

