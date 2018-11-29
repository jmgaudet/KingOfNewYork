//
//  resolve.cpp
//  KingOfNewYork_A3
//
//  Created by Jeremy Gaudet on 2018-11-01.
//  ID: #40045224
//  COMP_345_Section_N
//

#include <stdio.h>
#include "resolve.h"


void show_map(const std::map<std::string, int> &mapping) {
    std::cout << "\n";
    for (auto& e : mapping)
        std::cout << e.first << " => " << e.second << std::endl;
}

void build_dice_map(std::map<std::string, int> &mapping, Player *p) {
    for (int j = 1; j <= NUM_DICE_FACES; j++) {
        int container = 0;
        for (int i : *(p->m_dice.get_collection())) {
            if (i == j)
                container++;
        }
        if (container > 0)
            mapping.emplace(dice_names[j-1], container);
    }
}

void resolve_dice(Player *p, std::vector<Player*> pls) {
    
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
            resolve_generator(itr, p, pls);
            mapping.erase(itr);
        }
    }
}

void resolve_generator(const std::map<std::string, int>::iterator &itr, Player *p, std::vector<Player *> pls) {
    std::cout << "[Inside resolve_generator]\n";
    if (itr->first == "ENERGY")
        d_energy(itr->second, p);
    else if (itr->first == "ATTACK")
        d_attack(itr->second, p, pls);
    else if (itr->first == "DESTRUCTION")
        d_destruction(itr->second, p, pls);
    else if (itr->first == "HEAL")
        d_heal(itr->second, p);
    else if (itr->first == "CELEBRITY")
        d_celeb(itr->second, p, pls);
    else
        d_ouch(itr->second, p, pls);
}



void d_energy(int x, Player *p) {
    p->add_energy(x);
    std::cout << p->get_monster_name() << " now has " << p->get_energy() << " ENERGY CUBES\n";
}

