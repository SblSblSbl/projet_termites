#ifndef S91K2048_CONST_H
#define S91K2048_CONST_H

#ifdef QT_CORE_LIB
#define EXT_MODE 1
#define UI_WARN 1
#define ON_SCORE_UPDATE 1
#define ON_LEADERBOARD_UPDATE 1
#define ON_CLIENTS_LIST_UPDATE 1
#define ON_GAME_WON 1
#define ON_GAME_LOST 1
#define UI_LOAD_PREFS 1
#define UI_SAVE_PREFS 1
#endif

#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <errno.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <ctype.h>
#include <signal.h>
// linux seulement (sockets)
#include <fcntl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */

#define GAME_TITLE "s91k's CONST"
#define GAME_VERSION "0.04a_PROJET_dev"
#define SAVE_DIR "./save_s91k"
#define GRILLE_SAVE_FICHIER "save.dat"

#define TAILLE_X 4
#define TAILLE_Y 4

#define CELLULE_TYPE_VIDE 0

#define NB_CASES_SPAWN_DEBUT 2
#define MULTIPLICATEUR_CASE 2
#define CELLULE_VALEUR_GAGNANTE 2048

#define SAVE_GAME_INTERVAL 3000

#define POSITIONNEMENT_ABSOLU 1

#define CELL_WIDTH 7
#define CELL_HEIGHT 3
#define CELL_BORDER_WIDTH 2
#define CELL_BORDER_HEIGHT 1

#define GRID_DRAW_FIRST_WALL 1

#define MARGIN_LEFT 2
#define MARGIN_RIGHT 5
#define MARGIN_TOP 0
#define MARGIN_BOTTOM 0
#define PADDING_LEFT 0
#define PADDING_RIGHT 4
#define PADDING_TOP 1
#define PADDING_BOTTOM 1

#define MSG_MARGIN_TOP 5
#define MSG_PADDING_TOP 2
#define MSG_PADDING_BOTTOM 2
#define MSG_SCREEN_Y 8
#define MSG_SCREEN_Y_CHAT 4

#define LEADERBOARD_Y 2

#define CLIENTS_LIST_Y 10

#define LEADERBOARD_MAX_NB 10
#define LEADERBOARD_SAVE_USER_SIZE 64

#define LISTE_CONTENU_LARGEUR 32
#define LISTE_LARGEUR 36

#define SUBWD_PADDING_LEFT 0
#define SUBWD_PADDING_RIGHT 0
#define SUBWD_PADDING_TOP 1
#define SUBWD_PADDING_BOTTOM 1

#define RT_PADDING_LEFT 3

#define FULL_SCREEN_TITLE 1

#define GRID_X TAILLE_X * (CELL_WIDTH + CELL_BORDER_WIDTH) + CELL_BORDER_WIDTH
#define GRID_Y TAILLE_Y * (CELL_HEIGHT + CELL_BORDER_HEIGHT) + CELL_BORDER_HEIGHT

#define SCREEN_X PADDING_LEFT + GRID_X + PADDING_RIGHT
#define SCREEN_Y PADDING_TOP + GRID_Y + PADDING_BOTTOM + MARGIN_BOTTOM

#define WIN_SIZE SCREEN_X * SCREEN_Y

#define FULL_SCREEN_X 79
#define FULL_SCREEN_Y 24

#define CC_POLICE_NORMAL "\x1B[2m"
#define CC_POLICE_GRAS "\x1B[1m"

#define DEFAULT_COLOR "\x1B[40;37m"
#define BG_COLOR "\x1B[40;37m"
#define BG_COLOR_ME "\x1B[40;32m"
#define BG_COLOR_ME_CUR "\x1B[40;33m"
#define BG_COLOR_OTHER "\x1B[40;36m"
#define BG_COLOR_GRAYED "\x1B[40;36m"
#define TITLE_COLOR "\x1B[44;37m"
#define SELECTED_COLOR "\x1B[44;37m"
#define WALL_COLOR "\x1B[44;34m"
#define CELL_COLOR "\x1B[42;37m"
#define CELL_SELECTED_COLOR "\x1B[43;37m"
#define EMPTY_CELL_COLOR "\x1B[46;30m"

