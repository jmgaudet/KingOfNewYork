//
//  subject.cpp
//  KingOfNewYork_A3
//
//  Created by Jeremy Gaudet on 2018-11-14.
//  ID: #40045224
//  COMP_345_Section_N
//

#include "subject.h"
#include "observer.h"

Subject::Subject() {
    _observers = new std::list<Observer *>;
}

Subject::~Subject() {
//    delete _observers;
}

void Subject::Attach(Observer* o) {
    _observers->push_back(o);
}

void Subject::Detach(Observer* o) {
    _observers->remove(o);
}

void Subject::Notify() {
    std::list<Observer *>::iterator i = _observers->begin();
    for ( ; i != _observers->end(); ++i)
        (*i)->update();
}

void Subject::Notify(Player* p) {
    std::list<Observer *>::iterator i = _observers->begin();
    for ( ; i != _observers->end(); ++i)
        (*i)->update(p);
}
