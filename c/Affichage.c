#include <MLV/MLV_all.h>
#include <stdarg.h>
#include <assert.h>

#include "Affichage.h"
#include "Gestion_fichier.h"

/* Initialisation */
Bouton init_bouton(int x, int y, int l, int h, int etat, MLV_Font *font) {
    /* Initialise un bouton on/off de largeur `l` et de hauteur `h` ayant
     * pour ancrage haut-gauche le couple d'entier (x,y) et pour police `font`.
     * Un ratio de 2/3 est recommandé.
     * Renvoie le bouton initialisé */
    Bouton bouton;
    
    assert(font != NULL);
    assert(x >= 0);
    assert(y >= 0);
    
    bouton.x = x;
    bouton.y = y;
    bouton.hauteur = l;
    bouton.largeur = h;
    bouton.etat = etat;
    bouton.font = font;
    return bouton;
}

Boite init_boite(int x, int y, int l, int h, int min, int max, int nombre, MLV_Font* font) {
    /* Initialise une boite contenant un entier `nombre` compris entre `min` et `max`
     * ayant pour ancrage haut-gauche le couple (x,y) et pour dimention `l`et `h`
     * ainsi que pour police `font`
     * Renvoie la boite initialisée. */
    Boite b;
    
    assert(font != NULL);
    assert(x >= 0);
    assert(y >= 0);
    
    b.x = x;
    b.y = y;
    b.l = l;
    b.h = h;
    b.min = min;
    b.max = max;
    b.nombre = nombre;
    b.font = font;
    return b;
}

void dessine_fleche(int x, int y, int l, int h, MLV_Color couleur) {
    int vx[7], vy[7];
    vx[0] = x; vy[0] = y + h / 2;
    vx[1] = x + 2 * l / 5; vy[1] = y + h / 4;
    vx[2] = x + 2 * l / 5; vy[2] = y - 2 + h / 2;
    vx[3] = x + l * 7 / 8; vy[3] = y - 2 + h / 2;
    vx[4] = x + l * 7 / 8; vy[4] = y + 2 + h / 2;
    vx[5] = x + 2 * l / 5; vy[5] = y + 2 + h / 2;
    vx[6] = x + 2 * l / 5; vy[6] = y + 3 * h / 4;
    
    MLV_draw_filled_polygon(vx, vy, 7, couleur);
}

/* Fonctions de dessin */
void draw_centered_text(int x, int y, char text[], MLV_Font* font, MLV_Color couleur, ...) {
    /* Dessine sur la fenetre le texte `text` ayant pour police `font` et pour couleur `couleur`
     * ayant pour centre (x,y) avec des arguments optionnels (comme printf) */
    int l, h;
    va_list lst;
    
    assert(font != NULL);
    assert(text != NULL);
    assert(x >= 0);
    assert(y >= 0);
    
    va_start(lst, couleur);
    MLV_get_size_of_text_with_font_va(text, &l, &h, font, lst);
    
    MLV_draw_text_with_font_va(x - l / 2, y - h / 2, text, font, couleur, lst);
    va_end(lst);
}

void draw_bordered_circle(int x, int y, int rayon, int epaisseur, MLV_Color couleur_int, MLV_Color couleur_ext) {
    /* Dessine un cercle épais de centre (x,y) et de rayon `rayon` ayant pour epaisseur `epaisseur`
     * et pour couleurs `couleur_int pour l'interieur et `couleur_ext`pour l'exterrieur */
    MLV_draw_filled_circle(x, y, rayon, couleur_ext);
    MLV_draw_filled_circle(x, y, rayon - epaisseur, couleur_int);
}

void draw_bordered_rectangle(int x, int y, int largeur, int hauteur, int epaisseur, MLV_Color couleur_int, MLV_Color couleur_ext) {
    /* Dessine un rectangle épais ayant pour ancrage haut-gauche (x,y) et pour dimention
     * `hauteur`et `largeur` ainsi que pour epaisseur `epaisseur` et pour couleurs
     * `couleur_int pour l'interieur et `couleur_ext`pour l'exterrieur */
    MLV_draw_filled_rectangle(x, y, largeur, hauteur, couleur_ext);
    MLV_draw_filled_rectangle(x + epaisseur/2, y + epaisseur/2, largeur - 3*epaisseur/4, hauteur - 3*epaisseur/4, couleur_int);
}

