//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//

#ifndef player_view_h
#define player_view_h

#include "observer.h"
#include "player.h"

// CONCRETE OBSERVER

class PlayerView : public Observer {
private:
    std::string monster_name;
    Player* _player;
public:
    PlayerView();
    PlayerView(Player* p);
    virtual ~PlayerView();
    void update(Player* p) override;
    void update() override;
//    void register_view(Player* p);
    void display_stat();
    void display_dice();
    void display_move();
    void display_card();
};


#endif /* player_view_h */
