//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//

#include <iostream>
#include <vector>
#include <sstream>
#include "map.h"


Graph::Graph() {}
Graph::~Graph() {}

void Graph::add_vertex(const std::string& borough) {
    vmap::iterator itr = walk.find(borough);
    if (itr == walk.end()) {
        Borough *v;
        v = new Borough(borough);
        walk[borough] = v;
        return;
    }
    std::cout << "\nVertex already exists!\n";
}

void Graph::add_edge(const std::string& from, const std::string& to) {
    Borough* f = (walk.find(from)->second);
    f->adj.push_back(to);
}

void build_graph(Graph& g, const std::vector<std::string>& v) {
    for (int i = 0; i < v.size(); i++) {
        std::vector<std::string> sub_v;
        std::stringstream ss(v[i]);
        while (ss.good()) {
            std::string sub_str;
            std::getline(ss, sub_str, ',');
            sub_v.push_back(sub_str);
        }
        g.add_vertex(sub_v[0]);
        for (int j = 1; j < sub_v.size(); j++) {
            g.add_edge(sub_v[0], sub_v[j]);
        }
    }
}



Borough::Borough() {}
Borough::~Borough() {}

void Borough::print_avail_tiles() {
    int i = 1;
    for(auto const& t: revealed_tiles) {
        if (t.first.alive == true) {
            std::cout << "\n[" << i << "].\n";
            std::cout << "Type: " << t.first.type << "\n";
            std::cout << "Durability: " << t.first.durability << "\n";
            std::cout << "-----------------\n\n";
        }
        else {
            std::cout << "\n[" << i << "].\n";
            std::cout << "Type: " << t.second.type << "\n";
            std::cout << "Durability: " << t.second.durability << "\n";
            std::cout << "-----------------\n\n";
        }
        i++;
    }
}


void Graph::printMap(const Graph& g) {
    auto itr = g.walk.begin();
    for( ; itr != g.walk.end(); itr++) {
        std::cout << itr->first << ": ";
        auto li = itr->second->adj.begin();
        for( ; li != itr->second->adj.end(); li++)
            std::cout << li->borough << ", ";
        std::cout << std::endl;
    }
}