void draw_button(Bouton bouton) {
    /* Dessine un bouton en fonction de son etat (ON/OFF) */
    MLV_draw_filled_circle(bouton.x + bouton.largeur / 4, bouton.y + bouton.hauteur / 2,
                 bouton.hauteur / 2, MLV_COLOR_LIGHT_SLATE_GREY);
    MLV_draw_filled_circle(bouton.x + bouton.largeur * 3 / 4, bouton.y + bouton.hauteur / 2,
                 bouton.hauteur / 2, MLV_COLOR_LIGHT_SLATE_GREY);
    MLV_draw_filled_rectangle(bouton.x + bouton.largeur / 4, bouton.y, bouton.largeur * 2 / 4, bouton.hauteur, MLV_COLOR_LIGHT_SLATE_GREY);
    if (bouton.etat == ON) {
        MLV_draw_filled_circle(bouton.x + bouton.largeur * 3 / 4, bouton.y + bouton.hauteur / 2, bouton.hauteur / 2 - 5, MLV_COLOR_DIM_GREY);
        MLV_draw_filled_circle(bouton.x + bouton.largeur / 4, bouton.y + bouton.hauteur / 2, bouton.hauteur / 2 - 5, MLV_COLOR_FORESTGREEN);
        MLV_draw_circle(bouton.x + bouton.largeur / 4, bouton.y + bouton.hauteur / 2, bouton.hauteur / 2 - 5, MLV_COLOR_BLACK);
        draw_centered_text(bouton.x + bouton.largeur / 4 + 1, bouton.y + bouton.hauteur / 2 + 1, "On", bouton.font, MLV_rgba(70,70,70,255));
        draw_centered_text(bouton.x + bouton.largeur / 4, bouton.y + bouton.hauteur / 2, "On", bouton.font, MLV_rgba(0,0,0,255));
    } else {
        MLV_draw_filled_circle(bouton.x + bouton.largeur / 4, bouton.y + bouton.hauteur / 2, bouton.hauteur / 2 - 5, MLV_COLOR_DIM_GREY);
        MLV_draw_filled_circle(bouton.x + bouton.largeur * 3 / 4, bouton.y + bouton.hauteur / 2, bouton.hauteur / 2 - 5, MLV_COLOR_RED3);
        MLV_draw_circle(bouton.x + bouton.largeur * 3 / 4, bouton.y + bouton.hauteur / 2, bouton.hauteur / 2 - 5, MLV_COLOR_BLACK);
        draw_centered_text(bouton.x + bouton.largeur * 3 / 4 + 1, bouton.y + bouton.hauteur / 2 + 1, "Off", bouton.font, MLV_rgba(50,50,50,255));
        draw_centered_text(bouton.x + bouton.largeur * 3 / 4, bouton.y + bouton.hauteur / 2, "Off", bouton.font, MLV_rgba(0,0,0,255));
    }
}

