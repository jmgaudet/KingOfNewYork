//
//  statistics_view.cpp
//  KingOfNewYork_A3
//
//  Created by Jeremy Gaudet on 2018-11-18.
//  Copyright © 2018 JeremyGaudet. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "statistics_view.h"

StatisticsView::StatisticsView() {}
StatisticsView::~StatisticsView() {
    _engine->Detach(this);
}

StatisticsView::StatisticsView(Engine* game) {
    _engine = game;
    _engine->Attach(this);
}

void StatisticsView::update() {
    display();
}

std::string StatisticsView::get_players_borough(std::string location) {
    std::string answer;
    if (_engine->my_board.walk.at(location)->num_players > 0) {
        std::string separator;
        for (auto e : _engine->my_board.walk.at(location)->players_list) {
            answer += separator + e->get_monster_name();
            separator = ", ";
        }
    }
    return answer;
}

void StatisticsView::display() {
    std::cout << "GAME STATS:" << std::endl;
    std::cout << "Numer of players currently in the game: " << _engine->vPlayers.size() << std::endl;
    std::cout << "Borough infographics: " << std::endl;
    std::cout << "  *Manhattan: [" << _engine->my_board.walk.at("Manhattan")->num_players << "]: " << get_players_borough("Manhattan") << std::endl;
    std::cout << "  *Bronx: [" << _engine->my_board.walk.at("Bronx")->num_players << "]: " << get_players_borough("Bronx") << std::endl;
    std::cout << "  *Queens: [" << _engine->my_board.walk.at("Queens")->num_players << "]: " << get_players_borough("Queens") << std::endl;
    std::cout << "  *Staten Island: [" << _engine->my_board.walk.at("Staten Island")->num_players << "]: " << get_players_borough("Staten Island") << std::endl;
    std::cout << "  *Brooklyn: [" << _engine->my_board.walk.at("Brooklyn")->num_players << "]: " << get_players_borough("Brooklyn") << std::endl;
    std::cout << "Victory_Points Chart:" << std::endl;
    for (const auto &vPlayer : _engine->vPlayers) {
        std::cout << "  " << vPlayer->get_monster_name();
        int x = vPlayer->get_victorypoints();
        std::cout << " [" << x << "]";
        std::cout << "\n";
    }

}

//void StatisticsView::update() {
//    display();
//}
