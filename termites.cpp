#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <unistd.h>

#include "s91k2048_outils_terminal.h"
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
int sensRotationAleatoire() {
    return rand() % 2;
}

Coord creerCoord(int i, int j) {
   Coord c;
   c.x = i;
   c.y = j;
   return c;
}
void copierCoordDans(Coord &dest, Coord src) {
    dest.x = src.x;
    dest.y = src.y;
}
bool estDansTerrain(Coord coord) {
    return coord.x >= 0 && coord.y >= 0
            && coord.x < TAILLE && coord.y < TAILLE;
}

Termite creerTermite(int indice, int x, int y) {
    Termite m;
    m.coord = creerCoord(x, y);
    m.indice = indice;
    m.direction = directionAleatoire();
    m.brindille = false;
    m.tourner_sur_place = false;
    m.sablier = 0;
    m.sensRotation = sensRotationAleatoire();
    return m;
}
bool porteBrindille(Termite m) {
    return m.brindille;
}

void placeVide(Place &p) {
    p.type = PLACE_TYPE_VIDE;
}
int typePlace(Place p) {
    return p.type;
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

Place& coord2Place(Terrain &t, Coord coord) {
    return t.places[coord.y][coord.x];
}

void changerTypePlace(Place &p, int type) {
    p.type = type;
}

Coord coordDevant(Termite t){
    if (t.direction < 0 || t.direction >= NB_DIRECTIONS) { // pas bien
        WTF("[coordDevant] Termite mutante");
        return creerCoord(-1, -1);
    }
    int ind[8][2] = {{0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}};
    //          haut| haut_droite| droite| ba|s_droite |bas |bas_gauche |gauche |haut_gauche
    return creerCoord(t.coord.x + ind[t.direction][0], t.coord.y + ind[t.direction][1]);
}

void definirSensRotationTermite(Termite &m, int sens) {
    m.sensRotation = sens;
}

void tourneGauche(Termite &m){
    m.direction = (m.direction - 1);
    if (m.direction < 0) {
        m.direction += NB_DIRECTIONS;
    }
}

void tourneDroite(Termite &m){
    m.direction = (m.direction + 1) % NB_DIRECTIONS;
}

void tourneTermite(Termite &m) {
    if (m.sensRotation == SENS_ROTATION_GAUCHE) {
        tourneGauche(m);
    } else {
        tourneDroite(m);
    }
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
    for (int y = 0; y < TAILLE; y++) {
    //    cout << "\x1B[1m"; // gras
        if (y) cout << endl;
        for (int x = 0; x < TAILLE; x++) {
            Place &p = coord2Place(t, creerCoord(x, y));
            switch (typePlace(p)){
                case PLACE_TYPE_VIDE:{
                //    cout << "\x1B[44m"; // couleur bleue
                    cout << '_';
                break;
                }
                case PLACE_TYPE_BRINDILLE:{
                //    cout << "\x1B[47m"; // couleur blanche
                    cout << '0';
                break;
                }
                case PLACE_TYPE_TERMITE:{
                    Termite m = t.termites[p.indtermite];
                //    cout << (porteBrindille(m) ? "\x1B[43m" : "\x1B[42m"); // couleur orange / verte
                    afficheTermite(m);
                break;
                }
                default:
                    cout << "?";
            }
        //    cout << " ";
        }
    //    cout << "\x1B[0m"; // reset couleurs
    }
    cout << endl;
}

void chargerBrindille(Termite &m, Place &p) {
    placeVide(p);
    m.brindille=true;
}

void dechargerBrindille(Termite &m, Place &p) {
    changerTypePlace(p, PLACE_TYPE_BRINDILLE);
    m.brindille=false;
}

bool actionPlaceTermite(Termite &m, Place &p) {
    switch (typePlace(p)) {
        case PLACE_TYPE_TERMITE:
            definirSensRotationTermite(m, SENS_ROTATION_DROITE);
            tourneTermite(m);
            return true;
        case PLACE_TYPE_BRINDILLE:
            /* TODO */
            return true;
        case PLACE_TYPE_VIDE:
        default:
            return false;
    }
}

void deplaceTermiteDansTerrain(Terrain &t, Termite &m, Coord coord) {
   Place &old_place=coord2Place(t,m.coord);
   Place  &new_place=coord2Place(t,coord);
   new_place.indtermite=m.indice;
   copierCoordDans(m.coord,coord);
   changerTypePlace(old_place,PLACE_TYPE_VIDE);
   changerTypePlace(new_place,PLACE_TYPE_TERMITE);
   

}

void mouvementTermites(Terrain &t) {
    for (int i = 0; i < t.nbtermites; i++) {
        Termite &m = t.termites[i];
        Coord coord = coordDevant(m);
        if (!estDansTerrain(coord)) { // le termite est arrivé au bord du terrain, il tourne
            definirSensRotationTermite(m, sensRotationAleatoire());
            tourneTermite(m);
        } else { /* TODO */
            Place &p = coord2Place(t, coord);
            if (!actionPlaceTermite(m, p)) { // le termite essaye d'agir avec la place se trouvant devant lui...
                deplaceTermiteDansTerrain(t, m, coord); // ...mais rien ne se passe; le termite avance
            }
        }
    }
}

void quitterApplication() {
    cout << endl << endl;
    definirModeTerminal(false); // on redonne le contrôle du terminal à l'utilisateur
    exit(0);
}

int main() {
    srand(time(NULL));
    definirModeTerminal(true); // on prend le contrôle du terminal, pour que getchar() 
                               // n'attende pas que l'utilisateur ait saisi une touche

    cout << endl;
    Terrain t;
    initialiseTerrain(t);
    afficheTerrain(t);

    char c;
    while (true) {
        cout << "Entrer commande : ";
        while (true) {
            c = toupper(getchar()); // On obtient la touche saisie par l'utilisateur...
            if (c == 'C') { // la touche c quitte l'application
                quitterApplication();
                break;
            } else if (c == '\n') {
                usleep(50000); // si on appuie sur entrée, attendre 50ms (Entrée : avance frame à frame)
                break;
            } else if (c == 'Q') {
                usleep(40000); // si on appuie sur 's', attendre 40ms
                break;
            } else if (c == 'S') {
                usleep(20000); // si on appuie sur 's', attendre 20ms
                break;
            } else if (c == 'F') {
                for (int i = 0; i < 50; i++) mouvementTermites(t); // si on appuie sur 'f', faire 50 itérations (F : avance rapide)
                break;
            } else if (c == 'G') {
                for (int i = 0; i < 250; i++) mouvementTermites(t); // si on appuie sur 'g', faire 250 itérations
                break;
            } else if (c == 'H') {
                for (int i = 0; i < 500; i++) mouvementTermites(t); // si on appuie sur 'h', faire 500 itérations
                break;
            } else if (c == 'J') {
                for (int i = 0; i < 1000; i++) mouvementTermites(t); // si on appuie sur 'j', faire 1000 itérations (J : avance très rapide)
                break;
            }
        }
        cout << endl;
        mouvementTermites(t); // on continue l'animation
        afficheTerrain(t);
        usleep(10000); // on attend 10ms pour que l'animation soit fluide
    }

    quitterApplication();
    return 0;
}
