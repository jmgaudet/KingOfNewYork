//
//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//

#include "tiles.h"

Tiles::Tiles() = default;
Tiles::~Tiles() = default;

void initiate_buildings(buildings& fresh_stack) {
    for (int i = 0; i < 22; i++) {
        fresh_stack[i].type = "Office";
        fresh_stack[i].durability = 1;
    }
    for (int i = 22; i < 25; i++) {
        fresh_stack[i].type = "Power plant";
        fresh_stack[i].durability = 2;
    }
    for (int i = 25; i < 28; i++) {
        fresh_stack[i].type = "Hospital";
        fresh_stack[i].durability = 2;
    }
    for (int i = 28; i < 36; i++) {
        fresh_stack[i].type = "Office";
        fresh_stack[i].durability = 2;
    }
    for (int i = 36; i < 39; i++) {
        fresh_stack[i].type = "Power plant";
        fresh_stack[i].durability = 3;
    }
    for (int i = 39; i < 42; i++) {
        fresh_stack[i].type = "Hospital";
        fresh_stack[i].durability = 3;
    }
    for (int i = 42; i < 45; i++) {
        fresh_stack[i].type = "Office";
        fresh_stack[i].durability = 3;
    }
}


void initiate_units(units& fresh_stack) {
    for (int i = 0; i < 22; i++) {
        fresh_stack[i].type = "Infantry";
        fresh_stack[i].durability = 2;
    }
    for (int i = 22; i < 36; i++) {
        fresh_stack[i].type = "Jet";
        fresh_stack[i].durability = 3;
    }
    for (int i = 36; i < 45; i++) {
        fresh_stack[i].type = "Tank";
        fresh_stack[i].durability = 4;
    }
}

void initiate_pairs(buildings& b, units& u, block& block) {
    block.reserve(NTILES);
    for (int i = 0; i < NTILES; i++) {
        block.emplace_back(std::make_pair(b[i], u[i]));
    }
}

void Tiles::print_tile() const {
    std::cout << "-----------------\n";
    std::cout << "Type: " << type << "\n";
    std::cout << "Durability: " << durability << "\n";
    std::cout << "-----------------\n\n";
}
