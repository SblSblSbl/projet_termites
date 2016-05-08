#include <stdlib.h>
#include <string>
#include <iostream>

#include "s91k2048_outils_terminal.h"
#include "projet_termites_common.h"

using namespace std;

void quitterApplication() {
    cout << endl << endl;
    definirModeTerminal(false); // on redonne le contrôle du terminal à l'utilisateur (voir definirModeTerminal(true) dans main() dans projet_termites.cpp pour plus d'explications)
    exit(0);
}

void WTF(string str) {
    cout << "\x1B[41m \x1B[1mWTF : \x1B[2m" << str << " \x1B[0m";
}

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
bool egalCoord(Coord coord1, Coord coord2) {
    return coord1.x == coord2.x && coord1.y == coord2.y;
}
bool estValideCoord(Coord coord) {
    return coord.x >= 0 && coord.y >= 0
            && coord.x < TAILLE && coord.y < TAILLE;
}
void copierCoordDans(Coord &dest, Coord src) {
    dest.x = src.x;
    dest.y = src.y;
}
