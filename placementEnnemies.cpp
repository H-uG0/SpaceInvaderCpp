#include <iostream>
#include <vector>
#include <string>#include <iostream>
#include <vector>
#include <string>

using namespace std;

    const string KReset   ("0");
    const string KNoir    ("30");
    const string KRouge   ("31");
    const string KGreen    ("32");
    const string KYellow   ("33");
    const string KBleu    ("34");
    const string KMAgenta ("35");
    const string KCyan    ("36");



    const char KEmpty               = ' ';  // case vide de l'écran
    const char KRight               = '6';  // déplacement vers la droite
    const char KLeft                = '4';  // Déplacement vers la gauche
    const char KShoot               = '5';  // Lancé de torpille

    //  Constantes liées à l'envahisseur

    const string KInvadersColor (KYellow);  // Couleur de l'envahisseur
    const char KInsideInvader       = 'W';  // caractèrere formant l'envahisseur
    const char KMissile             = 'T';  // missile
    const unsigned KInvadersSize    =  4;   // nombre de caractères qui forment l'envahisseur
    const unsigned KInvadersMiddle  = KInvadersSize / 2;
    const string KInvadersForm (KInvadersSize, KInsideInvader);  // forme de l'envahisseur

    // Constantes liées au joueur

    const string KMyColor (KGreen);
    const char KInsideMe            = 'A';
    const char KTorpedo             = '|';
    const unsigned KMySize          = 1;
    const unsigned KMyMiddle        = KMySize / 2;
    const string KMyForm (KMySize, KInsideMe);

    // Constantes liées à l'eapace (l'écran)

    const unsigned KSizeLine   = 10;   // Nombre de lignes de l'écran (de l'espace)
    const unsigned KSizeSpace  = 10;   // Nombre de colonnes de l'écran (de l'espace)

    const unsigned KBegInvader = 0;    // Numéro de colonne où commence l'envahisseur
    const unsigned KBegMe      = KSizeLine / 2;  // Numéro de colonne où commence le joueur

    typedef vector <string> CVString;    // c'est le type de l'écran (l'espace, la matrice)

    const string KEmptyLine (KSizeLine, KEmpty);  // Une ligne vide de la matrice

    const unsigned KRatioMeInvaders = 4;    // Nombre de fois où c'est le tour du joueur pour un tour de l'envahisseur


    CVString placeEnnemiesOnGridRectangle(char ennemieSign,unsigned Xstart,unsigned Ystart,unsigned width, unsigned len, CVString grid,unsigned spacingY, unsigned spacingX);
    CVString placeEnnemiesOnGridPyramid(char ennemieSign,unsigned Xstart,unsigned Ystart,unsigned width, unsigned len, CVString grid);
    CVString fillInvader(CVString grid,unsigned width,unsigned len,char invaderCar, char hitboxCar);

    void ClearScreen ()
    {
        cout << "\033[H\033[2J";
    }
    
    void Couleur (const string & coul)
    {
        cout << "\033[" << coul <<"m";
    }


    void afficherGrille(CVString grid, string invaderCar){
        cout<<'\n';
        unsigned i;
        for(i = 0; i <= grid.size()-1; i++){
            if(grid[i] == invaderCar){
                Couleur(KRouge);
            }
            cout << grid[i];
            Couleur(KReset);
            cout<<endl;
        }
    }

    CVString creerGrille(char emptychar, unsigned width, unsigned len){
        unsigned i;
        string emptyline;
        CVString grid;
        for(i = 0; i < width; i++){
            emptyline += emptychar;
        }
        for(i = 0; i < len; i++){
            grid.push_back(emptyline);
        }
        return grid;
    }

int main()
    {
        CVString grid = creerGrille('0',165,105);
        afficherGrille(grid, "w");
        //cout<<"ok"<<'\n'<<'\n';
        grid = placeEnnemiesOnGridRectangle('w', 0, 0, 130, 50, grid,5,5);
        //cout<<"ok"<<'\n'<<'\n';
        afficherGrille(grid, "w");
        grid = fillInvader(grid, 4, 4, 'w', 'h');
        afficherGrille(grid, "w");
        return 0;
    }
    
    CVString fillInvader(CVString grid,unsigned width,unsigned len,char invaderCar, char hitboxCar){
        unsigned x,y;
        for(y = 0; y <= grid.size()-1; y++){
            for(x = 0; x <= grid[0].size()-1; x++){
                if(grid[y][x]==invaderCar){
                    grid = placeEnnemiesOnGridRectangle(hitboxCar, x-1, y-1, width, len, grid, 1, 1);
                }
            }
        }
        return grid;
    }

    CVString placeEnnemiesOnGridRectangle(char ennemieSign,unsigned Xstart,unsigned Ystart,unsigned width, unsigned len, CVString grid,unsigned spacingY, unsigned spacingX)
    // EnnemieSign : symbole ennemi ('w')
    // Xstart : debut du bloc d'ennemi sur X
    // Ystart : debut du bloc d'ennemi sur Y
    // width et len : largeur et longueur du bloc
    // grid la grille
    // spacingY : longeur de l'ennemi + marge avec ennemi suivant sur Y
    // spacingX : largeur de l'ennemi + marge avec ennemi suivant sur X
    {   if((width + Xstart <= grid.size())and(len + Ystart <= grid[0].size())){
            unsigned x, y;
            unsigned tempX, tempY;
            tempX = Xstart;
            tempY = Ystart;
            for(y = Ystart; y  < len + Ystart; y++){
                if(y == tempY+spacingY){
                    tempY = y;
                    cout <<'y' <<y << endl;
                    for(x = Xstart; x < width + Xstart; x++){
                        if(x == tempX+spacingX){
                            cout <<'x' <<x << endl;
                            tempX = x;
                            grid[y][x] = ennemieSign;
                        }

                    }
                    tempX = Xstart;
                }
                
            }

        }
        return grid;
    }


    CVString placeEnnemiesOnGridPyramid(char ennemieSign,unsigned Xstart,unsigned Ystart,unsigned width, unsigned len, CVString grid){
        unsigned x, y;
        x = Xstart - width/2;
        for(y = Ystart; y  < len + Ystart; y++){
            while(x < Xstart + width/2){
                grid[y][x] = ennemieSign;
                x++;
            }
            width = width - 2;
            x = Xstart - width/2;
        }
        return grid;
    }


   /* vector<vector<unsigned>> GridToCoo(unsigned windowWidth, unsigned windowLen, CVString grid){
        unsigned ecartX, ecartY;
        ecart = windowWidth/grid.size() ;
        ecart = window

    }*/

   // CVString moveInvaders(CVString,char invaderCar){

   // }




