#ifndef S91K2048_OUTILS_TERMINAL_MOD_TERMITES_H
#define S91K2048_OUTILS_TERMINAL_MOD_TERMITES_H

#define EFFACER_ECRAN "\x1B[2J"
#define CURSEUR_DEBUT "\x1B[1;1H"
#define EFFACER_TERMINAL EFFACER_ECRAN CURSEUR_DEBUT

#define CC_RESET "\x1B[0m"
#define CC_POLICE_NORMAL "\x1B[2m"
#define CC_POLICE_GRAS "\x1B[1m"

#define CC_TEXTE_VERT "\x1B[32m"
#define CC_TEXTE_ORANGE "\x1B[33m"
#define CC_TEXTE_BLEU "\x1B[34m"
#define CC_TEXTE_BLANC "\x1B[37m"

#define CC_FOND_VERT "\x1B[42m"
#define CC_FOND_ORANGE "\x1B[43m"
#define CC_FOND_BLEU "\x1B[44m"
#define CC_FOND_BLANC "\x1B[47m"


/**
 * Définit le mode du terminal du client local comme anonique ou non canonique
 * Le mode non canonique permet par ex d'utiliser getch() sans bloquer le
 * terminal
 * @param not_canon true pour que le mode soit non canonique (sinon il est
 *        canonique)
 * @return true si l'action s'est terminée avec succès
 */
bool definirModeTerminal(int not_canon);

#endif // S91K2048_OUTILS_TERMINAL_MOD_TERMITES_H
