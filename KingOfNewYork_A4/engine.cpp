//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//

#include "engine.h"
#include "nlohmann/json.hpp"    // I'm using this to import the 66 power cards from a .json file



Engine::Engine() {
    std::cout << "[Starting the game...]\n";
    std::cout << "Welcome to King Of New York!\n";
    std::cout << "Made by Jeremy Gaudet\n\n";
    
    // needed for the randomness of the rolling of the dice:
    std::srand(unsigned(std::time(nullptr)));
    
    // selecting the map on which you will play the game:
    choose_map();
    
    // create a vector of Players (Human and CPUs):
    create_players();
    
    // choose which monster card will represent you during the game:
    choose_monster_figure(vPlayers);
    
    // return an int representing which player in the vector will go first:
    this->first = starting_player(vPlayers);

    // going in order, each player will choose their starting positions:
    set_starting_positions();
    
    // setting up the miscellaneous remaining pieces:
    setup_tiles(my_board);
    setup_powerCards(my_deck);
    init_tokens(web_tokens, jinx_tokens, souvenir_tokens, carapace_tokens);
    setup_playerObservers();
    setup_diceObservers();
}

Engine::~Engine() {}

void Engine::choose_map() {
    //  Preparing the Game Board, and setting Player turn order
    const char* path= "/Users/jeremygaudet/Documents/Xcode/KingOfNewYork_A4/maps";
    std::vector<std::string> map_files;
//    dirwalk_powerful(path, map_files);
    dirwalk(path, map_files);   // "path" remains const; "map_files" is given a list of possible .map files from the original directory "path".
    std::vector<std::string> *v = import_map(path, map_files);
    
    // create a Graph object and push each item from the previously created vector into the graph data structure:
    build_graph(this->my_board, *v);
    delete v; // once the Graph object is created, "v" is no longer needed
    v = nullptr;
}

// creating the vector of players:
void Engine::create_players() {
    std::string mode_choice;
    do {
        std::cout << "Select which GAME_MODE you want to play:\n"
        << "[1] -- Single player mode (1 human, 1-5 AI players)\n[2] -- Tournament mode (2-6 AI players)" << std::endl;
        mode_choice = capture_input();
    } while (!isValid_num(mode_choice, 1, 2));
    if (get_digit(mode_choice) == 1)
        single_player_mode();
    else
        tournament_mode();
}

void Engine::single_player_mode() {
    int player_num = 0;
    bool ready = false;
    while (!ready) {
        std::cout << "\nHow many people wish to play?\nENTER a TOTAL number of players [2-6]: ";
        std::string ans = capture_input();
        if (isValid_num(ans, 2, 6)) {
            ready = true;
            player_num = get_digit(ans);
        }
    }
    for (int i = 0; i < player_num; i++) {
        if (i == 0)
            vPlayers.push_back(new Player(my_board, new Human));   // this will be the human player
        else {
            int random = rand() % 2;
            if (random == 0)
                vPlayers.push_back(new Player(my_board, new Moderate));
            else
                vPlayers.push_back(new Player(my_board, new Aggressive));
        }
    }
}

void Engine::tournament_mode() {
    int player_num = 0;
    bool ready = false;
    while (!ready) {
        std::cout << "\nHow many AI players are going to battle it out?\nENTER a TOTAL number of players [2-6]: ";
        std::string ans = capture_input();
        if (isValid_num(ans, 2, 6)) {
            ready = true;
            player_num = get_digit(ans);
        }
    }
    for (int i = 0; i < player_num; i++) {
        int random = rand() % 2;
        if (random == 0)
            vPlayers.push_back(new Player(my_board, new Moderate));
        else
            vPlayers.push_back(new Player(my_board, new Aggressive));
    }
}

// going in order, each Player chooses 1 of 4 possible starting positions:
void Engine::set_starting_positions() {
    for (size_t i = 0; i < vPlayers.size(); i++) {
        size_t x = (i + first) % vPlayers.size();
        vPlayers[x]->execute_starting_position(vPlayers[x]);
        std::cout << vPlayers[x]->get_monster_name() << " is now in borough: " << vPlayers[x]->get_location() << "\n\n";
    }
}

// function that constructs and places the tiles on each borough in the city:
void Engine::setup_tiles(const Graph& g) {
    buildings bb;
    units uu;
    block block1;
    initiate_buildings(bb);
    initiate_units(uu);
    initiate_pairs(bb,uu,block1);
    std::shuffle(block1.begin(), block1.end(), std::mt19937(std::random_device()()));
    for (auto &itr : g.walk) {
        for (int i = 0; i < 6; i++)
            itr.second->hidden_buildings.emplace(block1[i]);
        for (int j = 0; j < 3; j++)
            itr.second->revealed_tiles.push_back(block1[j]);
    }
}

void Engine::setup_powerCards(std::vector<Card>& d) {
    initiate_cards(d);
    shuffle_cards(d);   // suffle_cards() MUST come *before* the Observer creation. Or else the observers get mis-matched!
    for (auto& card : d) {
        CardExecution* cdex = new CardExecution(&card);
        card.Attach(cdex);
    }
    for (const auto& card : d) {
        if (card.ID == 1 || card.ID == 0) {
            vPlayers[0]->inactive_cards.emplace_back(card);
            continue;
        }
        my_stack_pc.push(card);
    }
    while (available_pc.size() < 3) {
        available_pc.push_back(my_stack_pc.top());
        my_stack_pc.pop();
    }
}


void Engine::setup_playerObservers() {
    std::cout << "[Initiating Player Observer.]" << std::endl;
    for (auto &player : vPlayers) {
        PlayerView* plv = new PlayerView(player);
        player->Attach(plv);
    }
}

void Engine::setup_diceObservers() {
    std::cout << "[Initiating Dice Observer.]" << std::endl;
//    for (auto& dice : )
    for (auto &player : vPlayers) {
        DiceView* dv = new DiceView(&player->m_dice);
        player->m_dice.Attach(dv);
    }

}

