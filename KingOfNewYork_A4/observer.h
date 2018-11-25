//
//  Observer.h
//  KingOfNewYork_A3
//
//  Created by Jeremy Gaudet on 2018-11-14.
//  ID: #40045224
//  COMP_345_Section_N
//

#ifndef observer_h
#define observer_h

#include <string>



class Observer {
public:
    virtual ~Observer();
//    virtual void update(Phase game_phase) = 0;
    virtual void update() = 0;
protected:
    Observer();
};


#endif /* observer_h */
