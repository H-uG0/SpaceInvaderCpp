#ifndef AUTRE_H
#define AUTRE_H

#include <iostream>
#include <thread>
#include <vector>

#include "mingl/mingl.h"

#include "vecteur.h"

using namespace std;


class autre
{
public:

    void initt (MinGL & window);

    void parcour (vector <pos> & A, MinGL & window);

    vector <pos> joueur (vector <pos> & A);
};

#endif // AUTRE_H
