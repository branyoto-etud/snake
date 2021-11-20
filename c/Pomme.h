#include "Case.h"
#include "Image.h"
#include <MLV/MLV_all.h>

#ifndef __POMME__
#define __POMME__
#define NB_POMME 3

typedef struct {
    Case pos;
    int gain;           /* nombre de case que la pomme donne. -1 pour la pomme empoisonnée */
    MLV_Image *image;
} Pomme;

Pomme pomme_gen_aleatoire(int n, int m, ListeImg* liste, int bonus);

#endif
