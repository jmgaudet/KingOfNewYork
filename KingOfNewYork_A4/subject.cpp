//
//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//

#include "subject.h"
#include "observer.h"

Subject::Subject() {}

Subject::~Subject() {}

void Subject::Attach(Observer* o) {
    _observers.push_back(o);
}

void Subject::Detach(Observer* o) {
    _observers.erase(std::remove(_observers.begin(), _observers.end(), o), _observers.end());
}

void Subject::Notify() {
    std::vector<Observer *>::iterator i = _observers.begin();
    for ( ; i != _observers.end(); ++i)
        (*i)->update();
}

void Subject::Notify(Player* p) {
    std::vector<Observer *>::iterator i = _observers.begin();
    for ( ; i != _observers.end(); ++i)
        (*i)->update(p);
}
