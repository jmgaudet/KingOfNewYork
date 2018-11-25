//
//  map_loader.cpp
//  KingOfNewYork_A3
//
//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//


#include <iostream>
#include <fstream>
#include <cstdlib>  // this is for the "exit()" function call
#include <sstream>  // for "stringstream"
#include <vector>
#include "map_loader.h"
#include "map.h"

// takes a string for the .map file location, and an incoming file stream:
void open_map(const std::string& path, std::ifstream& stream) {
    stream.open(path);
    if (stream.fail()) {
        std::cout << "Input file opening failed.\n";
        std::exit(1);
    }
    else
        std::cout << "The .map file was opened successfully.\n" << std::endl;
}


bool has_any_digits(const std::string& s) {
    return std::any_of(s.begin(), s.end(), ::isdigit);
}

std::vector<std::string> make_vector(std::ifstream& stream) {
    std::vector<std::string> v;
    std::string line;
    while (std::getline(stream, line)) {
        if (has_any_digits(line)) {
            std::cout << "Error: This map is not a valid game-board, and cannot be used.\nPlease select another file:\n" << std::endl;
            v.clear();
            return v;
        }
        if (!line.empty())
            v.push_back(line);
    }
    return v;
}

std::vector<std::string>* import_map(const char* path, std::vector<std::string> map_files) {
    std::vector<std::string> *v = new std::vector<std::string>();
    while (v->size() == 0) {
        
        std::string s_path(path);   // this is needed for appending the selected file further in the function
        std::string complete_path = "";
        std::ifstream in_stream;
        
        std::cout << "Which .map file would you like to implement?\nSelect a number from the following list:" << std::endl;
        for (int i = 0; i < map_files.size(); i++) {
            std::cout << (i+1) << ": " << map_files[i] << std::endl;
        }
        std::cout << "\nSelection: ";
        
        int map_choice;
        std::cin >> map_choice;
        std::cin.ignore();
        
        std::cout << "\nAttemting to load \"" << map_files[map_choice-1] << "\"..." << std::endl;
        complete_path = s_path + "/" + map_files[map_choice-1];
        open_map(complete_path, in_stream);
        
        // create a vector to store each line of the .map file in its own index:
        *v = make_vector(in_stream);
        if (v->size() != 0)
            in_stream.close();
    }
    return v;
}

std::vector<std::string>* quick_load(std::string map_file) {
    std::vector<std::string> *v = new std::vector<std::string>();
    std::ifstream in_stream;
    std::cout << "\nAttemting to load \"" << map_file << "\"..." << std::endl;
    open_map(map_file, in_stream);
    // create a vector to store each line of the .map file in its own index:
    *v = make_vector(in_stream);
    if (v->size() != 0)
    in_stream.close();
    return v;
}



