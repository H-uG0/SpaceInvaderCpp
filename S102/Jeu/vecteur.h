#ifndef VECTEUR_H
#define VECTEUR_H

#include <iostream>
#include <vector>

#include "mingl/mingl.h"
#include "mingl/gui/sprite.h"

using namespace std;


struct pos {
        size_t x;
        size_t y;
        int direction;
};

const unsigned kEnnemiX = 34;
const unsigned KEnnemiY = 32;
const unsigned kJoueurX = 56;
const unsigned kJoueurY = 60;
const unsigned kTirX = 4;
const unsigned kTirY = 8;

class Vecteur
{
public:
    void initVecteurObjet (vector <pos> & Enemy, pos & Joueur);

    void parcour (vector <pos> & Tirs, nsGui::Sprite TirsJoueur, vector <pos> & Enemy, nsGui::Sprite Adversaire, pos Joueur, nsGui::Sprite Player, MinGL & window);

    void BougerEnnemis (vector <pos> & Enemy);

    int testSiEnnemiToucheBord (vector <pos> & Enemy);

    void BougerTirs (vector <pos> & Tirs, vector <pos> & Enemy);

    void testSiTirTouche (vector <pos> & Tirs, vector <pos> & Enemy);

    bool colision (const pos & Pos1, const unsigned & kPos1X, const unsigned & kPos1Y, const pos & Pos2, const unsigned & kPos2X, const unsigned & kPos2Y);
};

#endif // VECTEUR_H
