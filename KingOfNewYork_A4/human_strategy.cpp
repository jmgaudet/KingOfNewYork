//
//  human_strategy.cpp
//  KingOfNewYork_A3
//
//  Created by Jeremy Gaudet on 2018-11-17.
//  ID: #40045224
//  COMP_345_Section_N
//

#include "human_strategy.h"

Human::Human() {}
Human::~Human() {}

void Human::dice_throw(Player* p) {
    p->m_dice.roll_dice();
    p->m_dice.display_dice();
    p->m_dice.other_dice_rolls();
    
}


void Human::move(Player* p) {
    std::string current_loc = p->get_location();
    // this move() function REQUIRES the object player to already have a "current_location"
    if (current_loc.empty()) {
        std::cout << "You haven't started the game yet!" << std::endl;
        exit(1);
    }
    // if Player is in Manhattan and has NOT just been attacked, Player must move to next Manhattan_space:
    if (current_loc == "Manhattan" && !p->attacked) {
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
        std::cout << "Do you want to move from " << p->get_location() << "? [y/n]: ";
        if (get_yesNo())
            done = flee(p, current_loc);
        else
            done = true;
    }
}

// RETURNS: true if the Player* p successfully moves to the "selected_location"
bool Human::flee(Player* p, std::string current_loc) {
    p->display_branches(current_loc);
    std::string selected_location = capture_input();
    std::cout << "You have chosen: " << selected_location << std::endl;
    
    // verification and placement of player:
    if (p->validate_location(current_loc, selected_location)) {
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
    }
    return false;
}

void display_avail_cards(const std::vector<Card>& v) {
    // print to the CONSOLE the 3 available cards:
    for (const auto& card : v) {
        card_description(card);
        std::cout << '\n';
    }
}

void Human::buy_cards(Player* p, std::vector<Card>& v, std::stack<Card>& s) {
    bool done = false;
    while (!done) {
        std::cout << "\n//--------------------------------------------------------------------//\n"
        << "Do you want to purchase any of these Power cards? You have " << p->get_energy() << " ENERGY CUBES that you can spend.\n\n";
        display_avail_cards(v);
        std::cout << "\nThese are the ones available [y/n]: ";
        bool answer = get_yesNo();
        if (answer) {
            std::cout << "Enter the ID number of the card you wish to buy: ";
            int choice = 0;
            int place = 0;
            std::cin >> choice;
            std::cin.ignore();
            for (const auto& card : v) {
                if (card.ID == choice) {
                    if (card.cost <= p->get_energy()) {
                        p->add_energy(-card.cost);
                        p->add_to_hand(card);
                        std::cout << "\n * You have this many remaining ENERGY CUBES: " << p->get_energy() << "\n\n";
                        v.erase(v.begin()+place);   // if the player buys a card matching the correct ID, the card must be removed from the vector
                        // re-populate the available Power cards list:
                        while (v.size() < 3 && s.size() > 0) {
                            v.push_back(s.top());
                            s.pop();
                        }
                    } else
                        std::cout << "You don't have enough ENERGY CUBES to buy that card.\n";
                }
                place++;    // needed to map Player's choice to the vector of available cards
            }
        }
        else if (answer == false) {
            if (p->get_energy() >= 2) {
                std::cout << "Do you want to spend 2 ENERGY CUBES to discard these power cards? [y/n]: ";
                bool answer2 = get_yesNo();
                if (answer2 == true) {
                    v.clear();
                    while (v.size() < 3) {
                        v.push_back(s.top());
                        s.pop();
                    }
                    p->add_energy(-2);
                }
                else if (answer2 == false)
                    done = true;
            }
            else
                done = true;
        }
    }
}

void Human::resolve_dice(Player *p, std::vector<Player*> pls) {
    std::map<std::string, int> mapping;
    build_dice_map(mapping, p);
    while (!mapping.empty()) {
        show_map(mapping);
        std::cout << "Which type of dice do you want to resolve?\n\n";
        std::string choice = capture_input();
        transform(choice.begin(), choice.end(), choice.begin(), ::toupper);
        auto itr = mapping.find(choice);
        if (itr == mapping.end())
            std::cout << "Your choice of dice was not valid.\n\n";
        else {
            resolve_generator(itr, p, pls); // Human player goes back into the default resolve_generator located in "resolve.cpp"
            mapping.erase(itr);
        }
    }
}

void Human::choose_to_move(Player* p) {
    bool answer = get_yesNo();
    if (answer) {
        p->attacked = true;
        flee(p, p->get_location());
        p->attacked = false;
    }
}



void Human::starting_position(Player* p) {
    std::string start;
    std::cout << "Select " << p->get_monster_name() << "'s starting position:\n" << std::endl;
    // displaying all possible starting_positions:
    auto itr = p->m_graph.walk.begin();
    for( ; itr != p->m_graph.walk.end(); itr++) {
        if (itr->first != "Manhattan")
            std::cout << itr->first << '\n';
    }
    std::cout << "\n";
    while (true) {
        start = capture_input();
        auto itr2 = p->m_graph.walk.begin();
        for( ; itr2 != p->m_graph.walk.end(); itr2++) {
            if (itr2->first == start && itr2->first != "Manhattan") {
                if (itr2->second->num_players < 2) {
                    p->set_location(start);
                    itr2->second->num_players++;
                    itr2->second->players_list.push_back(p);
                    return;
                }
                else
                    std::cout << "\nThere are too many players already in that Borough.";
            }
        }
        std::cout << "\nYou have chosen an invalid starting position.\nSelect another Borough: ";
    }
}
