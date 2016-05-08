#include <ctype.h> // pour toupper()
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <string>

#include "projet_termites_outils_terminal.h"
#include "projet_termites_common.h"
#include "projet_termites.h"
#include "termite.h"

using namespace std;

void placeVide(Place &p) {
    p.type = PLACE_TYPE_VIDE;
}
int typePlace(Place p) {
    return p.type;
}
void changerTypePlace(Place &p, int type) {
    p.type = type;
}
void echangerPlaces(Place &p1, Place &p2) {
    int ancien_type_p1 = p1.type;
    p1.type = p2.type;
    p2.type = ancien_type_p1;
    if (p2.type == PLACE_TYPE_TERMITE) {
        if (p1.type == PLACE_TYPE_TERMITE) { // si les 2 places contiennent des termites, on échange les indtermites
            int ancien_indtermite_p1 = p1.indtermite;
            p1.indtermite = p2.indtermite;
            p2.indtermite = ancien_indtermite_p1;
        } else { // si p2 va contenir un termite, on lui donne l'indtermite de p1
            p2.indtermite = p1.indtermite;
        }
    } else if (p1.type == PLACE_TYPE_TERMITE) { // si p1 va contenir un termite, on lui donne l'indtermite de p2
        p1.indtermite = p2.indtermite;
    }
}

bool contientTermite(Place p) {
    return typePlace(p) == PLACE_TYPE_TERMITE;
}

bool contientBrindille(Place p) {
    return typePlace(p) == PLACE_TYPE_BRINDILLE;
}

bool estVide(Place p) {
    return typePlace(p) == PLACE_TYPE_VIDE;
}

