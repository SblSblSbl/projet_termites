#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

#include "termites.h"
using namespace std;

void WTF(string str) {
    cout << "\x1B[41m \x1B[1mWTF : \x1B[2m" << str << " \x1B[0m";
};


bool aleatoire(double p) {
    return rand() < p*(RAND_MAX + 1.);
}
int directionAleatoire() {
    return rand() % NB_DIRECTIONS;
}

Coord creerCoord(int i, int j) {
   Coord c;
   c.x = i;
   c.y = j;
   return c;
}
Termite creerTermite(int indice, int x, int y) {
    Termite m;
    m.coord = creerCoord(x, y);
    m.indice = indice;
    m.direction = directionAleatoire();
    m.brindille = false;
    m.tourner_sur_place = false;
    m.sablier = 0;
    return m;
}

void placeVide(Place &p) {
    p.type = PLACE_TYPE_VIDE;
}

bool contientTermite(Place p) {
    return p.type == PLACE_TYPE_TERMITE;
}
bool contientBrindille(Place p) {
    return p.type == PLACE_TYPE_BRINDILLE;
}
bool estVide(Place p) {
    return p.type == PLACE_TYPE_VIDE;
}//verifie  par des booleens si une place est vide ou contient un termite ou une brindille

Coord coordDevant(Termite t){
    if (t.direction < 0 || t.direction >= NB_DIRECTIONS) { // pas bien
        WTF("[coordDevant] Termite mutante");
        return creerCoord(-1, -1);
    }
    int ind[8][2] = {{0,-1}, {-1,1}, {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}};
    //          haut| haut_droite| droite| ba|s_droite |bas |bas_gauche |gauche |haut_gauche
    return creerCoord(t.coord.x + ind[t.direction][0], t.coord.y + ind[t.direction][1]);
}

void tourneGauche(Termite &t){
    t.direction=(t.direction - 1) % NB_DIRECTIONS;
}

void tourneDroite(Termite &t){
    t.direction=(t.direction + 1) % NB_DIRECTIONS8;
}

void initialiseTerrain(Terrain &t) {
    t.nbtermites = 0;
    for (int y = 0; y < TAILLE; y++) {
        for (int x = 0; x < TAILLE; x++) {
            if (aleatoire(POURCENTAGE_TERMITES/100.)) {
                // aleatoire est entre 0 et 1
                Place p = t.places[y][x];
                p.type = PLACE_TYPE_TERMITE;
                p.indtermite = t.nbtermites;
                t.places[y][x] = p;
                t.termites[p.indtermite] = creerTermite(p.indtermite, x, y);
                t.nbtermites++;
            } else {
                if (aleatoire(POURCENTAGE_BRINDILLES/100)) {
                    t.places[y][x].type = PLACE_TYPE_BRINDILLE;
                } else {
                    t.places[y][x].type = PLACE_TYPE_VIDE;
                }
            }
        }
    }
}

void afficheTermite(Termite m) {
    switch (m.direction) {
        case DIRECTION_GAUCHE:
        case DIRECTION_DROITE:
            cout << "-";
            break;
        case DIRECTION_HAUT:
        case DIRECTION_BAS:
            cout << "|";
            break;
        case DIRECTION_GAUCHE_HAUT:
        case DIRECTION_DROITE_BAS:
            cout << "\\";
            break;
        case DIRECTION_GAUCHE_BAS:
        case DIRECTION_DROITE_HAUT:
            cout << "/";
            break;
        default:
            cout << "D";
    }
}
void afficheTerrain(Terrain t) {
    for(int y = 0; y < TAILLE; y++) {
        if (y) cout << endl;
        for (int x = 0; x < TAILLE; x++) {
            Place p = t.places[y][x];
            int type_place = p.type;
            switch (type_place){
                case PLACE_TYPE_VIDE:{
                    cout << "-";
                break;
                }
                case PLACE_TYPE_BRINDILLE:{
                    cout << "0";
                break;
                }
                case PLACE_TYPE_TERMITE:{
                    Termite m = t.termites[p.indtermite];
                    afficheTermite(m);
                break;
                }
                default:
                    cout << "?";
            }
        }
    }
    cout << endl << endl;
}

int main() {
    srand(time(NULL));
    cout << endl;
    Terrain t;
    initialiseTerrain(t);
    afficheTerrain(t);
    return 0;
}
