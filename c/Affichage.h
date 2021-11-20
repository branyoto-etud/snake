#include "Monde.h"
#include "Pomme.h"
#include "Serpent.h"
#include "Regles.h"
#include "Image.h"
#include <MLV/MLV_all.h>

#ifndef __AFFICHAGE__

#define __AFFICHAGE__

typedef enum {
    OFF,
    ON
} Etat;

typedef struct {
    int x,y;
    int largeur, hauteur;
    Etat etat;
    MLV_Font *font;
} Bouton;

typedef struct {
    int x,y;
    int l,h;
    int min, max;
    int nombre;
    MLV_Font *font;
} Boite;

Bouton init_bouton(int x, int y, int l, int h, int etat, MLV_Font* font);
Boite init_boite(int x, int y, int l, int h, int min, int max, int nombre, MLV_Font* font);

void dessine_fleche(int x, int y, int l, int h, MLV_Color couleur);
void draw_centered_text(int x, int y, char text[], MLV_Font* font, MLV_Color couleur, ...);
void draw_bordered_circle(int x, int y, int rayon, int epaisseur, MLV_Color couleur_int, MLV_Color couleur_ext);
void draw_bordered_rectangle(int x, int y, int largeur, int hauteur, int epaisseur, MLV_Color couleur_int, MLV_Color couleur_ext);
void draw_button(Bouton bouton);
void draw_boite(Boite b);

void afficher_quadrillage(Monde monde);
void afficher_pomme(Pomme *pomme, int nb_pomme, int taille_case);
void afficher_serpent(Serpent serpent, int taille_case);
int afficher_monde(Monde monde);

int menu_lancement(Regle *regle);
int menu_option(Regle *regle);
int menu_score();

void changer_couleur_corps(Corps* corps, MLV_Color inte, MLV_Color contour);
int est_dans_bouton(Bouton *bouton, int x, int y);
int est_dans_rectangle(int c_x, int c_y, int x, int y, int l, int h);
int est_dans_boite(Boite *b, int x, int y);



#endif
