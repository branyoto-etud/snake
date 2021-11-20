#include "Regles.h"

Regle init_regle() {
    /* Initialise les regles
     * Renvoie les regles initialisées */
    Regle regle;
    
    regle.nb_colonnes = 64;     /*64*/
    regle.nb_lignes = 32;       /*32*/
    regle.taille_case = 20;     /*20*/
    regle.taille_serpent = 4;   /*4*/
    regle.nombre_pomme = 3;     /*3*/
    regle.mode = SOLO;          /*SOLO=0*/
    regle.sound = 1;            /*1*/
    regle.bonus = 1;            /*1*/
    
    return regle;
}
