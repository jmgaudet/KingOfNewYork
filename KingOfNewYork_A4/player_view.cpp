//
//  player_view.cpp
//  KingOfNewYork_A3
//
//  Created by Jeremy Gaudet on 2018-11-14.
//  ID: #40045224
//  COMP_345_Section_N
//

#include "player_view.h"
#include <iostream>

PlayerView::PlayerView() {}

PlayerView::PlayerView(Player* p) {
    _player = p;
//    _player->Attach(this);
}

PlayerView::~PlayerView() {
    // upon destruction, it detaches itself from its player
    _player->Detach(this);
}

void PlayerView::register_view(Player* p) {
    _player->Attach(this);
}

void PlayerView::update() {
    monster_name = _player->get_monster_name();
    Phase state = _player->get_gamePhase();
    if (state == START || state == END_TURN)
        display_stat();
    else if (state == DICE)
        display_dice();
    else if (state == MOVE)
        display_move();
    else if (state == BUY_CARDS)
        display_card();
}

void PlayerView::display_stat() {
    std::cout << "\nUPDATED PLAYER VALUES" << std::endl;
    std::cout << "*NAME: " << monster_name << std::endl;
    std::cout << "*BOROUGH: " << _player->get_location() << std::endl;
    std::cout << "*VICTORY_POINTS: " << _player->get_victorypoints() << std::endl;
    std::cout << "*LIFE_POINTS: " << _player->get_lifepoints() << std::endl;
    std::cout << "*ENERGY: " << _player->get_energy() << "\n" << std::endl;
}

void PlayerView::display_dice() {
    std::cout << "\n" << monster_name << " rolls the dice!" << std::endl;
}

void PlayerView::display_move() {
    std::cout << "\nUPDATED PLAYER VALUES" << std::endl;
    std::cout << "*" << monster_name << " has moved to " << _player->get_location() << std::endl;
    auto itr = _player->m_graph.walk.find(_player->get_location());
    std::cout << "*Number of players currently in that borough --> " << itr->second->num_players << std::endl;
    if (itr->second->num_players > 0) {
        std::cout << "*Monsters in that borough: ";
        std::string separator;
        for (auto e : itr->second->players_list) {
            std::cout << separator << e->get_monster_name();
            separator = ", ";
        }
    }
    std::cout << "\n";
}

void PlayerView::display_card() {
    
}

