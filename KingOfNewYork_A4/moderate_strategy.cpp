//
//  moderate_strategy.cpp
//  KingOfNewYork_A3
//
//  Created by Jeremy Gaudet on 2018-11-16.
//  ID: #40045224
//  COMP_345_Section_N
//

#include "moderate_strategy.h"

Moderate::Moderate() {}
Moderate::~Moderate() {}

void Moderate::dice_throw(Player* p) {
    p->m_dice.roll_dice();      // AI will use the same first two functions as Human Players
    p->m_dice.display_dice();
    find_moderate_dice(p);
}

void Moderate::find_moderate_dice(Player* p) {
    int turns = 1;
    while (turns <= 2) {
        std::vector<int> values;
        std::vector<int> *c = p->m_dice.get_collection();
        int i = 1;
        for (int e : *c) {
            if (e != 1 && e != 4)
                values.push_back(i);
            i++;
        }
        if (values.size() != 0) {
            p->m_dice.roll_dice_again(values);
            p->m_dice.display_dice();
        }
        turns++;
    }
}

void Moderate::moderate_d_attack(int x, Player *p, std::vector<Player *> pls) {
    if (p->m_in_manhattan) {
        for (Player* player : pls) {
            if (!player->m_in_manhattan)
                player->damage(x);
        }
    }
    else {
        for (Player* player : pls) {
            if (player->m_in_manhattan) {
                player->damage(x);
                std::cout << player->get_monster_name() << " in Manhattan took damage! Does " << player->get_monster_name() << " want to flee to another borough? " << std::endl;
                player->execute_choice_to_move(player);
            }
        }
    }
}

void Moderate::resolve_dice(Player* p, std::vector<Player*> pls) {
    std::map<std::string, int> mapping;
    build_dice_map(mapping, p);
    while (!mapping.empty()) {
        show_map(mapping);
        std::cout << "Which type of dice do you want to resolve?\n\n";
        auto itr = mapping.begin();
        std::advance(itr, rand() % mapping.size());
        std::cout << p->get_monster_name() << " has chosen: " << itr->first << std::endl;
        if (itr->first == "ATTACK")
            moderate_d_attack(itr->second, p, pls);
        else if (itr->first == "DESTRUCTION")
            moderate_d_destruction(itr->second, p, pls);
        else
            resolve_generator(itr, p, pls); // if the dice is neither of the above, then it resolves the same as a Human player
        mapping.erase(itr);
    }
}

void Moderate::move(Player* p) {
    std::string current_loc = p->get_location();
    // this move() function REQUIRES the object player to already have a "current_location"
    if (current_loc.empty()) {
        std::cout << "You haven't started the game yet!" << std::endl;
        exit(1);
    }
    // if Player is in Manhattan and has NOT just been attacked, Player must move to next Manhattan_space:
    if (current_loc == "Manhattan" && p->attacked != true) {
        std::cout << "You are currently in Manhattan, which means you cannot move on this turn.\n";
        if (p->get_zone() == LOWER) { p->set_zone(MIDDLE); }
        if (p->get_zone() == MIDDLE) { p->set_zone(UPPER); }
        return;
    }
    // if there's no Player currently in Manhattan, Player must move to Manhattan:
    auto it = p->m_graph.walk.find("Manhattan");
    if (it->second->num_players == 0) {
        std::cout << "There is no Player currently in Manhattan, so " << p->get_monster_name() << " must move there.\n";
        // fix the values at the OLD borough:
        p->m_graph.walk.at(current_loc)->num_players--;
        p->m_graph.walk.at(current_loc)->players_list.remove(p);
        
        // set the values Manhattan:
        p->set_location("Manhattan");
        it->second->num_players++;
        it->second->players_list.push_back(p);
        p->m_in_manhattan = true;
        p->set_zone(LOWER);
        p->add_victoryPoints(1);
        p->Notify();
        return;
    }
    bool done = false;
    while (!done) {
        std::cout << "Do you want to move from " << p->get_location() << "? [y/n]: Yes" << std::endl;
        
        done = flee(p, current_loc);
        
    }
}