void d_attack(int x, Player *p, std::vector<Player *> pls) {
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

// This is needed to delete a Tile from the vector in the method d_destruction():
//template <typename block>
void remove_unit_tile(block& b, size_t pos) {
    auto itr = b.begin();
    std::advance(itr, pos);
    b.erase(itr);
}

void get_reward(Player* p, std::string type, int dur) {
    if (type == "Office")
        p->add_energy(dur);
    else if (type == "Power plant")
        p->add_victoryPoints(dur);
    else if (type == "Hospital")
        p->healer(dur);
    else if (type == "Infantry")
        p->healer(dur-1);
    else if (type == "Jet")
        p->add_energy(dur-1);
    else if (type == "Tank")
        p->add_victoryPoints(dur - 1);
}


//template <typename block>
bool can_destroy(block& b, int x) {
    for (auto itr = b.begin(); itr != b.end(); ++itr) {
        if (itr->first.alive) {
            if (itr->first.durability <= x)
                return true;
        } else {
            if (itr->second.durability <= x)
                return true;
        }
    }
    std::cout << "\nYou do not have the required number of DESTRUCTION dice to destroy any buildings or units.\n\n";
    return false;
}

bool verify_choice(int c, int max) {
    return c > 0 && c <= max;
}



void d_destruction(int x, Player *p, std::vector<Player *> pls) {
    auto itr = p->m_graph.walk.find(p->get_location())->second;
    itr->print_avail_tiles();

    // WHILE the player still has DESTRUCTION dice to use:
    while (can_destroy(itr->revealed_tiles, x)) {
        std::cout << "\nWhich do you want to destroy?\n";
        std::string s = capture_input();
        if (isValid_num(s, 1, static_cast<int>(itr->revealed_tiles.size()))) {
            int choice = get_digit(s)-1;
            if (itr->revealed_tiles[choice].first.alive) {    // if the Tile at "choice" is a BUILDING:
                if (itr->revealed_tiles[choice].first.durability <= x) {
                    itr->revealed_tiles[choice].first.alive = false;
                    get_reward(p, itr->revealed_tiles[choice].first.type, itr->revealed_tiles[choice].first.durability);
                    x -= itr->revealed_tiles[choice].first.durability;
                    if (itr->hidden_buildings.size() > 0) {
                        itr->revealed_tiles.push_back(itr->hidden_buildings.top());
                        itr->hidden_buildings.pop();
                    }
                } else
                    std::cout << p->get_monster_name() << " doesn't have enough DESTRUCTION dice to destroy that BUILDING\n";
            } else {  // if the Tile at "choice" is a UNIT:
                if (itr->revealed_tiles[choice].second.tag) {
                    if (itr->revealed_tiles[choice].second.durability <= x) {
                        itr->revealed_tiles[choice].second.alive = false;
                        get_reward(p, itr->revealed_tiles[choice].second.type,
                                   itr->revealed_tiles[choice].second.durability);
                        x -= itr->revealed_tiles[choice].second.durability;
                        remove_unit_tile(itr->revealed_tiles, choice);
                    } else
                        std::cout << p->get_monster_name() << " doesn't have enough DESTRUCTION dice to destroy that UNIT\n";
                } else
                    std::cout << "That UNIT cannot be targetted for destruction on this TURN.\n";
            }
            itr->print_avail_tiles();
        }
    }
    // The TAG for each new UNIT must be switched to TRUE so that the unit can be destroyed only on the next turn
    for (auto& t : itr->revealed_tiles) {
        if (!t.first.alive)
            t.second.tag = true;
    }
}

void d_heal(int x, Player *p) {
    if (p->m_in_manhattan) {
        std::cout << "Since " << p->get_monster_name() << " is in Manhattan, HEAL dice have no effect.\n";
        return;
    }
    p->healer(x);
    std::cout << p->get_monster_name() << " healed by +" << x << ". " << p->get_monster_name() << " now has " << p->get_lifepoints() << " LIFE POINTS.\n";
}

void d_celeb(int x, Player *p, std::vector<Player *> pls) {
    std::string myString = "Superstar";
    // next line creates an ITERATOR that SEARCHES for the Superstar card in Player p's hand:
    std::vector<Card>::const_iterator it;
    for (it = p->get_hand().begin(); it != p->get_hand().end(); it++) {
        if (it->name == myString) {
            p->add_victoryPoints(x);
            return;
        }
    }
    // player does NOT have the Superstar card
//    auto itr = find_if(p->get_hand().begin(), p->get_hand().end(), [&myString](const Card& obj) {return obj.name == myString;});
//    if (itr != p->get_hand().end())  // this means that the player HAS the Superstar card
//        p->add_victoryPoints(x);
    if (x >= 3) {
            // Here, the player should be ASSIGNED the Superstar card
//            for (Player &player : *pls) {
//                auto itr2 = find_if(player.get_hand().begin(), player.get_hand().end(), [&myString](const Card& obj) {return obj.name == myString;});
//                player.get_hand().erase(itr2);  // this erases the card from another player's hand
//                   // have to give the current player the SUPERSTAR card here
//            }
        p->add_victoryPoints(x - 3);
        std::cout << p->get_monster_name() << " takes the SUPERSTAR card and gains " << (x-3) << " VICTORY POINTS\n";
        return;
    }
    std::cout << p->get_monster_name() << " doesn't have either the SUPERSTAR card or the minimum number of CELEBRITY dice to take it.\n";
}

void d_ouch(int x, Player *p, std::vector<Player *> pls) {
//    if (p->check_card_hand(18))
//        x -= 1;
    if (x == 1 || x == 2) {
        auto itr = p->m_graph.walk.find(p->get_location())->second;
        int unit_count = 0;
        for (auto& t : itr->revealed_tiles) {
            if (!t.first.alive)     // count all the active UNITS in the player's borough (by checking to see if the BUILDING is dead).
                unit_count++;
        }
        if (x == 1) {
            if (p->check_card_hand(18) && unit_count > 0)
                unit_count -= 1;
            p->damage(unit_count);
            std::cout << "BAM POW KABOOM! " << p->get_monster_name() << " takes " << unit_count << " damage!\n";
        }
        else {
            for (auto& player : itr->players_list) {
                if ((p->check_card_hand(18)) && (player->get_monster_name() == p->get_monster_name()) && (unit_count > 0))
                    player->damage(unit_count-1);
                else
                    player->damage(unit_count);
                std::cout << "BAM POW KABOOM! " << player->get_monster_name() << " takes " << unit_count << " damage!\n";
                player->Notify();
            }
        }
    }
    else if (x >= 3) {
        auto itr2 = p->m_graph.walk.begin();
        for ( ; itr2 != p->m_graph.walk.end(); ++itr2) {
            // for every BOROUGH:
            int unit_count = 0;
            for (auto& t : itr2->second->revealed_tiles) {
                if (!t.first.alive)     // count all the active UNITS in the player's borough (by checking to see if the BUILDING is dead).
                    unit_count++;
            }
            for (auto& player : itr2->second->players_list) {
                if ((p->check_card_hand(18)) && (player->get_monster_name() == p->get_monster_name()) && (unit_count > 0)) {
                    player->damage(unit_count-1);
                    std::cout << "BAM POW KABOOM! " << player->get_monster_name() << " takes " << (unit_count-1) << " damage!\n";
                }
                else {
                    player->damage(unit_count);
                    std::cout << "BAM POW KABOOM! " << player->get_monster_name() << " takes " << unit_count << " damage!\n";
                }
                player->Notify();
            }
        }
    }
}






