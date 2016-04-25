#ifndef TERMITES_H_INCLUDED
#define TERMITES_H_INCLUDED

const int TAILLE = 40;
const double POURCENTAGE_TERMITES = 1.;
const double POURCENTAGE_BRINDILLES = 5.;


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
    Place places[TAILLE][TAILLE];
    Termite termites[TAILLE*TAILLE];
    int nbtermites;
};

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
 * @return la direction
 */
int directionAleatoire();

/**
 * Crée des coordonnées
 * @param x abscisse
 * @param y ordonnée
 * @return les coordonnées {x, y}
 */
Coord creerCoord(int i, int j);

/**
 * Crée une termite
 * @param x abscisse de la termite dans son terrain
 * @param y ordonnée de la termite dans son terrain
 * @return la termite avec l'indice indice et les coordonnées {x, y} dans son
 *         terrain
 */
Termite creerTermite(int indice, int x, int y);

/**
 * Initialise une place vide
 * @param &p référence vers la place cible
 */
void placeVide(Place &p);

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
 * Renvoie les coordonnées de l'éventuelle place située devant une termite,
 * sans vérifier si elles sont contenues dans les bornes du terrain
 * Si la direction de la termite est invalide, renvoie {-1, -1}
 * @param m termite cible
 * @return les coordonnées de l'éventuelle place située devant m
 */
Coord coordDevant(Termite m);

/** 
 * Fait tourner un termite à gauche
 * @param &t réference vers le termite cible
 */
void tourneGauche(Termite &t);

/**
 * Fait tourner un termite à droite
 * @param &t réference vers le terrain cible
 */
void tourneDroite(Termite &t);

/**
 * Initialise un terrain en lui attribuant ses valeurs de début
 * @param &t référence vers le terrain cible
 */
void initialiseTerrain(Terrain &t);

/**
 * Affiche dans la fenêtre de terminal un symbole correspondant aux paramètres
 * d'une termite
 * @param m termite cible
 */
void afficheTermite(Termite m);

/**
 * Affiche le contenu d'un terrain dans la fenêtre de terminal
 * @param t terrain cible
 */
void afficheTerrain(Terrain t);

#endif // TERMITES_H_INCLUDED