using namespace std;

    const string KReset   ("0");
    const string KNoir    ("30");
    const string KRouge   ("31");
    const string KGreen    ("32");
    const string KYellow   ("33");
    const string KBleu    ("34");
    const string KMAgenta ("35");
    const string KCyan    ("36");

    void Couleur (const string & coul)
    {
        cout << "\033[" << coul <<"m";
    }



    const char KEmpty               = ' ';  // case vide de l'écran
    const char KRight               = '6';  // déplacement vers la droite
    const char KLeft                = '4';  // Déplacement vers la gauche
    const char KShoot               = '5';  // Lancé de torpille

    //  Constantes liées à l'envahisseur

    const string KInvadersColor (KYellow);  // Couleur de l'envahisseur
    const char KInsideInvader       = 'W';  // caractèrere formant l'envahisseur
    const char KMissile             = 'T';  // missile
    const unsigned KInvadersSize    =  4;   // nombre de caractères qui forment l'envahisseur
    const unsigned KInvadersMiddle  = KInvadersSize / 2;
    const string KInvadersForm (KInvadersSize, KInsideInvader);  // forme de l'envahisseur

    // Constantes liées au joueur

    const string KMyColor (KGreen);
    const char KInsideMe            = 'A';
    const char KTorpedo             = '|';
    const unsigned KMySize          = 1;
    const unsigned KMyMiddle        = KMySize / 2;
    const string KMyForm (KMySize, KInsideMe);

    // Constantes liées à l'eapace (l'écran)

    const unsigned KSizeLine   = 10;   // Nombre de lignes de l'écran (de l'espace)
    const unsigned KSizeSpace  = 10;   // Nombre de colonnes de l'écran (de l'espace)

    const unsigned KBegInvader = 0;    // Numéro de colonne où commence l'envahisseur
    const unsigned KBegMe      = KSizeLine / 2;  // Numéro de colonne où commence le joueur

    typedef vector <string> CVString;    // c'est le type de l'écran (l'espace, la matrice)

    const string KEmptyLine (KSizeLine, KEmpty);  // Une ligne vide de la matrice

    const unsigned KRatioMeInvaders = 4;    // Nombre de fois où c'est le tour du joueur pour un tour de l'envahisseur


    CVString placeEnnemiesOnGridRectangle(char ennemieSign,unsigned Xstart,unsigned Ystart,unsigned width, unsigned len, CVString grid);
    CVString placeEnnemiesOnGridPyramid(char ennemieSign,unsigned Xstart,unsigned Ystart,unsigned width, unsigned len, CVString grid);

    void ClearScreen ()
    {
        cout << "\033[H\033[2J";
    }


    void afficherGrille(CVString grid){
        cout<<'\n';
        unsigned i;
        for(i = 0; i <= grid.size()-1; i++){
            cout << grid[i];
            cout<<endl;
        }
    }

    CVString creerGrille(char emptychar, unsigned width, unsigned len){
        unsigned i;
        string emptyline;
        CVString grid;
        for(i = 0; i < width; i++){
            emptyline += emptychar;
        }
        for(i = 0; i < len; i++){
            grid.push_back(emptyline);
        }
        return grid;
    }

int main()
    {
        CVString grid = creerGrille('0',10,10);
        afficherGrille(grid);
        //cout<<"ok"<<'\n'<<'\n';
        grid = placeEnnemiesOnGridPyramid('w', 5, 0, 8, 5, grid);
        //cout<<"ok"<<'\n'<<'\n';
        afficherGrille(grid);
        return 0;
    }

    CVString placeEnnemiesOnGridRectangle(char ennemieSign,unsigned Xstart,unsigned Ystart,unsigned width, unsigned len, CVString grid)
    {   if((width + Xstart <= grid.size())and(len + Ystart <= grid[0].size())){
            unsigned x, y;
            for(y = Ystart; y  < len + Ystart; y++){
                for(x = Xstart; x < width + Xstart; x++){
                    grid[y][x] = ennemieSign;
                }
            }

        }
        return grid;
    }


    CVString placeEnnemiesOnGridPyramid(char ennemieSign,unsigned Xstart,unsigned Ystart,unsigned width, unsigned len, CVString grid){
        unsigned x, y;
        x = Xstart - width/2;
        for(y = Ystart; y  < len + Ystart; y++){
            while(x < Xstart + width/2){
                grid[y][x] = ennemieSign;
                x++;
            }
            width = width - 2;
            x = Xstart - width/2;
        }
        return grid;
    }



