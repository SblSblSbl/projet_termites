#ifndef S91K2048_OUTILS_TERMINAL_H
#define S91K2048_OUTILS_TERMINAL_H

#include "s91k2048_const.h"

/**
 * Définit le mode du terminal du client local comme
 *  canonique ou non canonique
 * @param not_canon true pour que le mode soit non
 *        canonique (sinon il est canonique)
 * @return true si l'action s'est terminée avec succès
 */
bool definirModeTerminal(int not_canon);

/**
 * Obtient la longueur et la largeur de la fenetre du terminal local
 * @param x pointeur vers le nombre entier représentant la longueur
          de la fenetre de terminal
 * @param y pointeur vers le nombre entier représentant la largeur
          de la fenetre de terminal
 * @return true si l'action s'est terminée avec succès
 */
bool getTermSize(int* x, int* y);

#endif // S91K2048_OUTILS_TERMINAL_H
