//
//  main.cpp
//  KingOfNewYork_A3
//  DRIVER
//
//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//



#include "engine.h"
#include "statistics_view.h"    // "engine.h" cannot have this file, or circular-relationship happens!

// This is needed to delete a Player from the vector:
template <typename Player>
void remove_player(Player& p, size_t pos) {
    auto itr = p.begin();
    std::advance(itr, pos);
    p.erase(itr);
}

void testing(Engine* e) {
    Player* bob = new Player(e->my_board, new Human);
    bob->set_monster_name("bob_monster");
    
    Player* meg = new Player(e->my_board, new Human);
    meg->set_monster_name("meg_monster");
    
    PlayerView* plb = new PlayerView(bob);
    bob->Attach(plb);
    PlayerView* plm = new PlayerView(meg);
    meg->Attach(plm);
    
    bob->Attach(plm);
    meg->Attach(plb);
    
    bob->set_location("Bronx");
    meg->set_location("Queens");
    
    bob->execute_move(bob);
    
}




int main() {
    Engine* e = new Engine();
//    testing(e);
    StatisticsView *overhead __attribute__((unused)) = new StatisticsView(e);
    bool end = false;
    size_t x = 0;
    while (!end) {
        
        for (size_t i = 0; i < e->vPlayers.size(); i++) {
            x = (i + e->first) % e->vPlayers.size();
            
            e->Notify();    // display game-world statistics
            
            std::cout << "\n////////////////////////////////////////////////////////////////////////////////////////////////" << std::endl;
            std::cout << "////////////////////////////////////////////////////////////////////////////////////////////////" << std::endl;
            std::cout << "\t\t\t\t\t\t\t\t\t\t" << e->vPlayers[x]->get_monster_name() << "'s turn!" << std::endl;
            std::cout << "////////////////////////////////////////////////////////////////////////////////////////////////" << std::endl;
            std::cout << "////////////////////////////////////////////////////////////////////////////////////////////////" << std::endl;
            
            e->vPlayers[x]->manhattan_points();    // grant the player currently in Manhattan the earned points
            
            // ROLL_THE_DICE //
            
            e->vPlayers[x]->set_phase(DICE);
            e->vPlayers[x]->Notify();
            e->vPlayers[x]->execute_dice_rolling(e->vPlayers[x]);
            
            // RESOLVE_DICE //
            
            e->vPlayers[x]->set_phase(RESOLVE);
            e->vPlayers[x]->execute_resolve_dice(e->vPlayers[x], e->vPlayers);
            e->vPlayers[x]->Notify();
            
            // MOVE //
            
            e->vPlayers[x]->set_phase(MOVE);
            e->vPlayers[x]->execute_move(e->vPlayers[x]);
            
            // BUY_CARDS //
            
            e->vPlayers[x]->set_phase(BUY_CARDS);
            e->vPlayers[x]->execute_buy_cards(e->vPlayers[x], e->available_pc, e->my_stack_pc);
            
            if (e->vPlayers[x]->get_victorypoints() >= 20)
                goto finish;
            
            // END_OF_TURN //
            
            e->vPlayers[x]->set_phase(END_TURN);
            e->vPlayers[x]->Notify();
            
            if (e->vPlayers[x]->get_lifepoints() <= 0) {
                e->my_board.walk.at(e->vPlayers[x]->get_location())->num_players--;
                e->my_board.walk.at(e->vPlayers[x]->get_location())->players_list.remove(e->vPlayers[x]);
                remove_player(e->vPlayers, x);
            }
            if (e->vPlayers.size() == 1)
                goto finish;
            
        }
    }
finish:
    std::cout << e->vPlayers[x]->get_monster_name() << " has won the game!\n";
    delete overhead;
}

