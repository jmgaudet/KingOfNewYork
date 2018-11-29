//
//  player.h
//  KingOfNewYork_A3
//
//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//

#ifndef player_h
#define player_h

#include <string>
#include <stack>
#include "dice_rolling.h"
#include "map.h"
#include "subject.h"
#include "power_cards.h"
#include "player_view.h"
#include "strategy.h"
#include "input.h"

class Strategy;
class PlayerView;

enum Zone { OUTSIDE, LOWER, MIDDLE, UPPER };
enum Phase { START, DICE, RESOLVE, MOVE, BUY_CARDS, END_TURN };



class Player : public Subject {
private:
    int life_points = 10;
    int victory_points = 0;
    int energy_cubes = 2000;
    Zone player_zone = OUTSIDE; // a Player always begins the game OUTSIDE of Manhattan
    Phase player_phase = START;
    std::vector<Card> hand;     // this is for the player's cards that they bought
    std::string m_location = "";
    std::string m_monster_name = "";
    std::vector<PlayerView *> observers;
    Strategy* m_strategy = nullptr;


public:
    Player();
    explicit Player(Graph board);
    Player(Graph board, Strategy* strat);
    virtual ~Player();
    Dice m_dice;
    Graph m_graph;  // need this to be public, because the player, inside of resolve.cpp, needs to see what buildings he can destroy
    bool attacked = false;
    bool m_in_manhattan = false;
    bool validate_location(const std::string& current, const std::string& selec);
    bool has_won(const Player& p);
    std::vector<Card> get_hand();
    int get_lifepoints();
    int get_energy();
    int get_victorypoints();
    Zone get_zone();
    void set_zone(Zone manhattan_zone);
    Phase get_gamePhase();
    void set_phase(Phase game_phase);
    std::string get_monster_name();
    void add_victoryPoints(int x);
    void healer(int x);
    void damage(int x);
    void set_location(const std::string& place);
    std::string get_location();
    void manhattan_points();
    void add_to_hand(Card c);
    void remove_from_hand(Card c);
    bool check_card_hand(Card c);
    bool check_card_hand(int id);   // I can check with both a CARD and a simple int matching a card's ID
    void add_energy(int x);
    void set_monster_name(const std::string& name);
    void display_branches(const std::string& current);

    // STRATEGY METHODS:
    void execute_dice_rolling(Player* p);
    void execute_starting_position(Player* p);
    void execute_resolve_dice(Player* p, std::vector<Player*> pls);
    void execute_move(Player* p);
    void execute_choice_to_move(Player* p);
    void execute_buy_cards(Player* p, std::vector<Card>& v, std::stack<Card>& s);
    std::string get_strategy_name();
    void set_strategy(Strategy* strat);

};

static std::vector<std::string> names = {"Captain Fish", "Sherrif", "Kong", "Mantis", "Draconis", "Rob"};
int starting_player(std::vector<Player *> &v);
void choose_monster_figure(std::vector<Player *> &v);



#endif /* player_h */
