#include "autre.h"
#include "mingl/mingl.h"
#include "mingl/gui/sprite.h"

#include <iostream>
#include <vector>

using namespace std;


vector<pos> autre::joueur (vector <pos> & A){
    for (size_t i = 0; i < 15; ++i){
        A[i].x = i * 34 + 20;
        A[i].y = 32 + 20;
    }
    return A;
}

void autre::parcour (vector <pos> & A, MinGL & window){
    for (size_t i = 0; i < A.size(); ++i){
        nsGui::Sprite img("/amuhome/c21201897/Documents/S102/enemy.si2", nsGraphics::Vec2D(A[i].x, A[i].y));
        window << img;
    }
}

void autre::initt (MinGL & window){
    pos jour;
    vector <pos> A (14, jour);
    A = joueur (A);
    parcour (A, window);
}

