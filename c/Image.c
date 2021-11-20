#include <assert.h>
#include "Image.h"

int init_image(ListeImg* liste, int taille_case) {
    /* Initialise la liste des images `liste` en les redimentionnant
     * à la taille `taille_case`
     * Renvoie 1 si tous se passe bien et 0 si une erreur survient */
    
    assert(liste != NULL);
    
    if (( liste->pomme_1  = MLV_load_image("./img/apple_1.png")) == NULL)
        return 0;
    MLV_resize_image(liste->pomme_1, taille_case, taille_case);
    if (( liste->pomme_2  = MLV_load_image("./img/apple_2.png")) == NULL)
        return 0;
    MLV_resize_image(liste->pomme_2, taille_case, taille_case);
    if (( liste->pomme_3  = MLV_load_image("./img/apple_3.png")) == NULL)
        return 0;
    MLV_resize_image(liste->pomme_3, taille_case, taille_case);
    if (( liste->pomme_g  = MLV_load_image("./img/apple_g.png")) == NULL)
        return 0;
    MLV_resize_image(liste->pomme_g, taille_case, taille_case);
    
    return 1;
}

void resize_all_image(ListeImg *liste, int taille_case) {
    /* Redimentionne toutes les images de `liste` à la taille `taille_case` */
    
    assert(liste != NULL);
    
    MLV_resize_image(liste->pomme_1, taille_case, taille_case);
    MLV_resize_image(liste->pomme_2, taille_case, taille_case);
    MLV_resize_image(liste->pomme_3, taille_case, taille_case);
    MLV_resize_image(liste->pomme_g, taille_case, taille_case);
}
