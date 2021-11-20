#include "Pomme.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

Pomme pomme_gen_aleatoire(int n, int m, ListeImg *liste, int bonus) {
    /* Genere une pomme avec une position aléatoire entre `n`et `m`
     * et ayant pour représentation une image de `liste`.
     * Le gain a une chance d'être plus élevé si bonus vaut 1.
     * Renvoie la pomme initialisée. */
    Pomme pomme;
    
    assert(liste != NULL);
    
    pomme.pos.x = rand() % m;
    pomme.pos.y = rand() % n;
    pomme.gain = 1;
    
    /* random entre 0 et 4 si bonus == 1 */
    /* random entre 1 et 5 si bonus == 0 */
    switch (rand() % 5 + !bonus) {
        case 0:
            pomme.gain = 4;
            pomme.image = liste->pomme_g;
            break;
        case 1:
        case 2:
            pomme.image = liste->pomme_1;
            break;
        case 3:
        case 4:
        case 5:
            pomme.image = liste->pomme_2;
            break;
    }
    return pomme;
}

