//
//  map_finder.cpp
//  KingOfNewYork_A3
//
//  Created by Jeremy Gaudet on 2018-10-28.
//  Copyright © 2018 JeremyGaudet. All rights reserved.
//


#include "map_finder.h"

void dirwalk(const char *path, std::vector<std::string> &list) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path)) != nullptr) {
        while ((ent = readdir (dir)) != nullptr) {
            // skip files & directories that begin with periods
            if ((strcmp(ent->d_name, ".")) == 0 || (strcmp(ent->d_name, "..") == 0))
                continue;
            // print to console files that end in .map
            if (strncmp(ent->d_name + strlen(ent->d_name) - 4, ".map", 4) == 0){
                list.push_back(ent->d_name);
//                printf ("%s\n", ent->d_name); // this prints the .map file_names to the console
            }
        }
        closedir (dir);
    } else
        perror ("Could not open directory.");
}





/*
 Version that would search thru directories:
 */

//    DIR *dir;
//    struct dirent *ent;
//    if (!(dir = opendir(path))) {   // if NULL, return to main
//        closedir(dir);
//        return;
//    }
//
//    while ((ent = readdir(dir)) != nullptr) {
//        if (ent->d_type == DT_DIR) {
//            if ( (strcmp(ent->d_name, ".")) == 0 || (strcmp(ent->d_name, "..") == 0) )
//                continue;
//            char *subdir = const_cast<char *>("");
//            strcpy(subdir, path);
//            strcat(subdir, "/");
//            strcat(subdir, ent->d_name);
//            dirwalk(subdir);
//        }
//        else {
//            if (strncmp(ent->d_name + strlen(ent->d_name) - 4, ".map", 4) == 0) {
//                char *subdir2 = const_cast<char *>("");
//                strcpy(subdir2, path);
//                strcat(subdir2, "/");
//                strcat(subdir2, ent->d_name);
//                printf("%s\n", ent->d_name);
//            }
//        }
//    }
//    closedir(dir);
