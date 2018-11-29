//
//  dice_view.h
//  KingOfNewYork_A4
//
//  Created by Jeremy Gaudet on 2018-11-28.
//  Copyright © 2018 JeremyGaudet. All rights reserved.
//

#ifndef dice_view_h
#define dice_view_h

#include "observer.h"
#include "dice_rolling.h"

// CONCRETE OBSERVER

class Player;

class DiceView : public Observer {
private:
    Dice* _dice;
public:
    DiceView();
    DiceView(Dice* d);
    virtual ~DiceView();
    void update(Player* p) override;
    void update() override;
    void display();
};


#endif /* dice_view_h */
