//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//

#ifndef map_finder_h
#define map_finder_h

#include <dirent.h>
#include <string>
#include <vector>

void dirwalk(const char* path, std::vector<std::string> &list);
void dirwalk_powerful(char *path, std::vector<std::string> &list);

#endif /* map_finder_h */