void Moderate::moderate_d_destruction(int x, Player *p, std::vector<Player *> pls) {
    auto itr = p->m_graph.walk.find(p->get_location())->second;
    itr->print_avail_tiles();
    
    // WHILE the player still has DESTRUCTION dice to use:
    while (can_destroy(itr->revealed_tiles, x)) {
        std::cout << "\nWhich do you want to destroy?\n";
        int pos = 0;
        for (auto& t : itr->revealed_tiles) {
            if (t.first.alive) {
                if (t.first.durability <= x) {
                    std::cout << "You have chosen: [" << pos+1 << "]" << std::endl;
                    t.first.alive = false;
                    get_reward(p, t.first.type, t.first.durability);
                    x -= t.first.durability;
                    if (itr->hidden_buildings.size() > 0) {
                        itr->revealed_tiles.push_back(itr->hidden_buildings.top());
                        itr->hidden_buildings.pop();
                    }
                    itr->print_avail_tiles();
                }
            }
            else {
                if (t.second.tag) {
                    if (t.second.durability <= x) {
                        std::cout << "You have chosen: [" << pos+1 << "]" << std::endl;
                        t.second.alive = false;
                        get_reward(p, t.second.type, t.second.durability);
                        x -= t.second.durability;
                        remove_unit_tile(itr->revealed_tiles, pos);
                        itr->print_avail_tiles();
                    }
                }
            }
            pos++;
        }
    }
    // The TAG for each new UNIT must be switched to TRUE so that the unit can be destroyed only on the next turn
    for (auto& t : itr->revealed_tiles) {
        if (!t.first.alive)
            t.second.tag = true;
    }
}



// RETURNS: true if the Player* p successfully moves to the "selected_location"
bool Moderate::flee(Player* p, std::string current_loc) {
    std::cout << "\nWhere do you want to move to?" << std::endl;
    //    p->display_branches(current_loc);
    //    auto itr = p->m_graph.walk.begin();
    std::string selected_location;
    bool valid = false;
    while (!valid) {
        auto itr = p->m_graph.walk.begin();
        std::advance(itr, rand() % p->m_graph.walk.size());
        selected_location = itr->second->borough;
        if (selected_location == "Manhattan") {
            if (itr->second->num_players >= 1)
                continue;
        }
        else {
            if (itr->second->num_players >= 2)
                continue;
        }
        valid = true;
    }
    std::cout << "You have chosen: " << selected_location << std::endl;
    if (selected_location == "Manhattan") {
        p->m_in_manhattan = true;
        p->set_zone(LOWER);
    }
    else {
        p->m_in_manhattan = false;
        p->set_zone(OUTSIDE);
    }
    // fix the values at the OLD borough:
    p->m_graph.walk.at(current_loc)->num_players--;
    p->m_graph.walk.at(current_loc)->players_list.remove(p);
    
    p->set_location(selected_location);
    
    // fix the values at the NEW borough:
    p->m_graph.walk.at(selected_location)->num_players++;
    p->m_graph.walk.at(selected_location)->players_list.push_back(p);
    
    p->Notify();
    return true;
    
    return false;
}

void Moderate::buy_cards(Player* p, std::vector<Card>& v, std::stack<Card>& s) {
    
}

void Moderate::choose_to_move(Player* p) {
    if (p->get_lifepoints() < 8) {  // a Moderate player will flee Manhattan quickly
        p->attacked = true;
        flee(p, p->get_location());
        p->attacked = false;
    }
    else
        std::cout << "\n- \"Nope, not this time. I am a Moderate_Player.\"" << std::endl;
}



void Moderate::starting_position(Player* p) {
    std::vector<std::string> starting_boroughs = {"Bronx","Queens","Brooklyn","Staten Island"};
    while (true) {
        int loc = rand() % 4;
        auto itr = p->m_graph.walk.at(starting_boroughs[loc]);
        if (itr->num_players < 2){
            p->set_location(starting_boroughs[loc]);
            itr->num_players++;
            itr->players_list.push_back(p);
            return;
        }
    }
}