void draw_boite(Boite b) {
    /* Dessine une boite `b` et deux fleches permetant d'augmenter ou de
     * diminuer la valeur du nombre de `b` */
    int x2, y2;
    MLV_draw_filled_rectangle(b.x, b.y, b.l, b.h, MLV_COLOR_FLORAL_WHITE);
    MLV_draw_rectangle(b.x, b.y, b.l, b.h, MLV_COLOR_BLACK);
    
    draw_centered_text(b.x + b.l / 3, b.y + b.h / 2, "%d", b.font, MLV_COLOR_BLACK, b.nombre);
    x2 = b.x + 2 * b.l / 3;
    MLV_draw_filled_rectangle(x2, b.y, b.l / 3, b.h, MLV_COLOR_GREY);
    MLV_draw_rectangle(x2, b.y, b.l / 3, b.h / 2, MLV_COLOR_BLACK);
    MLV_draw_rectangle(x2, b.y + b.h / 2, b.l / 3, b.h / 2, MLV_COLOR_BLACK);
    
    MLV_draw_line(x2 + b.l / 18, b.y + b.h * 2 / 6, x2 + b.l / 6, b.y + b.h / 6, MLV_COLOR_BLACK);
    MLV_draw_line(x2 + b.l * 5 / 18, b.y + b.h * 2 / 6, x2 + b.l / 6, b.y + b.h / 6, MLV_COLOR_BLACK);
    
    y2 = b.y + b.h / 2;
    MLV_draw_line(x2 + b.l / 18, y2 + b.h / 6, x2 + b.l / 6, y2 + b.h * 2 / 6, MLV_COLOR_BLACK);
    MLV_draw_line(x2 + b.l * 5 / 18, y2 + b.h / 6, x2 + b.l / 6, y2 + b.h * 2 / 6, MLV_COLOR_BLACK);
}

/* Fonctions d'affichage */
void afficher_quadrillage(Monde monde) {
    /* Affiche la grille de fond du jeu */
    int i,j;
    
    for (i=0; i<monde.largeur; i+=1) {
        for (j=0; j<monde.hauteur; j+=1) {
            if ((i+j) % 2 == 0)
                MLV_draw_filled_rectangle((i + 1) * monde.regle.taille_case, (j + 1) * monde.regle.taille_case, monde.regle.taille_case, monde.regle.taille_case, MLV_COLOR_BLANCHED_ALMOND);
            else
                MLV_draw_filled_rectangle((i + 1) * monde.regle.taille_case, (j + 1) * monde.regle.taille_case, monde.regle.taille_case, monde.regle.taille_case, MLV_COLOR_PEACHPUFF);
        }
    }
}

void afficher_pomme(Pomme *pomme, int nb_pomme, int taille_case) {
    /* Affiche les pommes du tableau `pomme`, il y en a `nb_pomme` */
    int i;
    
    assert(pomme != NULL);
    assert(nb_pomme >= 0);
    
    for (i=0; i<nb_pomme; i+=1)
        MLV_draw_image(pomme[i].image, (pomme[i].pos.x + 1) * taille_case, (pomme[i].pos.y + 1) * taille_case);
}

void afficher_serpent(Serpent serpent, int taille_case) {
    /* Affiche le serpent `serpent` */
    Corps corps;
    
    for (corps = serpent.corps; corps != NULL; corps = corps->suivant)
        draw_bordered_circle((corps->position.x + 1.5) * taille_case, (corps->position.y + 1.5) * taille_case, taille_case/2, 2, corps->interieur, corps->contour);
    
}

int afficher_monde(Monde monde) {
    /* Affiche tous les composants du monde:
     * le terrain, les pommes, le(s) serpent(s) et le score
     * Renvoie 0 si une erreur survient et 1 sinon */
    MLV_Font* small_font = MLV_load_font("./font/game_font_2.ttf", monde.regle.taille_case);
    
    if (small_font == NULL) return 0;
    
    MLV_clear_window(MLV_COLOR_OLDLACE);
    MLV_draw_rectangle(monde.regle.taille_case-1, monde.regle.taille_case-1, monde.regle.taille_case * monde.largeur+2, monde.regle.taille_case * monde.hauteur+2, MLV_COLOR_GREY18);
    
    afficher_quadrillage(monde);
    afficher_pomme(monde.pomme, monde.regle.nombre_pomme, monde.regle.taille_case);
    afficher_serpent(*(monde.serpent), monde.regle.taille_case);
    
    if (monde.regle.mode != SOLO)
        afficher_serpent(*(monde.versus), monde.regle.taille_case);
    
    draw_centered_text((monde.largeur +2) * monde.regle.taille_case / 2, 2 * monde.regle.taille_case/5,
                        "Vous avez %d points!" , small_font, MLV_COLOR_BLACK, monde.nb_pomme_manger);
    
    draw_centered_text((monde.largeur +2) * monde.regle.taille_case / 2, (2 + monde.hauteur - .5) * monde.regle.taille_case,
                        "%.3f s" , small_font, MLV_COLOR_BLACK, monde.temps / 1000.0);
    MLV_actualise_window();
    MLV_free_font(small_font);
    return 1;
}

