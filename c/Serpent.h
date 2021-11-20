#include "Case.h"
#include <MLV/MLV_all.h>

#ifndef __SERPENT__

#define __SERPENT__
typedef enum {
    NORD,
    EST,
    SUD,
    OUEST
} Direction;

typedef struct cell {
    Case position;
    MLV_Color interieur;
    MLV_Color contour;
    struct cell* suivant;
} Cellule, *Corps;

typedef struct {
    int taille;
    Direction direction;
    Corps corps;
} Serpent;


int insert_tete(Corps *corps, Case c, MLV_Color inte, MLV_Color contour);
void suppr_derniere(Corps *corps);
int init_serpent(Serpent *serpent, int taille, int x, int y, MLV_Color inte, MLV_Color contour);
Cellule* alloue_corps(Case c, MLV_Color inte, MLV_Color contour);

#endif
