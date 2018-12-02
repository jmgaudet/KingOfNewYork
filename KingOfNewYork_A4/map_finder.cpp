//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
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

void dirwalk_powerful(char *path, std::vector<std::string> &list) {
    DIR *dir;
    struct dirent *ent;
    if (!(dir = opendir(path))) {   // if NULL, return to main
        closedir(dir);
        return;
    }
//    char *subdir = const_cast<char *>("");
    char result[1000];

    while ((ent = readdir(dir)) != nullptr) {
        if (ent->d_type == DT_DIR) {
            if ( (strcmp(ent->d_name, ".")) == 0 || (strcmp(ent->d_name, "..") == 0) )
                continue;
//                strcpy(subdir, path);
            strcpy(result, path);
            strcat(result, "/");
            strcat(result, ent->d_name);
            dirwalk_powerful(result, list);
        }
        else {
            if (strncmp(ent->d_name + strlen(ent->d_name) - 4, ".map", 4) == 0) {
//                strcpy(result, path);
//                strcat(result, "/");
//                strcat(result, ent->d_name);
                printf("%s\n", ent->d_name);
                list.push_back(ent->d_name);
            }
        }
    }
    closedir(dir);
}


