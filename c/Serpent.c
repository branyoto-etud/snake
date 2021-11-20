#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>

#include "Serpent.h"

Cellule* alloue_cellule(Case c, MLV_Color inte, MLV_Color contour) {
    /* Créé une cellule ayant pour position la position de
     * la case `c` et pour couleur `inte` pour l'interieur et `contour`
     * pour l'exterieur.
     * Renvoie NULL si elle n'a pas pu etre alloué et elle sinon */
    Cellule* corps;
    
    if ((corps = (Cellule*)malloc(sizeof(Cellule))) == NULL)
        return NULL;
    
    corps->suivant = NULL;
    corps->position = c;
    corps->interieur = inte;
    corps->contour = contour;
    
    return corps;
}


int insert_tete(Corps *corps, Case c, MLV_Color inte, MLV_Color contour) {
    /* Prend en argument un corps, une case, et deux couleurs
     * Insert la case au debut du corps.
     * Retourne 0 si l'allocation s'est mal passée et 1 sinon */
    Corps tmp = alloue_cellule(c, inte, contour);
    
    if (tmp == NULL)
        return 0;
    tmp->suivant = *corps;
    *corps = tmp;
    
    return 1;
}

void suppr_derniere(Corps *corps) {
    /* Prend en argument un corps dont on retire sa dernière cellule */
    if (*corps == NULL)
        return;
    
    if ((*corps)->suivant == NULL)
        *corps = NULL;
    else
        suppr_derniere(&((*corps)->suivant));
}

int init_serpent(Serpent* serpent, int taille, int x, int y, MLV_Color inte, MLV_Color contour) {
    /* Prend en argument un serpent, sa taille, sa position (x,y) et ses couleurs.
     * Renvoie 0 si l'allocation s'est mal passée et 1 sinon */
    int i;
    Case c;
    
    assert(serpent != NULL);
    
    c.x = x;
    c.y = y;
    serpent->taille = taille;
    serpent->direction = NORD;
    
    /* Allocation du corps */
    serpent->corps = NULL;
    for (i=0; i<taille; i+=1) {
        if (insert_tete(&(serpent->corps), c, inte, contour) == 0)
            return 0;
    }
    return 1;
}
