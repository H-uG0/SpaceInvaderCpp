#define FPS_LIMIT 60

#include <iostream>
#include <vector>

#include "mingl/mingl.h"
#include "autre.h"
#include "vecteur.h"


#include "mingl/gui/sprite.h"


using namespace std;


Vecteur Salut;
autre toto;
const unsigned dimensionFenetreX = 1500;
const unsigned dimensionFenetreY = 1000;

bool clavier(MinGL & window, pos & Joueur, vector <pos> & Tirs)
{
    // On vérifie si le joueur ne touche pas les bords de la fenêtre
    if (Joueur.x < 5){
        Joueur.x += 1;
        return false;
    }
    if (Joueur.x > dimensionFenetreX - 61){
        Joueur.x -=1;
        return false;
    }
    // On vérifie si QSD est pressé, et met a jour la position
    if (window.isPressed({'q', false}))
        Joueur.x -= 5;
    else if (window.isPressed({'d', false}))
        Joueur.x += 5;
    else if (window.isPressed({'s', false})){
        Tirs.resize(Tirs.size() + 1);
        Tirs[Tirs.size() - 1].x = Joueur.x + kJoueurX / 2;
        Tirs[Tirs.size() - 1].y = Joueur.y + 4;
    }
    return false;
}

int main()
{
    MinGL window("Fenêtre", nsGraphics::Vec2D(dimensionFenetreX, dimensionFenetreY), nsGraphics::Vec2D(250, 0), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();

    chrono::microseconds frameTime = chrono::microseconds::zero();

    vector <pos> Enemy;
    vector <pos> Tirs;

    pos Joueur;

    nsGui::Sprite Player ("/amuhome/c21201897/Documents/S102/Vaisseau.si2", nsGraphics::Vec2D(0, 0));
    nsGui::Sprite Adversaire ("/amuhome/c21201897/Documents/S102/enemy.si2", nsGraphics::Vec2D(0, 0));
    nsGui::Sprite TirsJoueur ("/amuhome/c21201897/Documents/S102/tirs.si2", nsGraphics::Vec2D(0, 0));

    Salut.initVecteurObjet(Enemy, Joueur);



    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // On dessine les formes géométriques

        if (clavier(window, Joueur, Tirs))
            Joueur.x += 50;

        Salut.parcour(Tirs, TirsJoueur, Enemy, Adversaire, Joueur, Player, window);

        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);

        if (Enemy.size() == 0) break;
    }
    return 0;
}
