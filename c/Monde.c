#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Monde.h"

int init_monde(Monde* monde, Regle regle, ListeImg liste) {
    /* Retourne le monde initialisé en suivant les regles `regle`
     * Renvoie 0 si une erreur d'allocation survient et 1 sinon */
    int i;
    
    assert(monde != NULL);
    
    monde->regle = regle;
    monde->largeur = regle.nb_colonnes;
    monde->hauteur = regle.nb_lignes;
    monde->nb_pomme_manger = 0;
    monde->temps = 0;
    monde->images = liste;
    
    /* Le(s) serpent(s) */
    if ((monde->serpent = (Serpent*) malloc(sizeof(Serpent))) == NULL) 
        return 0;
    if (regle.mode != SOLO && (monde->versus = (Serpent*) malloc(sizeof(Serpent))) == NULL) 
        return 0;
    
    if (0 == init_serpent(monde->serpent, monde->regle.taille_serpent, regle.nb_colonnes/2, regle.nb_lignes/2, MLV_COLOR_FORESTGREEN, MLV_COLOR_DARKGREEN))
        return 0;
    if (regle.mode != SOLO && 0 == init_serpent(monde->versus, monde->regle.taille_serpent, regle.nb_colonnes/4, regle.nb_lignes/2, MLV_COLOR_BLUE3, MLV_COLOR_BLUE4))
        return 0;
    
    /* Pommes */
    if ((monde->pomme = (Pomme*)malloc(sizeof(Pomme) * monde->regle.nombre_pomme)) == NULL)
        return 0;
    for (i=0; i<regle.nombre_pomme; i+=1)
        ajouter_pomme_monde(monde, i);
    if (regle.bonus == 1) {
        monde->pomme[0].gain = -1;
        monde->pomme[0].image = liste.pomme_3;
    }
    
    return 1;
}

int est_libre_serpent(Monde monde, int x, int y) {
    /* Test si la case (x,y) n'est pas occupée par un serpent 
     * Renvoie 1 si elle est libre et 0 si elle est occupée */
    Corps corps;
    for (corps = monde.serpent->corps; corps != NULL; corps = corps->suivant) {
        if (corps->position.x == x && corps->position.y == y)
            return 0;
    }
    if (monde.regle.mode == SOLO)
        return 1;
    
    for (corps = monde.versus->corps; corps != NULL; corps = corps->suivant) {
        if (corps->position.x == x && corps->position.y == y)
            return 0;
    }
    return 1;
}

int est_libre_pomme(Pomme pomme[], int x, int y, int taille) {
    /* Test si la case (x,y) n'est pas occupée par une pomme 
     * Renvoie 1 si elle est libre et 0 si elle est occupée */
    int i;
    
    for (i=0; i<taille; i+=1) {
        if (pomme[i].pos.x == x && pomme[i].pos.y == y)
            return 0;
    }
    return 1;
}

int est_libre(Monde monde, Case c) {
    /* Teste si la case `c` est libre 
     * Renvoie 1 si elle est libre et 0 si elle est occupée */
    return (est_libre_pomme(monde.pomme, c.x, c.y, monde.regle.nombre_pomme) && est_libre_serpent(monde, c.x, c.y));
}

void ajouter_pomme_monde(Monde *monde, int indice) {
    /* Ajoute une pomme au monde `monde` a la position `indice` du tableau
     * monde->pomme */
    Pomme pomme;
    
    assert(monde != NULL);
    
    do {
        pomme = pomme_gen_aleatoire(monde->hauteur, monde->largeur, &(monde->images), monde->regle.bonus);
    } while (!est_libre(*monde, pomme.pos));
    
    monde->pomme[indice] = pomme;
}

int deplacer_serpent(Monde *monde, Serpent* serpent) {
    /* Deplace le serpent */
    /* UNIQUEMENT SI LA CASE EST LIBRE */
    /* Retourne 0 si il ne peut pas avancer, -1 si l'allocation rate
     * et 1 si le serpent se déplace */
    Case c;
    
    assert(monde != NULL);
    assert(serpent != NULL);
    
    c = serpent->corps->position;
    
    switch (serpent->direction) {
        case NORD:
            c.y -= 1;
            if (c.y < 0 || !est_libre(*monde, c))
                return 0;
            if (insert_tete(&(serpent->corps), c, serpent->corps->interieur, serpent->corps->contour) == 0)
                return -1;
            suppr_derniere(&(serpent->corps));
            break;
        case EST:
            c.x += 1;
            if (c.x >= monde->largeur || !est_libre(*monde, c))
                return 0;
            if (insert_tete(&(serpent->corps), c, serpent->corps->interieur, serpent->corps->contour) == 0)
                return -1;
            suppr_derniere(&(serpent->corps));
            break;
        case SUD:
            c.y += 1;
            if (c.y >= monde->hauteur || !est_libre(*monde, c))
                return 0;
            if (insert_tete(&(serpent->corps), c, serpent->corps->interieur, serpent->corps->contour) == 0)
                return -1;
            suppr_derniere(&(serpent->corps));
            break;
        case OUEST:
            c.x -= 1;
            if (c.x < 0 || !est_libre(*monde, c))
                return 0;
            if (insert_tete(&(serpent->corps), c, serpent->corps->interieur, serpent->corps->contour) == 0)
                return -1;
            suppr_derniere(&(serpent->corps));
            break;
    }
    return 1;
}

