#include "Case.h"

Case init_case(int x, int y) {
    /* Prend en argument des coordonnées (x,y) et initialise
     * une case avec ces coordonnées.
     * Retourne la cellule initialisée. */
    Case c;
    c.x = x;
    c.y = y;
    return c;
}


