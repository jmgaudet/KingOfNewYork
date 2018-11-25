//
//  tokens.cpp
//  KingOfNewYork_A3
//
//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N
//

#include "tokens.h"

void init_tokens(std::stack<Web_T>& w, std::stack<Jinx_T>& j, std::stack<Souvenir_T>& s, std::stack<Carapace_T>& c) {
    Web_T w_object;
    for (int i = 0; i < NWEB; i++)
        w.push(w_object);
    Jinx_T j_object;
    for (int i = 0; i < NJINX; i++)
        j.push(j_object);
    Souvenir_T s_object;
    for (int i = 0; i < NSOUVENIR; i++)
        s.push(s_object);
    Carapace_T c_object;
    for (int i = 0; i < NCARAPACE; i++)
        c.push(c_object);
}
