//
//  player.cpp
//  KingOfNewYork_A3
//
//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//


#include <iostream>
#include "player.h"

Player::Player() {}
Player::~Player() {
    std::cout << "\n\n\nI HAVE DELETED A PLAYER\n\n\n";
}

// Human Player constructor:
Player::Player(Graph board) { m_graph = board; m_strategy = nullptr; }

// AI Player construction:
Player::Player(Graph board, Strategy* strat) {
    m_graph = board;
    m_strategy = strat;
}

void Player::add_energy(int x) { energy_cubes += x; }

void Player::healer(int x) {
    while (life_points < 10 && x > 0) {
        life_points++;
        x--;
    }
}

void Player::damage(int x) { life_points -= x; }

int Player::get_lifepoints() { return life_points; }

std::vector<Card> Player::get_hand() { return hand; }

void Player::add_to_hand(Card c) {
    this->hand.push_back(c);
    c.Notify(this);
}

void Player::add_victoryPoints(int x) { victory_points += x; }


void Player::execute_starting_position(Player* p) {
    return this->m_strategy->starting_position(p);
}

void Player::execute_resolve_dice(Player* p, std::vector<Player *> pls) {
    return this->m_strategy->resolve_dice(p, pls);
}

void Player::execute_move(Player* p) {
    return this->m_strategy->move(p);
}

void Player::execute_choice_to_move(Player* p) {
    return this->m_strategy->choose_to_move(p);
}

void Player::execute_buy_cards(Player* p, std::vector<Card>& v, std::stack<Card>& s) {
    return this->m_strategy->buy_cards(p, v, s);
}



int starting_player(std::vector<Player *> &v) {
    int top = 0;    // Index of player who rolls the highest num of ATTACKS. This is the value that is returned.
    int temp = 0;
    int max = 0;
    int copy = 0;
    std::vector<int> max_tracker(v.size(), 0);
    bool done = false;
    while (!done) {
        for (int i = 0; i < v.size(); i++) {
            if (max_tracker[i] == max) {
                v[i]->m_dice.set_specialRoll(true);
                v[i]->m_dice.roll_dice();
                std::cout << "\nPlayer #" << (i+1) << " rolled: ";
                v[i]->m_dice.display_dice();
                std::vector<int> *c = v[i]->m_dice.get_collection();
                int amount = v[i]->m_dice.count_attack(c);
                std::cout << "(Player #" << (i+1) << " rolled " << amount << " ATTACK dice)\n\n";
                max_tracker[i] = amount;
                if (amount > temp) {
                    temp = amount;
                    top = i;    // this is needed to identify which player got the most ATTACKS
                    copy = 0;
                }
                if (amount == temp)
                    copy++;
            }
            else
                max_tracker[i] = -1;  // If a player's roll didn't match the top amount of ATTACKS, they are "eliminated".
            v[i]->m_dice.set_specialRoll(false);
        }// end of for-loop
        max = max_tracker[top];
        temp = 0;
        if (copy <= 1)
            done = true;
    }
    std::cout << "\nPlayer with the highest # of Attacks: " << v[top]->get_monster_name() << "." << std::endl;
    std::cout << v[top]->get_monster_name() << " will therefore go first." << std::endl;
    return top;
}

template <typename Player>
void remove_from_vector(Player& vp, size_t pos) {
    auto itr = vp.begin();
    std::advance(itr, pos);
    vp.erase(itr);
}
int choose_monster(int max) {
    bool done = false;
    int c = 0;
    while (!done) {
        std::cout << "\nSection [enter a #]: ";
        std::string ans = capture_input();
        if (isValid_num(ans, 1, static_cast<int>(names.size()))) {
            c = get_digit(ans);
            done = true;
        }
    }
    return c;
}

void choose_monster_figure(std::vector<Player *> &v) {
    for (int i = 0; i < v.size(); i++) {
        std::cout << "\nPlayer #" << (i+1) << ", choose your monster card:\n";
        // display all the Monster_Names currently available:
        for (int j = 0; j < names.size(); j++)
            std::cout << (j+1) << ". " << names[j] << "\n";
        int choice = 0;
        if (v[i]->get_strategy_name() == "Human")    // if the Player is a human
            choice = choose_monster(static_cast<int>(names.size()));
        else
            choice = (rand() % static_cast<int>(names.size())) + 1;
        std::cout << "Player #" << (i+1) << ", you have chosen: " << names[choice-1] << "\n";
        v[i]->set_monster_name(names[choice-1]);
        remove_from_vector(names, choice-1);
    }
}

void Player::display_branches(const std::string& current) {
    auto itr = m_graph.walk.find(current);
    if(itr == m_graph.walk.end())
        std::cout << "Key-value pair not present in map\n" ;
    else {
        std::cout << "Boroughs you can jump to: " << std::endl;
        auto li = itr->second->adj.begin();
        for( ;li != itr->second->adj.end(); li++)
            std::cout << "~ " << li->borough << " ~";
        std::cout << std::endl;
    }
}

bool Player::validate_location(const std::string& current, const std::string& selec) {
    auto itr = m_graph.walk.find(current);
    auto li = itr->second->adj.begin();
    for( ;li != itr->second->adj.end(); ++li) {
        if (li->borough == selec) {
            // there are different rules for the number of Players in Manhattan:
            if (selec == "Manhattan") {
                auto itr3 = m_graph.walk.find(selec);
                if (itr3->second->num_players < 1)
                    return true;
                else {
                    std::cout << "There are too many Players in " << selec << " already.\n";
                    return false;
                }
            }
            else {
                auto itr3 = m_graph.walk.find(selec);
                if (itr3->second->num_players < 2)
                    return true;
                else {
                    std::cout << "There are too many Players in " << selec << " already.\n";
                    return false;
                }
            }
        }
    }
    std::cout << "You have entered an invalid selection." << std::endl;
    return false;
}

void Player::set_strategy(Strategy* strat) {
    this->m_strategy = strat;
}

void Player::execute_dice_rolling(Player* p) {
    this->m_strategy->dice_throw(p);
}


std::string Player::get_strategy_name() {
    return this->m_strategy->see_strategy_name();
}

void Player::set_monster_name(const std::string& name) { m_monster_name = name; }

std::string Player::get_location() { return m_location; }

void Player::set_location(const std::string& place) { m_location = place; }

int Player::get_energy() { return energy_cubes; }

Zone Player::get_zone() {
    return player_zone;
}

void Player::set_zone(Zone manhattan_zone) {
    this->player_zone = manhattan_zone;
}

void Player::set_phase(Phase game_phase) {
    this->player_phase = game_phase;
}

Phase Player::get_gamePhase() {
    return player_phase;
}

int Player::get_victorypoints() { return victory_points; }

bool Player::has_won(const Player& p) { return (p.victory_points >= 20); }

std::string Player::get_monster_name() { return m_monster_name; }

void Player::manhattan_points() {
    if (player_zone == LOWER) {
        add_energy(1);
        add_victoryPoints(1);
    }
    if (player_zone == MIDDLE) {
        add_energy(1);
        add_victoryPoints(2);
    }
    if (player_zone == UPPER) {
        add_energy(2);
        add_victoryPoints(2);
    }
}



