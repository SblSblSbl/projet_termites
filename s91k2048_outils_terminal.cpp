#ifndef OUTILS_TERMINAL_CPP
#define OUTILS_TERMINAL_CPP 1

#include "s91k2048_outils_terminal.h"
using namespace std;

bool definirModeTerminal(int not_canon) {
    // active / désactive le mode non canonique
    int fileno_stdin = fileno(stdin);
    struct termios ttystate;
    int is_tty = tcgetattr(fileno_stdin, &ttystate) == 0;
    //  ~ICANON : pas de saut de ligne obligatoire (1)
    //    ~ECHO : pas d'affichage des caractères
    int params = (ICANON | ECHO);
    if (not_canon) {
        if (is_tty) {
            ttystate.c_lflag &= ~params;
            ttystate.c_cc[VMIN] = 1;
            tcsetattr(fileno_stdin, TCSANOW, &ttystate);
        }
        // O_NONBLOCK : pas de saut de ligne obligatoire (1)
        fcntl(fileno_stdin, F_SETFL, fcntl(fileno_stdin, F_GETFL) | O_NONBLOCK);
    } else {
        if (is_tty) {
            ttystate.c_lflag |= params;
            ttystate.c_cc[VMIN] = 0;
            tcsetattr(fileno_stdin, TCSANOW, &ttystate);
        }
        fcntl(fileno_stdin, F_SETFL, fcntl(fileno_stdin, F_GETFL) & ~O_NONBLOCK);
    }
    return true;
}

bool getTermSize(int* x, int* y) {
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) < 0) {
        return false;
    }
    *x = w.ws_col;
    *y = w.ws_row;
    return true;
}



#endif // OUTILS_TERMINAL_CPP