/* Affichage du menu */
int menu_lancement(Regle *regle) {
    /* Menu graphique permettant de lancer le jeu, modifier les regles ou
     * voir le tableau de scores. */
    /* Renvoie 1 pour lancer le jeu, 2 pour lancer les options, 3 pour afficher les scores et
     * 0 pour quitter le jeu et -1 pour une erreur */
    int x,y;
    MLV_Image *titre, *solo, *versus, *option, *scores, *son_on, *son_off;
    MLV_Font *quitter;
    
    assert(regle != NULL);
    
    /* Initialisation */
    if ((titre = MLV_load_image("img/Snake.png")) == NULL) return -1;
    MLV_resize_image(titre, 300, 100);
    if ((solo = MLV_load_image("img/Solo.png")) == NULL) return -1;
    MLV_resize_image(solo, 100, 60);
    if ((versus = MLV_load_image("img/Versus.png")) == NULL) return -1;
    MLV_resize_image(versus, 150, 60);
    if ((option = MLV_load_image("img/settings.png")) == NULL) return -1;
    MLV_resize_image(option, 75, 75);
    if ((scores = MLV_load_image("img/leaderboard.png")) == NULL) return -1;
    MLV_resize_image(scores, 75, 75);
    if ((son_on = MLV_load_image("img/sound_on.png")) == NULL) return -1;
    MLV_resize_image(son_on, 75, 75);
    if ((son_off = MLV_load_image("img/sound_off.png")) == NULL) return -1;
    MLV_resize_image(son_off, 75, 75);
    if ((quitter = MLV_load_font("font/game_font_2.ttf", 40)) == NULL) return -1;
    
    /* Dessin */
    MLV_clear_window(MLV_COLOR_ANTIQUEWHITE);
    /* Titre */
    MLV_draw_image(titre, 250, 10);
    /* Solo */
    MLV_draw_filled_rectangle(170, 160, 170, 70, MLV_COLOR_PEACHPUFF3);
    MLV_draw_filled_rectangle(165, 155, 170, 70, MLV_COLOR_PEACHPUFF2);
    MLV_draw_image(solo, 200, 160);
    /* Chrono */
    /* Versus */
    MLV_draw_filled_rectangle(465, 160, 170, 70, MLV_COLOR_PEACHPUFF3);
    MLV_draw_filled_rectangle(460, 155, 170, 70, MLV_COLOR_PEACHPUFF2);
    MLV_draw_image(versus, 475, 160);
    /* Option */
    MLV_draw_filled_rectangle(255, 300, 85, 85, MLV_COLOR_PEACHPUFF3);
    MLV_draw_filled_rectangle(250, 295, 85, 85, MLV_COLOR_PEACHPUFF2);
    MLV_draw_image(option, 255, 300);
    /* Leaderboard */
    MLV_draw_filled_rectangle(362, 300, 85, 85, MLV_COLOR_PEACHPUFF3);
    MLV_draw_filled_rectangle(357, 295, 85, 85, MLV_COLOR_PEACHPUFF2);
    MLV_draw_image(scores, 362, 300);
    /* Son */
    MLV_draw_filled_rectangle(470, 300, 85, 85, MLV_COLOR_PEACHPUFF3);
    MLV_draw_filled_rectangle(465, 295, 85, 85, MLV_COLOR_PEACHPUFF2);
    if (regle->sound == 1)
        MLV_draw_image(son_on, 470, 300);
    else
        MLV_draw_image(son_off, 470, 300);
    /* Quitter */
    draw_centered_text(400, 430, "Quitter", quitter, MLV_COLOR_RED);
    
    /* Action au clic */
    do {
        MLV_actualise_window();
        MLV_wait_mouse(&x, &y);
        if (est_dans_rectangle(x, y, 165, 155, 170, 70)) {
            regle->mode = SOLO;
            return 1;
        }
        if (est_dans_rectangle(x, y, 460, 155, 170, 70)) {
            regle->mode = VERSUS;
            return 1;
        }
        if (est_dans_rectangle(x, y, 250, 295, 85, 85))
            return 2;
        if (est_dans_rectangle(x, y, 357, 295, 85, 85))
            return 3;
        if (est_dans_rectangle(x, y, 465, 295, 85, 85)) {
            regle->sound = (regle->sound + 1) % 2;
            
            MLV_draw_filled_rectangle(465, 295, 85, 85, MLV_COLOR_PEACHPUFF2);
            if (regle->sound == 1)
                MLV_draw_image(son_on, 470, 300);
            else
                MLV_draw_image(son_off, 470, 300);
        }
    } while (!est_dans_rectangle(x, y, 330, 410, 140, 50));
    return 0;
}

