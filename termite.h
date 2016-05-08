#ifndef TERMITE_H
#define TERMITE_H

#include "projet_termites_common.h"

struct Termite {
    Coord coord;
    Coord ancien_coord;
    int direction;
    int sens_rotation;
    int sablier;
    bool tourner_sur_place;
    bool vient_de_se_retourner;
    bool brindille;
    int indice;
};

/**
 * Crée un termite
 * @param x abscisse du termite dans son terrain
 * @param y ordonnée du termite dans son terrain
 * @return le termite avec l'indice indice et les coordonnées {x, y} dans son
 *         terrain
 */
Termite creerTermite(int indice, int x, int y);

/** 
 * Vérifie si une termite porte une brindille
 * @param m termite cible
 * @return true si m porte une brindille
 */
bool porteBrindilleTermite(Termite m);

/**
 * Renvoie les coordonnées de l'éventuelle place située devant un termite,
 * sans vérifier si elles sont contenues dans les bornes du terrain
 * Si la direction du termite est invalide, renvoie {-1, -1}
 * @param m termite cible
 * @return les coordonnées de l'éventuelle place située devant m
 */
Coord coordDevantTermite(Termite m);

/** 
 * Fait tourner un termite à gauche
 * @param &m réference vers le termite cible
 */
void tourneGaucheTermite(Termite &m);

/**
 * Fait tourner un termite à droite
 * @param &t réference vers le termite cible
 */
void tourneDroiteTermite(Termite &m);

/**
 * Fait tourner un termite dans sa direction par défaut
 * @param &m réference vers le termite cible
 */
void tourneTermite(Termite &m);

/**
 * Définit le sens de rotation d'un termite
 * @param &m réference vers le termite cible
 * @param sens nouveau sens de rotation de &m
 */
void definirSensRotationTermite(Termite &m, int sens);

/**
 * Fait charger une brindille à un termite (ne modifie pas le terrain)
 * @param &m réference vers le termite cible
 */
void chargerBrindilleTermite(Termite &m);

/**
 * Fait décharger une brindille à un termite (ne modifie pas le terrain)
 * @param &m réference vers le termite cible
 */
void dechargerBrindilleTermite(Termite &m);

/**
 * Téléporte un termite vers une place (sans modifier le terrain)
 * @param &m réference vers le termite cible
 * @param coordonnées de la place vers laquelle m sera téléporté
 */
void teleporterTermite(Termite &m, Coord coord);

/** 
 * Retourne progressivement un termite (càd pendant un certain nombre de
 * tours/frames/whatever)
 * Par exemple, si on veut retourner progressivement le termite de 180°, on doit
 * appeler cette fonction de la façon suivante :
 *  retourneProgressivementTermite(mon_termite, NB_DIRECTIONS/2);
 * @param &m réference vers le termite cible
 * @param nb_tours nombre de tours pendant lesquels le termite doit tourner
 */
void retourneProgressivementTermite(Termite &m, int nb_tours);

/** 
 * Vérifie si le sablier d'un termite est actif, càd 
 * @param m termite cible
 */
bool estSablierActifTermite(Termite m);

/** 
 * Décrémente le sablier d'un termite si possible
 * @param &m réference vers le termite cible
 */
void decrementerSablierTermite(Termite &m);

/** 
 * Vérifie si un termite doit tourner sur place au lieu d'agir avec les places
 * du terrain
 * @param m termite cible
 */
bool doitTournerSurPlaceTermite(Termite m);

/** 
 * Définit le mode "tourner sur place" d'un termite
 *
 * @see doitTournerSurPlaceTermite(Termite m)
 *
 * @param &m réference vers le termite cible
 * @param actif true si le mode "tourner sur place" de m doit être activé
 */
void definirModeTournerSurPlaceTermite(Termite &m, bool actif);

/** 
 * Vérifie si un termite ne peut pas agir avec les brindilles du terrain
 * C'est le cas lorsque le termite vient de se retourner
 * @param &m réference vers le termite cible
 */
bool actionsAvecBrindillesBloqueesTermite(Termite m);

/** 
 * Débloque les actions d'un termite avec les brindilles du terrain
 * /!\ Appeler cette fonction à la fin de rassemblerBrindilles() pour que le termite
 * puisse agir avec les brindilles (i.e. la prise des brindilles / le marquage du mode
 * "tourner sur place")
 * @param &m réference vers le termite cible
 */
void debloquerActionsAvecBrindillesSiNecessaireTermite(Termite &m);


/**
 * Affiche dans la fenêtre de terminal une chaîne de caractères correspondant
 * aux paramètres d'un termite
 *
 * Symbole : 
 *  |, /, - ou \ selon la directions du termite
 * 
 * Couleurs
 * - vert   : ne porte pas de brindille
 * - orange : porte une brindille
 *
 * @param m termite cible
 */
void afficheTermite(Termite m);


#endif // TERMITES_H_INCLUDED