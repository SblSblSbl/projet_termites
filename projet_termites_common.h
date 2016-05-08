#ifndef PROJET_TERMITES_COMMON_H
#define PROJET_TERMITES_COMMON_H

#include <string>

const int TAILLE = 40;
const double POURCENTAGE_TERMITES = 1.;
const double POURCENTAGE_BRINDILLES = 5.;


enum {
    PLACE_TYPE_VIDE,
    PLACE_TYPE_BRINDILLE,
    PLACE_TYPE_TERMITE,
} type_place;
enum {
    DIRECTION_HAUT,
    DIRECTION_DROITE_HAUT,
    DIRECTION_DROITE,
    DIRECTION_DROITE_BAS,
    DIRECTION_BAS,
    DIRECTION_GAUCHE_BAS,
    DIRECTION_GAUCHE,
    DIRECTION_GAUCHE_HAUT,
    NB_DIRECTIONS
} directions;
enum {
	SENS_ROTATION_GAUCHE,
	SENS_ROTATION_DROITE
} sens_rotation_enum;

struct Coord {
    int x;
    int y;
};

/**
 * Quitte l'application tout en redonnant le contrôle de la fenêtre de terminal
 * à l'utilisateur
 */
void quitterApplication();

/**
 * Affihe une erreur qui ne devrait pas arriver
 * @param str chaîne de caractères représentant l'erreur à afficher
 */
void WTF(std::string str);

/**
 * Renvoie true avec une probabilité donnée
 * @param p probabilité de renvoyer true
 * @return true avec une probabilité de p, false sinon
 */
bool aleatoire(double p);

/**
 * Renvoie une direction aléatoire
 * @return la direction aléatoire
 */
int directionAleatoire();

/**
 * Renvoie un sens de rotation aléatoire
 * @return le sens de rotation aléatoire
 */
int sensRotationAleatoire();

/**
 * Crée des coordonnées
 * @param x abscisse
 * @param y ordonnée
 * @return les coordonnées {x, y}
 */
Coord creerCoord(int i, int j);

/**
 * Vérifie si des coordonnées sont égales
 * @param coord1 coordonnées
 * @param coord2 coordonnées
 * @return true si coord1.x == coord2.x et coord1.y == coord2.y
 */
bool egalCoord(Coord coord1, Coord coord2);

/**
 * Vérifie si des coordonnées sont valides, càd si elles sont contenues dans les
 * bornes du terrain (0 <= coord.x < TAILLE et 0 <= coord.y < TAILLE)
 * @param coord coordonnées cibles
 * @return true si les coordonnées coord sont contenues dans le terrain
 */
bool estValideCoord(Coord coord);

/**
 * Copie des coordonnées d'une source (src) vers une destination (dest)
 * @param &dest référence vers les coordonnées destination
 * @param src les coordonnées source
 */
void copierCoordDans(Coord &dest, Coord src);

#endif // PROJET_TERMITES_COMMON_H