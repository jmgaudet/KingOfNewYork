//
//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//

#ifndef subject_h
#define subject_h

#include <vector>
#include <string>
#include <iostream>

class Observer;
class Player;

class Subject {
private:
    std::vector<Observer *> _observers;
public:
    virtual void Attach(Observer* o);
    virtual void Detach(Observer* o);
    virtual void Notify();  // have to keep this method as PUBLIC because it is used in places other than "player.cpp"
    virtual void Notify(Player* p);
    Subject();
    ~Subject();
};


#endif /* Subject_h */
