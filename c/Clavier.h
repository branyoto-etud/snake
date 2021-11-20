#include <MLV/MLV_all.h>
#include "Monde.h"

#ifndef __CLAVIER__

#define __CLAVIER__


typedef enum {
    NONE = -100,
    KEY_UP = 0,
    KEY_RIGHT = 1,
    KEY_DOWN = 2,
    KEY_LEFT = 3,
    KEY_Z = 4,
    KEY_D = 5,
    KEY_S = 6,
    KEY_Q = 7,
    /* Je laisse de la place pour si on ajoute d'autres joueurs */
    KEY_P = 20,
    KEY_RETURN = 21
} Touche;

int get_touche_pressed();
void gerer_action(Monde* monde, int* pause, MLV_Sound *sfx);

#endif