int manger_pomme_serpent(Monde *monde, Serpent* serpent) {
    /* Deplace le serpent et lui fait manger la pomme  */
    /* UNIQUEMENT SI IL Y A UNE POMME SUR SA DIRECTION */
    /* Retourne 0 si il ne peut pas avancer ou qu'il mange la pomme empoisonnée,
     * -1 si l'allocation rate et 1 si le serpent mange une pomme */
    Case c;
    int i,j;
    
    assert(monde != NULL);
    assert(serpent != NULL);
    
    c = serpent->corps->position;
    
    switch (serpent->direction) {
        case NORD:
            c.y -= 1;
            if (est_libre_pomme(monde->pomme, c.x, c.y, monde->regle.nombre_pomme))
                return 0;
            if (insert_tete(&(serpent->corps), c, serpent->corps->interieur, serpent->corps->contour) == 0)
                return -1;
            suppr_derniere(&(serpent->corps));
            break;
        case EST:
            c.x += 1;
            if (est_libre_pomme(monde->pomme, c.x, c.y, monde->regle.nombre_pomme))
                return 0;
            if (insert_tete(&(serpent->corps), c, serpent->corps->interieur, serpent->corps->contour) == 0)
                return -1;
            suppr_derniere(&(serpent->corps));
            break;
        case SUD:
            c.y += 1;
            if (est_libre_pomme(monde->pomme, c.x, c.y, monde->regle.nombre_pomme))
                return 0;
            if (insert_tete(&(serpent->corps), c, serpent->corps->interieur, serpent->corps->contour) == 0)
                return -1;
            suppr_derniere(&(serpent->corps));
            break;
        case OUEST:
            c.x -= 1;
            if (est_libre_pomme(monde->pomme, c.x, c.y, monde->regle.nombre_pomme))
                return 0;
            if (insert_tete(&(serpent->corps), c, serpent->corps->interieur, serpent->corps->contour) == 0)
                return -1;
            suppr_derniere(&(serpent->corps));
            break;
    }
    /* Manger une pomme */
    for (i=0; i<monde->regle.nombre_pomme; i+=1) {
        if (serpent->corps->position.x == monde->pomme[i].pos.x &&
                    serpent->corps->position.y == monde->pomme[i].pos.y) {
            if (monde->pomme[i].gain == -1)
                return 0;
            /* Augmenter taille serpent */
            serpent->taille += monde->pomme[i].gain;
            monde->nb_pomme_manger += monde->pomme[i].gain;
            
            for (j=0; j<monde->pomme[i].gain; j+=1) {
                if (insert_tete(&(serpent->corps), c, serpent->corps->interieur, serpent->corps->contour) == 0)
                    return -1;
            }
            /* Ajouter une pomme a l'indice i */
            ajouter_pomme_monde(monde, i);
            /* Fin de programme */
            return 1;
        }
    }
    /* Si atteint là => incohérence */
    printf("Incohérence!\n");
    return 0;
}

int mort_serpent(Monde *monde, Serpent *serpent) {
    /* Test si le serpent VA etre dans une situation perdante */
    /* Retourne 1 le serpent va mourir 0 s'il va vivre */
    Case c;
    
    assert(monde != NULL);
    assert(serpent != NULL);
    
    c = serpent->corps->position;
    switch (serpent->direction) {
        case NORD:
            if (c.y - 1 < 0 || !est_libre_serpent(*(monde), c.x, c.y - 1))
                return 1;
            break;
        case EST:
            if (c.x + 1 >= monde->largeur || !est_libre_serpent(*(monde), c.x + 1, c.y))
                return 1;
            break;
        case SUD:
            if (c.y + 1 >= monde->hauteur || !est_libre_serpent(*(monde), c.x, c.y + 1))
                return 1;
            break;
        case OUEST:
            if (c.x - 1 < 0 || !est_libre_serpent(*(monde), c.x - 1, c.y))
                return 1;
            break;
    }
    return 0;
}

int deplacement_complet(Monde* monde, Serpent* serpent, int* frame_rate, MLV_Sound *sfx) {
    /* Deplace le serpent et incrémente `frame_rate` s'il mange une pomme.
     * Renvoie -1 si erreur lors de l'allocation, 0 si il mange une pomme empoisonnée ou
     * 1 si il se déplace normalement. */
    int code_err;
    
    assert(monde != NULL);
    assert(serpent != NULL);
    
    code_err = deplacer_serpent(monde, serpent);
    if (code_err == -1) /* Allocation fail */
        return -1;
    else if (code_err == 0) {
        /* Son de mangeage */
        if (sfx != NULL && monde->regle.sound == 1)
            MLV_play_sound(sfx, 1.0);
        code_err = manger_pomme_serpent(monde, serpent);
        if (code_err == -1) /* Allocation fail */
            return -1;
        if (code_err == 0) /* Atteint si pomme empoisonnée */
            return 0;
        if (frame_rate != NULL && *frame_rate > 25)
            *frame_rate -= 5;
    }
    return 1;
}
