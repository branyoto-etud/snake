#include <MLV/MLV_all.h>

#ifndef __IMAGE__
#define __IMAGE__

typedef struct {
    MLV_Image *pomme_1;
    MLV_Image *pomme_2;
    MLV_Image *pomme_3;
    MLV_Image *pomme_g;
} ListeImg;

int init_image(ListeImg* liste, int taille_case);
void resize_all_image(ListeImg* liste, int taille_case);

#endif
