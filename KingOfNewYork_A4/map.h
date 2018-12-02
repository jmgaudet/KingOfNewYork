//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//

#ifndef map_h
#define map_h

#include <map>
#include <vector>
#include <list>
#include <stack>
#include "tiles.h"

class Player;


struct Borough { // ie. Vertex = Borough
    std::vector<Borough> adj;    // creating the vector of adjacent boroughs
    std::string borough;
    mutable int num_players = 0;
    std::list<Player*> players_list;    
    std::stack<std::pair<Tiles, Tiles>> hidden_buildings;
    std::vector<std::pair<Tiles, Tiles>> revealed_tiles;
    void print_avail_tiles();
    Borough(std::string n) : borough(n) {}
    Borough();
    ~Borough();
};

class Graph {
public:
    Graph();
    ~Graph();
    typedef std::map<std::string, Borough *> vmap;
    vmap walk;
    void add_vertex(const std::string& borough);       // add a vertex to the map
    void add_edge(const std::string& from, const std::string& to);      // look up vertex in map and add to the vertex adjacency list
    void printMap(const Graph& g);
};

void build_graph(Graph& g, const std::vector<std::string>& v);


#endif /* map_h */