int menu_option(Regle *regle) {
    /* Affiche le menu des options.
     * Renvoie 0 si une erreur survient et 1 sinon */
    int x, y;
    MLV_Font *titre, *texte, *bouton; 
    Bouton bonus, son;
    Boite serpent, pommes, colonnes, lignes, cases;
    
    assert(regle != NULL);
    
    if ((titre = MLV_load_font("font/game_font_1.ttf", 60)) == NULL) return 0;
    if ((bouton = MLV_load_font("font/game_font_2.ttf", 12)) == NULL) return 0;
    if ((texte = MLV_load_font("font/game_font_2.ttf", 20)) == NULL) return 0;
    
    bonus = init_bouton(525, 150, 35, 50, regle->bonus, bouton);
    son = init_bouton(525, 220, 35, 50, regle->sound, bouton);
    serpent = init_boite(500, 285, 100, 30, 1, 100, regle->taille_serpent, texte);
    pommes = init_boite(500, 355, 100, 30, 1, 50, regle->nombre_pomme, texte);
    colonnes = init_boite(500, 410, 100, 30, 5, 100, regle->nb_colonnes, texte);
    lignes = init_boite(500, 440, 100, 30, 5, 100, regle->nb_lignes, texte);
    cases = init_boite(500, 495, 100, 30, 5, 100, regle->taille_case, texte);
    x = y = -1;
    
    do {
        MLV_clear_window(MLV_COLOR_ANTIQUEWHITE);
        draw_centered_text(400, 75, "OPTION", titre, MLV_COLOR_BLACK);
        /* Bonus zone */
        est_dans_bouton(&bonus, x, y);
        regle->bonus = bonus.etat;
        MLV_draw_text_with_font(200, 150, "pommes Bonus", texte, MLV_COLOR_BLACK);
        draw_button(bonus);
        /* Sound zone */
        est_dans_bouton(&son, x, y);
        regle->sound = son.etat;
        MLV_draw_text_with_font(200, 220, "Son", texte, MLV_COLOR_BLACK);
        draw_button(son);
        /* Taille serpent */
        est_dans_boite(&serpent, x, y);
        draw_boite(serpent);
        regle->taille_serpent = serpent.nombre;
        MLV_draw_text_with_font(200, 290, "Taille du Serpent", texte, MLV_COLOR_BLACK);
        /* Nb pommess */
        est_dans_boite(&pommes, x, y);
        draw_boite(pommes);
        regle->nombre_pomme = pommes.nombre;
        MLV_draw_text_with_font(200, 360, "Nombre de Pommes", texte, MLV_COLOR_BLACK);
        /* Nb colonnes/lignes */
        est_dans_boite(&colonnes, x, y);
        est_dans_boite(&lignes, x, y);
        draw_boite(colonnes);
        draw_boite(lignes);
        regle->nb_colonnes = colonnes.nombre;
        regle->nb_lignes = lignes.nombre;
        MLV_draw_text_with_font(200, 430, "Dimention du plateau", texte, MLV_COLOR_BLACK);
        /* Taille cases */
        est_dans_boite(&cases, x, y);
        draw_boite(cases);
        regle->taille_case = cases.nombre;
        MLV_draw_text_with_font(200, 500, "Taille des cases", texte, MLV_COLOR_BLACK);
        /* Retour */
        MLV_draw_filled_rectangle(2, 2, 40, 40, MLV_COLOR_SIENNA4);
        MLV_draw_filled_rectangle(0, 0, 40, 40, MLV_COLOR_SIENNA2);
        dessine_fleche(5, 5, 30, 30, MLV_COLOR_BLACK);
        
        
        MLV_actualise_window();
        MLV_wait_mouse(&x, &y);
    } while (!est_dans_rectangle(x, y, 0, 0, 40, 40));
    /* sauvegarde_des_options */
    save_regle(*regle);
    return 1;
}

