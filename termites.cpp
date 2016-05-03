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
bool egalCoord(Coord coord1, Coord coord2) {
    return coord1.x == coord2.x && coord1.y == coord2.y;
}
bool estDansTerrain(Coord coord) {
    return coord.x >= 0 && coord.y >= 0
            && coord.x < TAILLE && coord.y < TAILLE;
}

Termite creerTermite(int indice, int x, int y) {
    Termite m;
    m.coord = creerCoord(x, y);
    m.ancien_coord = creerCoord(x, y);
    m.indice = indice;
    m.direction = directionAleatoire();
    m.brindille = false;
    m.sablier = 0;
    m.sens_rotation = sensRotationAleatoire();
    m.tourner_sur_place = false;
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
void changerTypePlace(Place &p, int type) {
    p.type = type;
}

bool contientTermite(Place p) {
    return typePlace(p) == PLACE_TYPE_TERMITE;
}
bool contientBrindille(Place p) {
    return typePlace(p) == PLACE_TYPE_BRINDILLE;
}
bool estVide(Place p) {
    return typePlace(p) == PLACE_TYPE_VIDE;
}//verifie  par des booleens si une place est vide ou contient un termite ou une brindille

Place& coord2Place(Terrain &t, Coord coord) {
    return t.places[coord.y][coord.x];
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
    m.sens_rotation = sens;
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
    if (m.sens_rotation == SENS_ROTATION_GAUCHE) {
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
        cout << "\x1B[1m"; // gras
        if (y) cout << endl;
        for (int x = 0; x < TAILLE; x++) {
            Place &p = coord2Place(t, creerCoord(x, y));
            switch (typePlace(p)){
                case PLACE_TYPE_VIDE:{
                    cout << "\x1B[44m"; // couleur bleue
                    cout << ' ';
                break;
                }
                case PLACE_TYPE_BRINDILLE:{
                    cout << "\x1B[47m"; // couleur blanche
                    cout << '0';
                break;
                }
                case PLACE_TYPE_TERMITE:{
                    Termite m = t.termites[p.indtermite];
                    cout << (porteBrindille(m) ? "\x1B[43m" : "\x1B[42m"); // couleur orange / verte
                    afficheTermite(m);
                break;
                }
                default:
                    cout << "?";
            }
        //    cout << " ";
        }
        cout << "\x1B[0m"; // reset couleurs
    }
    cout << endl;
}

void chargerBrindille(Termite &m, Place &p) {
    placeVide(p);
    m.brindille = true;
}

void dechargerBrindille(Termite &m, Place &p) {
    changerTypePlace(p, PLACE_TYPE_BRINDILLE);
    m.brindille = false;
}

bool actionPlaceTermite(Termite &m, Place &p) {
    switch (typePlace(p)) {
        case PLACE_TYPE_TERMITE:
            definirSensRotationTermite(m, sensRotationAleatoire());
            tourneTermite(m);
            return true;
        case PLACE_TYPE_BRINDILLE:
            if (m.vient_de_se_retourner) {
                tourneTermite(m);
            } else if (porteBrindille(m)) {
                tourneTermite(m); // le termite tourne une fois sur place,
                m.tourner_sur_place = true; // et il va le faire à chaque tour jusqu'à ce qu'il trouve une
                                            // place vide pour poser sa brindille
            } else { // tout est ok, il peut donc
                chargerBrindille(m, p);    // charger la brindille,
                m.sablier = NB_DIRECTIONS/2; // et se retourne
                                             // le termite va tourner automatiquement pendant NB_DIRECTIONS/2 tours
            }
            return true;
        case PLACE_TYPE_VIDE:
        default:
            return false;
    }
}

void deplaceTermiteDansTerrain(Terrain &t, Termite &m, Coord coord) {
   Place &old_place = coord2Place(t, m.coord);
   Place &new_place = coord2Place(t, coord);

   changerTypePlace(old_place, PLACE_TYPE_VIDE);

   changerTypePlace(new_place, PLACE_TYPE_TERMITE);
   new_place.indtermite = m.indice;

   copierCoordDans(m.ancien_coord, m.coord);
   copierCoordDans(m.coord, coord);
}

void mouvementTermites(Terrain &t) {
    for (int i = 0; i < t.nbtermites; i++) { // on parcourt le tableau contenant tous les termites du terrain
        Termite &m = t.termites[i]; // on prend le termite courant
        if (m.sablier > 0) { // ...sinon, si son sablier est positif...
            tourneTermite(m); // il tourne automatiquement,
            m.sablier--; // et décrémente son sablier
            if (m.sablier == 0) {
                m.vient_de_se_retourner = true; // on interdit au termite de charger une brindille au prochain tour
            }
        } else {
            Coord coord = coordDevant(m); // on récupère les coordonnées de la place se trouvant devant lui
            if (!estDansTerrain(coord)) { // le termite est arrivé au bord du terrain, il tourne...
                definirSensRotationTermite(m, sensRotationAleatoire());
                tourneTermite(m);
            } else { // ...sinon
                Place &p = coord2Place(t, coord); // on récupère la place se trouvant devant le termite
                if (!actionPlaceTermite(m, p)) { // ce dernier essaie d'agir avec elle...
                    // ...mais rien ne se passe, c'est donc une place vide
                    if (m.tourner_sur_place && !egalCoord(coord, m.ancien_coord)) { // si le termite veut déposer sa brindille sur
                                                                          // la place vide la plus proche,
                                                                          // et si ce n'est pas sa case d'entrée.. // => on préserve la liberté des termites
                        dechargerBrindille(m, p); // il décharge sa brindille sur la place vide devant lui,
                        m.sablier = NB_DIRECTIONS/2-1; // et se retourne // on peut aussi mettre NB_DIRECTIONS/2-1
                                                                       // (alternative à bool vient_de_se_retourner,
                                                                       // mais il ne va pas se retourner complètement)
                        m.tourner_sur_place = false;
                    } else if (rand()%10 < 1) { // ..le termite a 1 chance sur 10 de tourner dans une direction aléatoire..
                        definirSensRotationTermite(m, sensRotationAleatoire());
                        tourneTermite(m);
                    } else { // ..sinon,
                        deplaceTermiteDansTerrain(t, m, coord); // le termite avance
                    }
                    m.vient_de_se_retourner = false;
                }
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
        int nb_passes = 1;
        while (true) {
            c = toupper(getchar()); // On obtient la touche saisie par l'utilisateur...
            if (c == 'C') { // la touche c quitte l'application
                quitterApplication();
                break;
            } else if (c == '\n') {
                usleep(50000); // si on appuie sur entrée, attendre 50ms faire une passe (Entrée : avance frame à frame)
                break;
            } else if (c == 'Q') {
                usleep(40000); // si on appuie sur 's', attendre 40ms et faire une passe
                break;
            } else if (c == 'S') {
                usleep(20000); // si on appuie sur 's', attendre 20ms et faire une passe
                break;
            } else if (c == 'S') {
                usleep(5000); // si on appuie sur 's', faire une passe
                break;
            } else if (c == 'F') {
                nb_passes = 50; // si on appuie sur 'f', faire 50 passes
                break;
            } else if (c == 'G') {
                nb_passes = 250; // si on appuie sur 'g', faire 250 passes
                break;
            } else if (c == 'H') {
                nb_passes = 500; // si on appuie sur 'h', faire 500 passes
                break;
            } else if (c == 'J') {
                nb_passes = 1000;
                break;
            }
        }
        cout << endl;
        for (int i = 0; i < nb_passes; i++) {
            mouvementTermites(t); // on continue l'animation
        }
        afficheTerrain(t);
        usleep(10000); // on attend 10ms pour que l'animation soit fluide
    }

    quitterApplication();
    return 0;
}
