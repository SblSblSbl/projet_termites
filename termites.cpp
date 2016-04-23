#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;


const int taille = 40;
const double pourcentage_termites = 1.;
const double pourcentage_brindille = 5.;

enum {
    PLACE_TYPE_VIDE,
    PLACE_TYPE_BRINDILLE,
    PLACE_TYPE_TERMITE,
} type_place;
enum {
    DIRECTION_GAUCHE,
    DIRECTION_GAUCHE_HAUT,
    DIRECTION_HAUT,
    DIRECTION_DROITE_HAUT,
    DIRECTION_DROITE,
    DIRECTION_DROITE_BAS,
    DIRECTION_BAS,
    DIRECTION_GAUCHE_BAS,
    NB_DIRECTIONS
} directions;

struct Coord {
    int x;
    int y;
};
struct Place {
    int type;
    int indtermite;
};
struct Termite {
    Coord coord;
    int direction;
    int indice;
    int sablier;
    bool brindille;
    bool tourner_sur_place;
};
struct Terrain {
    Place places[taille][taille];
    Termite termites[taille*taille];
    int nbtermites;
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

void place_vide(Place &p) {
    p.type=PLACE_TYPE_VIDE;
    p.indtermite=-1;
}

bool contient_termite(Place &p) {
    return p.indtermite != -1;
}
bool contient_brindille(Place &p) {
    p.type = PLACE_TYPE_BRINDILLE;
    return true;
}

void initialiseTerrain(Terrain &t) {
    t.nbtermites = 0;
    for (int y = 0; y < taille; y++) {
        for (int x = 0; x < taille; x++) {
            if (aleatoire(pourcentage_termites/100.)) {
                // aleatoire est entre 0 et 1

                Place p = t.places[y][x];
                p.type = PLACE_TYPE_TERMITE;
                p.indtermite = t.nbtermites;
                t.places[y][x] = p;

                t.termites[p.indtermite] = creerTermite(p.indtermite, x, y);
                t.nbtermites++;
            } else {
                if (aleatoire(pourcentage_brindille/100)) {
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
    for(int y = 0; y < taille; y++) {
        if (y) cout << endl;
        for (int x = 0; x < taille; x++) {
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
}

int main() {
    srand(time(NULL));
    Terrain t;
    initialiseTerrain(t);
    afficheTerrain(t);
    return 0;
}
