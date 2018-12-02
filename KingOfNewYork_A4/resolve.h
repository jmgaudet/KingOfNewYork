//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//

#ifndef resolve_h
#define resolve_h

#include <string>
#include <map>
#include <iostream>
#include "player.h"


void resolve_dice(Player* p, std::vector<Player *> pls);

void build_dice_map(std::map<std::string, int> &mapping, Player *p);
void show_map(const std::map<std::string, int> &mapping);
void resolve_generator(const std::map<std::string, int>::iterator &itr, Player *p, std::vector<Player* > pls);
void d_energy(int x, Player *p);
void d_attack(int x, Player *p, std::vector<Player *> pls);
void d_destruction(int x, Player *p, std::vector<Player *> pls);
bool can_destroy(block& b, int x);
void get_reward(Player* p, std::string type, int dur);
void remove_unit_tile(block& b, size_t pos);
void d_heal(int x, Player *p);
void d_celeb(int x, Player *p, std::vector<Player *> pls);
void d_ouch(int x, Player *p, std::vector<Player *> pls);


#endif /* resolve_h */
