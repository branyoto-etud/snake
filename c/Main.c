#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <MLV/MLV_all.h>

#include "Monde.h"
#include "Regles.h"
#include "Affichage.h"
#include "Clavier.h"
#include "Gestion_fichier.h"

/* Bug 1 le temps defile toujours en pause. CORRIGE*/
/* Pas d'égalité */


int boucle_jeu(Monde *monde) {
    /* Prend en argument un monde fraichement (re)initialisé.
     * Contient toutes les actions nescessaires pour le déroulement d'une partie.
     * Renvoie 0 si une allocation/chargement s'est mal passé et 1 sinon */
    MLV_Font* normal_font, *big_font;
    MLV_Sound *sfx_manger, *sfx_mvt, *sfx_pause;
    int pause = 0, frame = 0, frame_rate = 125;
    int code_err;
    int decalage = MLV_get_time();
    
    assert(monde != NULL);
    
    /* Chargement des polices */
    if ((normal_font = MLV_load_font("font/game_font_1.ttf", 30)) == NULL) return 0;
    if ((big_font = MLV_load_font("font/game_font_1.ttf", 50)) == NULL) return 0;
    /* Chargement partie audio */
    MLV_init_audio();
    if ((sfx_manger = MLV_load_sound("sound/MANGER.wav")) == NULL) return 0;
    if ((sfx_mvt = MLV_load_sound("sound/BOUGER.wav")) == NULL) return 0;
    if ((sfx_pause = MLV_load_sound("sound/PAUSE.wav")) == NULL) return 0;
    
    while (!mort_serpent(monde, monde->serpent) && (monde->regle.mode == SOLO || !mort_serpent(monde, monde->versus))) {
        if (!pause) {
            monde->temps = MLV_get_time() - decalage;
            MLV_stop_all_sounds();
            /* Deplacement */
            code_err = deplacement_complet(monde, monde->serpent, &frame_rate, sfx_manger);
            if (code_err == -1) return 0;
            if (code_err == 0) break;
            if (monde->regle.mode != SOLO) {
                code_err = deplacement_complet(monde, monde->versus, &frame_rate, sfx_manger);
                if (code_err == -1) return 0;
                if (code_err == 0) break;
            }
            if (frame % 2 == 0 && monde->regle.sound == 1)
                MLV_play_sound(sfx_mvt, 0.2);
            if (afficher_monde(*monde) == 0) return 0;
        } else { /* Affichage de la pause */
            decalage = MLV_get_time() - monde->temps;
            if (frame % 6 > 2) {
                draw_centered_text((monde->regle.nb_colonnes+2)*monde->regle.taille_case /2 , (monde->regle.nb_lignes-2)*monde->regle.taille_case /2, "PAUSE", big_font, MLV_COLOR_WHITE);
                draw_centered_text((monde->regle.nb_colonnes+2)*monde->regle.taille_case /2 , (monde->regle.nb_lignes+2)*monde->regle.taille_case /2, "Appuyer sur 'p' pour reprendre.", normal_font, MLV_COLOR_WHITE);
            } else {
                draw_centered_text((monde->regle.nb_colonnes+2)*monde->regle.taille_case /2 , (monde->regle.nb_lignes-2)*monde->regle.taille_case /2, "PAUSE", big_font, MLV_COLOR_BLACK);
                draw_centered_text((monde->regle.nb_colonnes+2)*monde->regle.taille_case /2 , (monde->regle.nb_lignes+2)*monde->regle.taille_case /2, "Appuyer sur 'p' pour reprendre.", normal_font, MLV_COLOR_BLACK);
            }
            MLV_actualise_window();
        }
        frame += 1;
        /* Evenements clavier */
        gerer_action(monde, &pause, sfx_pause);
        /* Attente de boucle */
        MLV_wait_milliseconds(frame_rate);
    }
    /* Liberation des polices */
    MLV_free_font(big_font);
    MLV_free_font(normal_font);
    /* Liberation des sons */
    MLV_free_sound(sfx_manger);
    MLV_free_sound(sfx_mvt);
    MLV_free_sound(sfx_pause);
    MLV_free_audio();
    return 1;
}

