#ifndef __REGLES__

#define __REGLES__

typedef enum {
    SOLO,
    VERSUS
} Mode;

typedef struct {
    int nb_colonnes, nb_lignes; /* Nombre de lignes/colonnes du plateau */
    int taille_case;    /* Taille des cases */
    int taille_serpent; /* Taille initiale du serpent */
    int nombre_pomme;   /* Nombre de pomme sur le terrain */
    Mode mode;   /* Mode de jeu choisi */
    int sound;  /* 1 si les sons sont activés 0 sinon */
    int bonus;  /* 1 si les bonus sont activés 0 sinon */
} Regle;

Regle init_regle();

#endif

