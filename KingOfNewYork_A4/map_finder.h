//
//  map_finder.h
//  KingOfNewYork_A3
//
//  Created by Jeremy Gaudet on 2018-10-28.
//  Copyright © 2018 JeremyGaudet. All rights reserved.
//

#ifndef map_finder_h
#define map_finder_h

#include <dirent.h>
#include <string>
#include <vector>

void dirwalk(const char* path, std::vector<std::string> &list);

#endif /* map_finder_h */