int menu_score() {
    /* Affich les 30 premiers scores du fichier scores.dat".
     * Renvoie 0 si une erreur survient et 1 sinon */
    FILE* fichier;
    int i, j, score;
    char nom[32];
    MLV_Font *titre, *texte;
    fichier = fopen("scores.dat", "r");
    
    if ((titre = MLV_load_font("font/game_font_1.ttf", 60)) == NULL) return 0;
    if ((texte = MLV_load_font("font/game_font_2.ttf", 20)) == NULL) return 0;
    
    MLV_clear_window(MLV_COLOR_ANTIQUEWHITE);
    draw_centered_text(400, 60, "SCORES", titre, MLV_COLOR_BLACK);
    if (fichier != NULL) {
        for (i=0; i<3; i+=1) {
            for (j=0; j<10; j+=1) {
                if (chargement_score(fichier, nom, &score) == 0)
                    break;
                draw_centered_text((i+1) * 200, j*30 + 150 ,"%s : %d", texte, MLV_COLOR_BLACK, nom, score);
            }
        }
        fclose(fichier);
    }
    MLV_actualise_window();
    MLV_wait_mouse(NULL,NULL);
    return 1;
}


/* Autre */
void changer_couleur_corps(Corps* corps, MLV_Color inte, MLV_Color contour) {
    /* Prend en parametre le corps d'un serpent ainsi que sa nouvelle couleur,
     * Change la couleur du serpent. */
    if (*corps == NULL)
        return;
    (*corps)->interieur = inte;
    (*corps)->contour = contour;
    changer_couleur_corps(&((*corps)->suivant), inte, contour);
}

int est_dans_bouton(Bouton *bouton, int x, int y) {
    /* Change l'état du bouton si le clic (x,y) de l'utilisateur est sur le bouton.
     * Renvoie 1 si l'etat change, 0 sinon*/
    
    assert(bouton != NULL);
    
    if (bouton->x <= x && x <= bouton->x + bouton->largeur && bouton->y <= y && y <= bouton->y + bouton->hauteur) {
        bouton->etat = (bouton->etat + 1) % 2;
        return 1;
    }
    return 0;
}

int est_dans_rectangle(int c_x, int c_y, int x, int y, int l, int h) {
    /* Renvoie 1 si le clic (c_x,c_y) est dans le rectangle ancré en (x,y)
     * et de dimention `l` et `h` et 0 s'il n'y est pas */
    return  (x <= c_x && c_x <= x+l && y <= c_y && c_y <= y + h);
}

int est_dans_boite(Boite *b, int x, int y) {
    /* Si le clic (x,y) est sur une des fleches on augmente ou diminue
     * la valeur de l'entier contenue dans la boite `b`. 
     * Renvoie 1 si le clic est sur une des fleches et 0 sinon */
    
    assert(b != NULL);
    
    if (b->x + b->l * 2 / 3 <= x && x <= b->x + b->l && b->y <= y && y <= b->y + b->h / 2) {
        if (b->nombre < b->max)
            b->nombre += 1;
        return 1;
    } else if (b->x + b->l * 2 / 3 <= x && x <= b->x + b->l && b->y + b->h / 2 <= y && y <= b->y + b->h) {
        if (b->nombre > b->min)
            b->nombre -= 1;
        return 1;
    }
    return 0;
}
