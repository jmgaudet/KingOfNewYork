//
//  engine.h
//  KingOfNewYork_A3
//
//  Created by Jeremy Gaudet on 2018-11-15.
//  ID: #40045224
//  COMP_345_Section_N
//

#ifndef engine_h
#define engine_h

#include <random>   // this is needed to shuffle the tiles and power_cards
#include <iostream>
#include <fstream>
#include "map_finder.h"
#include "map.h"
#include "map_loader.h"
//#include "power_cards.h"    // "player.h" already includes power_cards.h
#include "input.h"
#include "resolve.h"    // "resolve.h" already includes "player.h" and "power_cards.h"
#include "tokens.h"
#include "aggressive_strategy.h"
#include "moderate_strategy.h"
#include "human_strategy.h"
#include "subject.h"
#include "card_exec.h"
#include "dice_view.h"


class Engine : public Subject {
private:
    void choose_map();
    void create_players();
    void single_player_mode();
    void tournament_mode();
    void set_starting_positions();
    void setup_tiles(const Graph& g);
    void setup_playerObservers();
    void setup_cardExecution();
    void setup_diceObservers();

    
public:
    Engine();
    ~Engine();
//    void start_game();
    Graph my_board;
    std::vector<Player*> vPlayers;
    int first;
    void setup_powerCards(std::vector<Card>& mydeck);

    std::vector<Card> my_deck;
    
    std::stack<Card> my_stack_pc;
    std::vector<Card> available_pc;    // have a vector of Cards that shows the three available power_cards from the stack
    std::stack<Web_T> web_tokens;
    std::stack<Jinx_T> jinx_tokens;
    std::stack<Souvenir_T> souvenir_tokens;
    std::stack<Carapace_T> carapace_tokens;
};

#endif /* engine_h */
