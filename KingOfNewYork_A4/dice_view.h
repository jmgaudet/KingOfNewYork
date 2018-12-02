//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
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