#define DEFAULT_CHAR " "
#define BG_CHAR " "
#define TITLE_CHAR " "
#define WALL_CHAR " "
#define CELL_CHAR " "
#define CELL_SELECTED_CHAR " "
#define EMPTY_CELL_CHAR " "

#define ANIM_MOVE_NB 7.0
#define ANIM_BLINK_NB 4.0
#define ANIM_MOVE_TIME 25.0
#define ANIM_BLINK_SPAWNED_TIME 50.0

#define BLINK_SPAWNED_NB 2


#define MAX_CLIENTS 50

#define SERVER_PORT 1338
#define SOCK_TIMEOUT 5000
#define TELNET_SEND_MAX_TRIES 1000

#define TYPE_CLIENT_INCONNU -1
#define TYPE_CLIENT_LOCAL 1
#define TYPE_CLIENT_TELNET 2
#define TYPE_CLIENT_ANDROID 2

#define MAX_USERSTR_SIZE 255
#define PROMPT_MAX_SIZE 9
#define PROMPT_NICK_MAX_SIZE 9

#define DEF_SRV_NAME "serveur"
#define DEFAULT_PS ""


#define CHAT_FULLSCREEN 1
#define CHAT_MAX_MSG_SIZE 256
#define CHAT_MAX_MSGS 0 // nombre de messages de chat infini, pas de suppression des anciens messages
#define CHAT_MAX_MSGS_INGAME 5
#define CHAT_MAX_MSGS_INGAME_HUD 3

#define CHAT_PADDING_TOP 0

#define CHAT_ECRIT_DEMARQUER_TM 2000


#define L10N_LEADERBOARD_TITLE "Meilleurs scores"
#define L10N_LEADERBOARD_TITLE_SHORT "Meilleurs scores"
#define L10N_CLIENTS_LIST_TITLE "Joueurs connectés"

#define BD_DEFAUT -1
#define BD_INIT 0
#define BD_JEU 1
#define BD_MSG 2
#define BD_CHAT 3
#define BD_LISTE_SCORES 4
#define BD_LISTE_CLIENTS 5

#define BD_MSG_NONE 0
#define BD_MSG_PAUSE 1
#define BD_MSG_FIN_JEU 2
#define BD_MSG_SCORES 3
#define BD_MSG_PROMPT_QUITTER 30
#define BD_MSG_PROMPT_NOUVELLE_PARTIE 31
#define BD_MSG_NORMAL 909
#define BD_MSG_WARN 910
#define BD_MSG_ERREUR 911
#define BD_PROMPT_PSEUDO 20

#define OUTPUT_CLEAR_STR "\x1B[2J"

#define CTRL_C_TAP_NB 1

#define TELNET_IGNORED_FIRST_CHARS_NB 54
#define TELNET_FIRST_CHAR_SEND_TM 1000

typedef struct {
    int x;
    int y;
} Point;

const int GAUCHE = 7;
const int DROITE = 4;
const int HAUT = 8;
const int BAS = 2;
const int ENTREE = 90;
const int CTRL_W = 91;
const int ESC = 92;
const int BACKSPACE = 93;



#ifdef EXT_MODE
extern void onRedraw();
#endif

#ifdef UI_WARN
extern void uiWarnCStr(const char* cstr);
#endif

#ifdef ON_SCORE_UPDATE
extern void onScoreUpdate();
#endif

#ifdef ON_LEADERBOARD_UPDATE
extern void onLeaderboardUpdate();
#endif

#ifdef ON_CLIENTS_LIST_UPDATE
extern void onClientsListUpdate();
#endif

#ifdef ON_GAME_WON
extern void onGameWon();
#endif

#ifdef ON_GAME_LOST
extern void onGameLost();
#endif

#ifdef UI_LOAD_PREFS
extern void uiLoadPrefs();
#endif

#ifdef UI_SAVE_PREFS
extern void uiSavePrefs();
#endif

#endif // S91K2048_CONST_H
