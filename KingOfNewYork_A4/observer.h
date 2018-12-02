//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//

#ifndef observer_h
#define observer_h

#include <string>

class Player;

class Observer {
public:
    virtual ~Observer();
    virtual void update() = 0;
    virtual void update(Player* p) = 0;
protected:
    Observer();
};


#endif /* observer_h */
