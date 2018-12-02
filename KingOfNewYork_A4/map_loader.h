//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//

#ifndef map_loader_h
#define map_loader_h

#include <vector>

// takes a string for the .map file location, and an incoming file stream:
void open_map(const std::string& path, std::ifstream& stream);
std::vector<std::string> make_vector(std::ifstream& stream);
bool has_any_digits(const std::string& s);
std::vector<std::string>* import_map(const char* path, std::vector<std::string> map_files);
std::vector<std::string>* quick_load(std::string map_file);

#endif /* map_loader_h */
