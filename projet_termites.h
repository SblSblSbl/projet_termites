#ifndef PROJET_TERMITES_H
#define PROJET_TERMITES_H

#include "projet_termites_common.h"
#include "termite.h"

struct Place {
    int type;
    int indtermite;
};
struct Terrain {
    Place places[TAILLE][TAILLE];
    Termite termites[TAILLE*TAILLE];
    int nbtermites;
};

/**
 * Initialise une place vide
 * @param &p référence vers la place cible
 */
void placeVide(Place &p);

/**
 * Renvoie le type d'une place
 * @param p place cible
 * @return le type de p
 */
int typePlace(Place p);

/**
 * Modifie le type d'une place
 * @param &p référence vers la place cible
 * @param type nouveau type de p
 */
void changerTypePlace(Place &p, int type);

/**
 * Echange les types et les paramètres de deux places (i.e. les indices
 * des éventuels termites qu'elles contiennent)
 * @param &p1 référence vers la première place, qui sera échangée avec p2
 * @param &p2 référence vers la deuxième place, qui sera échangée avec p1
 */
void echangerPlaces(Place &p1, Place &p2);

/**
 * Vérifie si une place contient une termite
 * @param p place cible
 * @return true si p contient une termite, false sinon
 */
bool contientTermite(Place p);

/**
 * Vérifie si une place contient une brindille
 * @param p place cible
 * @return true si p contient une brindille, false sinon
 */
bool contientBrindille(Place p);

/**
 * Renvoie une référence vers une place à laquelle correspondent un terrain et
 * des coordonnées
 * @param &t référence vers le terrain cible
 * @param t référence vers les coordonnées qui définissent la place à renvoyer
 * @return une référence vers la place définie par &t et coord
 */
Place& coord2Place(Terrain &t, Coord coord);

/**
 * Initialise un terrain en lui attribuant ses valeurs de début
 * @param &t référence vers le terrain cible
 */
void initialiseTerrain(Terrain &t);

/**
 * Affiche le contenu d'un terrain dans la fenêtre de terminal
 * @param t terrain cible
 */
void afficheTerrain(Terrain t);

/**
 * Fait charger une brindille d'une place à un termite
 * @param &m réference vers le termite cible
 * @param &p référence vers la place cible
 * @param coord coordonnées de la place cible dans le terrain courant
 */
void chargerBrindilleTermitePlace(Termite &m, Place &p, Coord coord);

/**
 * Fait décharger une brindille sur une place à un termite
 * @param &m réference vers le termite cible
 * @param &p référence vers la place cible
 * @param coord coordonnées de la place cible dans le terrain courant
 */
void dechargerBrindilleTermitePlace(Termite &m, Place &p, Coord coord);

/**
 * Déplace un termite à une place d'un terrain définie par ses coordonnées
 * @param &t référence vers le terrain cible
 * @param &m référence vers le termite cible à déplacer
 * @param coord coordonnées de la place vers laquelle m doit se déplacer
 */
void deplaceTermiteDansTerrain(Terrain &t, Termite &m, Coord coord);

/**
 * Fait agir un termite avec une place d'un terrain selon le type de celle-ci
 * @param &p référence vers le terrain cible
 * @param &t référence vers le termite cible qui doit agir avec la place
 * @param coord coordonnées de la place cible
 */
void actionPlaceTermite(Terrain &t, Termite &m, Coord coord);

/**
 * Fait agir un termite (représente un tour/frame/whatever)
 * @param &t référence vers le terrain cible
 * @param &m référence vers le termite cible
 */
void rassemblerBrindilles(Terrain &t, Termite &m);

/**
 * Fait agir tous les termites d'un terrain (représente un tour/frame/whatever)
 * @param &t référence vers le terrain cible
 */
void mouvementTermites(Terrain &t);

#endif // PROJET_TERMITES_H