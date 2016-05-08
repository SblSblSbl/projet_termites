#include <iostream>
#include <string>

#include "projet_termites_common.h"
#include "termite.h"
using namespace std;


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
bool porteBrindilleTermite(Termite m) {
    return m.brindille;
}

Coord coordDevantTermite(Termite t){
    if (t.direction < 0 || t.direction >= NB_DIRECTIONS) { // pas bien
        WTF("[coordDevantTermite] Termite mutante");
        return creerCoord(-1, -1);
    }
    int ind[8][2] = {{0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}};
    //          haut| haut_droite| droite| ba|s_droite |bas |bas_gauche |gauche |haut_gauche
    return creerCoord(t.coord.x + ind[t.direction][0], t.coord.y + ind[t.direction][1]);
}

void definirSensRotationTermite(Termite &m, int sens) {
    m.sens_rotation = sens;
}

void tourneGaucheTermite(Termite &m){
    m.direction = (m.direction - 1);
    if (m.direction < 0) {
        m.direction += NB_DIRECTIONS;
    }
}

void tourneDroiteTermite(Termite &m){
    m.direction = (m.direction + 1) % NB_DIRECTIONS;
}

void tourneTermite(Termite &m) {
    if (m.sens_rotation == SENS_ROTATION_GAUCHE) {
        tourneGaucheTermite(m);
    } else {
        tourneDroiteTermite(m);
    }
}

void retourneProgressivementTermite(Termite &m, int nb_tours) {
    m.sablier = nb_tours;
}

bool estSablierActifTermite(Termite m) {
    return m.sablier > 0;
}

void decrementerSablierTermite(Termite &m) {
    if (m.sablier > 0) {
        m.sablier--;
        if (m.sablier == 0) {
            m.vient_de_se_retourner = true;
        }
    }
}

bool doitTournerSurPlaceTermite(Termite m) {
    return m.tourner_sur_place;
}
void definirModeTournerSurPlaceTermite(Termite &m, bool actif) {
    m.tourner_sur_place = actif;
}

bool actionsAvecBrindillesBloqueesTermite(Termite m) {
    return m.vient_de_se_retourner;
}
void debloquerActionsAvecBrindillesSiNecessaireTermite(Termite &m) {
    m.vient_de_se_retourner = false;
}

void chargerBrindilleTermite(Termite &m) {
    m.brindille = true;
}

void dechargerBrindilleTermite(Termite &m) {
    m.brindille = false;
}

void teleporterTermite(Termite &m, Coord coord) {
   copierCoordDans(m.ancien_coord, m.coord);
   copierCoordDans(m.coord, coord);
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