Place& coord2Place(Terrain &t, Coord coord) {
    return t.places[coord.y][coord.x];
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

void afficheTerrain(Terrain t) {
    cout << CURSEUR_DEBUT << endl;
    for (int y = 0; y < TAILLE; y++) {
        if (y) cout << endl;
        cout << ' ' << CC_POLICE_GRAS;
        for (int x = 0; x < TAILLE; x++) {
            Place &p = coord2Place(t, creerCoord(x, y));
            switch (typePlace(p)){
                case PLACE_TYPE_VIDE:{
                    cout << CC_FOND_BLEU;
                    cout << ' ';
                break;
                }
                case PLACE_TYPE_BRINDILLE:{
                    cout << CC_FOND_BLANC;
                    cout << '0';
                break;
                }
                case PLACE_TYPE_TERMITE:{
                    Termite m = t.termites[p.indtermite];
                    afficheTermite(m);
                break;
                }
                default:
                    cout << '?';
            }
        //    cout << " "; // décommenter pour que les places soient des carrés et pas des rectangles
        }
        cout << CC_RESET; // reset couleurs
    }
    cout << endl;
}

void chargerBrindilleTermitePlace(Termite &m, Place &p) {
    placeVide(p);
    chargerBrindilleTermite(m);
}

void dechargerBrindilleTermitePlace(Termite &m, Place &p) {
    changerTypePlace(p, PLACE_TYPE_BRINDILLE);
    dechargerBrindilleTermite(m);
}

void deplaceTermiteDansTerrain(Terrain &t, Termite &m, Coord coord) {
   Place &ancienne_place_termite = coord2Place(t, m.coord);
   Place &nouvelle_place_termite = coord2Place(t, coord);
   echangerPlaces(ancienne_place_termite, nouvelle_place_termite);
   teleporterTermite(m, coord);
}

void actionPlaceTermite(Terrain &t, Termite &m, Coord coord) {
   Place &p = coord2Place(t, coord);
    switch (typePlace(p)) {
        case PLACE_TYPE_TERMITE:
            definirSensRotationTermite(m, sensRotationAleatoire());
            tourneTermite(m);
        break;
        case PLACE_TYPE_BRINDILLE:
            if (actionsAvecBrindillesBloqueesTermite(m)) {
                tourneTermite(m);
            } else if (porteBrindilleTermite(m)) {
                tourneTermite(m); // le termite tourne une fois sur place,
                definirModeTournerSurPlaceTermite(m, true); // et il va le faire à chaque tour jusqu'à ce qu'il trouve une
                                                            // place vide pour poser sa brindille
            } else { // tout est ok, il peut donc
                chargerBrindilleTermitePlace(m, p);    // charger la brindille,
                retourneProgressivementTermite(m, NB_DIRECTIONS/2);  // et se retourner
                                                                     // le termite va tourner automatiquement pendant NB_DIRECTIONS/2 tours
            }
        break;
        case PLACE_TYPE_VIDE:
        default:
            if (doitTournerSurPlaceTermite(m) && !egalCoord(coord, m.ancien_coord)) { // si le termite veut déposer sa brindille sur
                                                                            // la place vide la plus proche,
                                                                            // et si ce n'est pas sa case d'entrée.. // => on préserve la liberté des termites
                dechargerBrindilleTermitePlace(m, p); // il décharge sa brindille sur la place vide devant lui,
                retourneProgressivementTermite(m, NB_DIRECTIONS/2-1); //  et se retourne // on peut aussi mettre NB_DIRECTIONS/2-1 au 
                                                                                         // lieu de NB_DIRECTIONS/2 (alternative à bool vient_de_se_retourner,
                                                                                         // mais il ne va pas se retourner complètement) // unmod
                definirModeTournerSurPlaceTermite(m, false);
            } else if (aleatoire(0.1)) { // ..le termite a 1 chance sur 10 de tourner dans une direction aléatoire..
                definirSensRotationTermite(m, sensRotationAleatoire());
                tourneTermite(m);
            } else { // ..sinon,
                deplaceTermiteDansTerrain(t, m, coord); // le termite avance
            }
            debloquerActionsAvecBrindillesSiNecessaireTermite(m);
        break;
    }
}

void rassemblerBrindilles(Terrain &t, Termite &m) {
    if (estSablierActifTermite(m)) { // ...sinon, si son sablier est positif...
        tourneTermite(m); // il tourne automatiquement,
        decrementerSablierTermite(m); // et décrémente son sablier
    } else {
        Coord coord = coordDevantTermite(m); // on récupère les coordonnées de la place se trouvant devant lui
        if (!estValideCoord(coord)) { // le termite est arrivé au bord du terrain, il tourne...
            definirSensRotationTermite(m, sensRotationAleatoire());
            tourneTermite(m);
        } else { // ...sinon, la place existe,
            actionPlaceTermite(t, m, coord); // et le termite agir selon son type
        }
    }
}

void mouvementTermites(Terrain &t) {
    for (int i = 0; i < t.nbtermites; i++) { // on parcourt le tableau contenant tous les termites du terrain
        Termite &m = t.termites[i]; // on prend le termite courant
        rassemblerBrindilles(t, m);
    }
}

int main() {
    srand(time(NULL));
    definirModeTerminal(true); // on prend le contrôle du terminal, pour que getchar() 
                               // n'attende pas que l'utilisateur ait saisi une touche

    cout << EFFACER_TERMINAL;

    cout << endl;
    Terrain t;
    initialiseTerrain(t);
    afficheTerrain(t);

    bool mouvement_automatique = false;
    char c;

    while (true) {

        if (mouvement_automatique) { // mouvement automatique...
            do {
                c = toupper(getchar());
                if (c == 'C') {
                    quitterApplication();
                    break;
                } else if (c == 'P') {
                    mouvement_automatique = false;
                } else {
                    cout << CC_POLICE_GRAS << MSG_KEYS "  " CC_POLICE_GRAS "P" CC_RESET " NORMAL" << CC_POLICE_NORMAL;// << endl;
                //    usleep(75000);
                    usleep(55000);
                    mouvementTermites(t);
                    afficheTerrain(t);
                }
            } while (mouvement_automatique);

        } else { // ...mouvement non automatique
            do {
                cout << CC_POLICE_GRAS << MSG_KEYS "  " CC_POLICE_GRAS "P" CC_RESET " AUTO  " << CC_POLICE_NORMAL;
                int nb_passes = 1;
                while (true) {
                    c = toupper(getchar()); // On obtient la touche saisie par l'utilisateur...
                    if (c == 'C') { // la touche c quitte l'application
                        quitterApplication();
                        break;
                    } else if (c == '\n') {
                        usleep(60000); // si on appuie sur entrée, attendre 60ms puis faire une passe (Entrée : avance frame à frame)
                        break;
                    } else if (c == 'Q') {
                        usleep(20000); // si on appuie sur 'q', attendre 20ms puis faire une passe
                        break;
                    } else if (c == 'S') {
                        usleep(10000); // si on appuie sur 's', attendre 10ms puis faire une passe
                        break;
                    } else if (c == 'D') {
                        usleep(5000); // si on appuie sur 'd', faire une passe
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
                        nb_passes = 1000; // si on appuie sur 'h', faire 500 passes
                        break;
                    } else if (c == 'P') {
                        mouvement_automatique = true;
                        break;
                    }
                }
                cout << endl;
                for (int i = 0; i < nb_passes; i++) {
                    mouvementTermites(t); // on continue l'animation
                }
                afficheTerrain(t);
             //   usleep(25000); // on attend 25ms pour que l'animation soit fluide et pour éviter que le terminal freeze
                                                               // avec CURSEUR_DEBUT au lieu de EFFACER_TERMINAL on peut attendre moins :
             //   usleep(25000); // on attend 10ms pour que l'animation soit fluide et pour éviter que le terminal freeze
                while (getchar() != EOF) {} // on supprime les touches pressées pendant le temps d'attente

            } while (!mouvement_automatique);
        }
    }

    quitterApplication();
    return 0;
}
