//
//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//

#ifndef tiles_h
#define tiles_h

#include <stdio.h>
#include <vector>
#include <iostream>
#include <array>
#include <string>
#include <map>
#include <utility>


constexpr std::size_t NTILES = 45;

struct Tiles {

    std::string type;
    int durability;
    bool alive = true;
    bool tag = false;
    void print_tile() const ;
    Tiles();
    ~Tiles();
    
};

using buildings = Tiles[NTILES];
using units = Tiles[NTILES];
using block = std::vector<std::pair<Tiles, Tiles>>;
void initiate_buildings(buildings& fresh_stack);
void initiate_units(buildings& fresh_stack);
void initiate_pairs(buildings& b, units& u, block& block);

#endif /* tiles_h */

