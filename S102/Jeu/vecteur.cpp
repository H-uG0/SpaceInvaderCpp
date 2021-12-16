#include "vecteur.h"


vector <pos> & Vecteur::Delete (vector <pos> & VPos, const unsigned & PosBeg)
{
    for (unsigned i (PosBeg); i < VPos.size() - 1; ++i )
        VPos [i] = VPos [i + 1];
    VPos.resize(VPos.size() - 1);
    return VPos;
}

void Vecteur::initVecteurObjet (vector <pos> & Enemy, pos & Joueur){
    Enemy.resize(32);
    for (size_t i = 0; i < Enemy.size(); ++i){
        Enemy[i].x = 80;
        Enemy[i].y = 60;
        Enemy[i].direction = -1;
    }
    unsigned cpt = 0;
    unsigned X = 0;
    unsigned Y = 0;
    for (size_t i = 0; i < Enemy.size() / 8; ++i){
        for (size_t i = 0; i < Enemy.size() / 4; ++i){
            Enemy[cpt].x += X;
            Enemy[cpt].y += Y;
            X += 180;
            cpt += 1;
        }
        X = 0;
        Y += 100;
    }
    Joueur.x = 700;
    Joueur.y = 900;
}

void Vecteur::BougerEnnemis(vector<pos> & Enemy){
    //On vérifie où se situent les extrémités pour le bloc d'ennemie
    int direction = testSiEnnemiToucheBord(Enemy);

    //Si une extrémité des ennemis touche le bord, la direction est inversé et le bloc d'ennemie descend
    if (direction != 0){
        for (size_t i = 0; i < Enemy.size(); ++i){
            Enemy[i].direction = direction;
            Enemy[i].y += 10;
        }
    }

    //On fait bouger tous les ennemis selon leur direction
    for (size_t i = 0; i < Enemy.size(); ++i)
        Enemy[i].x += 2 * Enemy[i].direction;
}

void Vecteur::BougerTirs (vector <pos> & Tirs, vector <pos> & Enemy){
    testSiTirTouche(Tirs, Enemy);
    for (size_t i = 0; i < Tirs.size(); ++i){
        Tirs[i].y -= 2;
    }
}

void Vecteur::testSiTirTouche (vector <pos> & Tirs, vector <pos> & Enemy){
    for (size_t i = 0; i < Tirs.size(); ++i){
        if (Tirs[i].y <= 2)
            Delete(Tirs, i);
        else {
            for (size_t j = 0; j < Enemy.size(); ++j){
                if (!colision(Tirs[i], kTirX, kTirY, Enemy[j], kEnnemiX, KEnnemiY)){
                    Delete(Tirs, i);
                    Delete(Enemy, j);
                }
            }
        }
    }
}

int Vecteur::testSiEnnemiToucheBord (vector <pos> & Enemy){
    //On initialise les indice de celui le plus à droite et de celui le plus à gauche dans le tableau d'ennemie
    unsigned indiceMax = 0;
    unsigned indiceMin = 0;

    //On trouve l'ennemie qui est le plus au bord à droite et à gauche
    for (size_t i = 0; i < Enemy.size(); ++i){
        if (Enemy[indiceMax].x < Enemy[i].x)
            indiceMax = i;
        if (Enemy[indiceMin].x > Enemy[i].x)
            indiceMin = i;
    }

    //On vérifie les deux extrémités touchent les bords
    if (Enemy[indiceMax].x >= 1450)
        return -1;
    if (Enemy[indiceMin].x < 5)
        return 1;
    return 0;
}

void Vecteur::parcour (vector <pos> & Tirs, nsGui::Sprite TirsJoueur, vector <pos> & Enemy, nsGui::Sprite Adversaire, pos Joueur, nsGui::Sprite Player, MinGL & window){
    for (size_t i = 0; i < Enemy.size(); ++i){
        Adversaire.setPosition(nsGraphics::Vec2D(Enemy[i].x, Enemy[i].y));
        window << Adversaire;
    }

    Player.setPosition(nsGraphics::Vec2D(Joueur.x, Joueur.y));
    window << Player;

    for (size_t i = 0; i < Tirs.size(); ++i){
        TirsJoueur.setPosition(nsGraphics::Vec2D(Tirs[i].x, Tirs[i].y));
        window << TirsJoueur;
    }

    BougerEnnemis (Enemy);
    BougerTirs (Tirs, Enemy);
}

bool Vecteur::colision (const pos & Pos1, const unsigned & kPos1X, const unsigned & kPos1Y, const pos & Pos2, const unsigned & kPos2X, const unsigned & kPos2Y){
    if (((Pos1.y <= (Pos2.y + kPos2Y))&& (Pos1.y >= (Pos2.y + kPos2Y))) && ((Pos1.x >= Pos2.x) && ((Pos1.x + kPos1X) <= (Pos2.x + kPos2X))))
        return false;
    /*if (((Pos1.y <= (Pos2.y + kPos2Y)) && (Pos1.y >= (Pos2.y + kPos2Y))) && (((Pos1.x + kPos1X) >= Pos2.x) && (Pos1.x <= Pos2.x)))
        return false;*/
    if (((Pos1.y + kPos1Y) >= Pos2.y) && ((Pos1.y + kPos1Y) <= (Pos2.y + kPos2Y)) && ((Pos1.x + kPos1X) >= Pos2.x) && (Pos1.x <= (Pos2.x + kPos2X)))
        return false;
    return true;
}