int message_mort(Monde *monde) {
    /* Prend en argument le monde à la fin de la partie et
     * affiche le score du joueur et lui permet de sauvegarder son score
     * Renvoie 0 si une erreur survient et 1 sinon*/
    int largeur = (monde->regle.nb_colonnes+2)*monde->regle.taille_case;
    int hauteur = (monde->regle.nb_lignes+2)*monde->regle.taille_case;
    MLV_Font* normal_font = MLV_load_font("font/game_font_1.ttf", 30);
    MLV_Font* big_font = MLV_load_font("font/game_font_1.ttf", 50);
    MLV_Sound* mort;
    char *text;
    
    assert(monde != NULL);
    
    MLV_init_audio();
    if ((mort = MLV_load_sound("sound/MORT.wav")) == NULL) return 0;
    
    if (monde->regle.sound == ON)
        MLV_play_sound(mort, 1.0);
    if (monde->regle.mode == SOLO || deplacer_serpent(monde, monde->serpent) != 1)
        changer_couleur_corps(&(monde->serpent->corps), MLV_COLOR_RED3, MLV_COLOR_RED4);
    else 
        changer_couleur_corps(&(monde->versus->corps), MLV_COLOR_RED3, MLV_COLOR_RED4);
    if (afficher_monde(*monde) == 0) return 0;
    MLV_actualise_window();
    if (monde->regle.mode == SOLO) {
        draw_centered_text(largeur / 2, hauteur /2, "Vous etes mort!", big_font, MLV_COLOR_BLACK);
        draw_centered_text(largeur /2 , (monde->regle.nb_lignes+8)*monde->regle.taille_case /2, "avec un score de : %d", normal_font, MLV_COLOR_BLACK, monde->nb_pomme_manger);
        MLV_wait_input_box_with_font(largeur * 1/4 , hauteur * 3/4 - 3 * monde->regle.taille_case, largeur / 2, hauteur / 4,
                                        MLV_COLOR_BLACK, MLV_COLOR_BLACK, MLV_COLOR_OLDLACE, "Entrer votre nom :", &text, normal_font);
        sauvegarde_score(text, monde->nb_pomme_manger);
		free(text);
    } else {
        if (monde->serpent->corps->interieur == MLV_COLOR_RED3)
            draw_centered_text(largeur /2 , hauteur /2, "Le joueur 2 a gagne!", big_font, MLV_COLOR_BLACK);
        else
            draw_centered_text(largeur /2 , hauteur /2, "Le joueur 1 a gagne!", big_font, MLV_COLOR_BLACK);
		MLV_actualise_window();
		MLV_wait_mouse(NULL,NULL);
    }
    MLV_free_font(big_font);
    MLV_free_font(normal_font);
    MLV_free_sound(mort);
    MLV_free_audio();
    return 1;
}

int jeu(Regle regle, ListeImg liste_img) {
    /* Partie jeu du programme : initialise le monde et lance le jeu
     * Renvoie 0 si il y a eu un problème pendant le jeu 0 sinon */
    Monde monde;
    MLV_Font *big_font;
    
    MLV_free_window();
    if (init_monde(&monde, regle, liste_img) == 0)
        return 0;
    /* Demarage du jeu */
    MLV_create_window("Snake", "snake", (regle.nb_colonnes+2)*monde.regle.taille_case, (regle.nb_lignes+2)*monde.regle.taille_case);
    if ((big_font = MLV_load_font("font/game_font_1.ttf", 50)) == NULL) return 0;
    
    /* Attends jusqu'à ce que l'utilisateur appuie sur entrer */
    if (afficher_monde(monde) == 0) return 0;
    draw_centered_text((regle.nb_colonnes+2)*monde.regle.taille_case /2 , (regle.nb_lignes+2)*monde.regle.taille_case /2, "Appuyer sur ENTRER.", big_font, MLV_COLOR_BLACK);
    MLV_actualise_window();
    
    while (get_touche_pressed() != KEY_RETURN) {}
    
    /* Boucle de jeu */
    if (boucle_jeu(&monde) == 0)
        return 0;
    if (message_mort(&monde) == 0)
        return 0;
    
    free(big_font);
    return 1;
}


int main(void){
    Regle regle = init_regle();
    ListeImg liste_img;
    int retour;
    
    srand(time(NULL));
    /* Chargement images */
    MLV_create_window("Chargement", "chargement", 400, 500);
    if (init_image(&liste_img, regle.taille_case) == 0) {
        printf("Impossible d'ouvrir une image! \n");
        printf("Verifiez que vous êtes bien dans le dossier Snake.\n");
        return 1;
    }
    MLV_free_window();
    
    /* Boucle du menu */
    do {
        MLV_create_window("Menu", "menu", 800, 500);
        retour = menu_lancement(&regle); 
        switch (retour) {
            case 1: /* Lancer jeu */
                if (jeu(regle, liste_img) == 0)
                    return 1;
                break;
            case 2: /* Options */
                MLV_change_window_size(800, 600);
                if (menu_option(&regle) == 0) return 1;
                resize_all_image(&liste_img, regle.taille_case);
                MLV_change_window_size(800, 500);
                break;
            case 3: /* Tableau de scores */
                trier_scores();
                menu_score();
                break;
        }
        MLV_free_window();
    } while (retour != 0);

    /* Fin programme */
    return 0;
}
