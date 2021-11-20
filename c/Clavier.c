#include <MLV/MLV_all.h>

#include "Clavier.h"

int get_touche_pressed() {
    /* Lit une touche et renvoie un entier codant cette touche */
    /* Exemple: La touche GAUCHE renvoie 3 */
    MLV_Keyboard_button touche;
    MLV_Button_state etat;
    
    if (MLV_get_event(&touche, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &etat) != MLV_KEY)
        return -1;
    if (etat != MLV_PRESSED)
        return -1;
    
    if (touche == MLV_KEYBOARD_UP)
        return KEY_UP;
    if (touche == MLV_KEYBOARD_RIGHT)
        return KEY_RIGHT;
    if (touche == MLV_KEYBOARD_DOWN)
        return KEY_DOWN;
    if (touche == MLV_KEYBOARD_LEFT)
        return KEY_LEFT;
    if (touche == MLV_KEYBOARD_z)
        return KEY_Z;
    if (touche == MLV_KEYBOARD_d)
        return KEY_D;
    if (touche == MLV_KEYBOARD_s)
        return KEY_S;
    if (touche == MLV_KEYBOARD_q)
        return KEY_Q;
    
    if (touche == MLV_KEYBOARD_RETURN)
        return KEY_RETURN;
    if (touche == MLV_KEYBOARD_p)
        return KEY_P;
    return NONE;
}

void gerer_action(Monde* monde, int* pause, MLV_Sound *sfx) {
    /* Prend en paramètre le monde, un entier et un son,
     * Si une touche directionnelle est pressée, on modifie la direction
     * de `monde->serpent` ou `monde->versus`.
     * Si la touche `p` est pressée, on modifie l'état de `pause` (1 ou 0) */
    int retour = get_touche_pressed();
    if (monde != NULL && retour >= KEY_UP && retour <= KEY_LEFT && (retour + monde->serpent->direction) % 2)
        monde->serpent->direction = retour;
    if (monde != NULL && monde->regle.mode != SOLO && retour >= KEY_Z && retour <= KEY_Q && (retour + monde->versus->direction) % 2) {
        monde->versus->direction = retour % 4;
    }
    else if (pause != NULL && retour == KEY_P) {
        *pause = (*pause + 1) % 2;
        if (*pause == 1 && sfx != NULL && monde->regle.sound == 1)
            MLV_play_sound(sfx, 1.0);
    }
}
