//
//  player_view.h
//  KingOfNewYork_A3
//
//  Created by Jeremy Gaudet on 2018-11-14.
//  ID: #40045224
//  COMP_345_Section_N
//

#ifndef player_view_h
#define player_view_h

#include "observer.h"
#include "player.h"

// CONCRETE OBSERVER

class PlayerView : public Observer {
public:
    PlayerView();
    PlayerView(Player* p);
    virtual ~PlayerView();
//    void update(Phase game_phase) override;
    void update() override;
//    void register_view(Player* p);
    void display_stat();
    void display_dice();
    void display_move();
    void display_card();
private:
    std::string monster_name;
    Player* _player;
};


#endif /* player_view_h */
