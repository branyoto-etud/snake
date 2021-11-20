#ifndef __MONDE__
#define __MONDE__

#include "Pomme.h" 
#include "Serpent.h"
#include "Regles.h"
#include "Image.h"

typedef struct {
    int largeur, hauteur;
    int nb_pomme_manger;
    int temps;
    Serpent *serpent;
    Serpent *versus;
    Pomme *pomme;
    Regle regle;
    ListeImg images;
} Monde;

int init_monde(Monde *monde, Regle regle, ListeImg liste);

void ajouter_pomme_monde(Monde *monde, int indice);

int est_libre_serpent(Monde monde, int x, int y);
int est_libre_pomme(Pomme pomme[], int x, int y, int taille);
int est_libre(Monde monde, Case c);

int deplacer_serpent(Monde *monde, Serpent* serpent);
int manger_pomme_serpent(Monde *monde, Serpent* serpent);
int mort_serpent(Monde *monde, Serpent* serpent);
int deplacement_complet(Monde* monde, Serpent* serpent, int* frame_rate, MLV_Sound *sfx);

#endif
