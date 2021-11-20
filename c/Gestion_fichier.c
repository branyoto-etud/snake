#include <MLV/MLV_all.h>
#include <stdio.h>
#include <assert.h>

#include "Gestion_fichier.h"

void save_regle(Regle regle) {
    /* Sauvegarde les regles dans un fichier 'Serpent.ini' */
    FILE* fichier;

    fichier = fopen("Serpent.ini", "w");
    
    fprintf(fichier, "%s %d\n", "nombre_de_pomme=", regle.nombre_pomme);
    fprintf(fichier, "%s %d\n", "taille_serpent=", regle.taille_serpent);
    fprintf(fichier, "%s %d\n", "nombre_de_colonnes=", regle.nb_colonnes);
    fprintf(fichier, "%s %d\n", "nombre_de_lignes=", regle.nb_lignes);
    fprintf(fichier, "%s %d\n", "nombre_de_pomme=", regle.taille_case);
    fprintf(fichier, "%s %d\n", "son=", regle.sound);
    fprintf(fichier, "%s %d\n", "bonus=", regle.bonus);
    
    fclose(fichier);
}

void trier_scores() {
    /* Trie les scores du fichier scores.dat et garde seulement les 30 premiers
     * (dans l'ordre décroissant). */
    FILE *source, *copie;
    FILE *sortie = fopen("scores.new", "w");
    char buff[128];
    int n_ligne, i, j, score, max;

    for (i=0; i<30; i+=1) {
        /* Ouverture */
        if ((source = fopen("scores.dat", "r")) == NULL)
            return;
        copie = fopen("scores.cpy", "w");
        /* initialisation */
        n_ligne = 0;
        j = 0;
        max = -1;
        /* parcours source */
        while ( (fgets(buff, 128, source)) != NULL ) {
            /* Stockage du numero de la ligne du max */
            sscanf(buff, "%d", &score);
            if ( score > max ) {
                max = score;
                n_ligne = j;
            }
            j+=1;
        }
        /* Si source est vide */
        if (j == 0)
            break;
        /* Remise au debut */
        rewind(source);
        j=0;
        /* parcours source */
        while ( (fgets(buff, 128, source)) != NULL ) {
            if ( n_ligne == j ) /* stockage dans sortie */
                fprintf(sortie, "%s", buff);
            else     /* stockage dans copie */
                fprintf(copie, "%s", buff);
            j+=1;
        }
        /* Fermeture source et copie */
        fclose(source);
        fclose(copie);
        /* Suppression de source */
        remove("scores.dat");
        /* Renommage de copie en source */
        rename("scores.cpy", "scores.dat");
    }
    /* Fermeture des fichiers */
    if (source != NULL)
        fclose(source);
    if (copie != NULL)
        fclose(copie);
    if (sortie != NULL)
        fclose(sortie);
    /* Renommage de sortie en source */
    remove("scores.cpy");
    remove("scores.dat");
    rename("scores.new", "scores.dat");
}

void sauvegarde_score(char *nom, int score) {
    /* Enregistre le score `score` de `nom` à la fin du fichier 'scores.dat' */
    FILE *fichier = fopen("scores.dat", "a");
    
    assert(nom != NULL);
    
    fprintf(fichier, "%d %s\n", score, nom);
    fclose(fichier);
}

int chargement_score(FILE* fichier, char* nom, int* score) {
    /* Charge un score à l'aide du fichier et enregistre les données
     * récupérées dans nom et score.
     * Renvoie 0 si on à atteint la fin du fichier et 1 sinon */
    
    assert(fichier != NULL);
    assert(nom != NULL);
    assert(score != NULL);
    
    if (fscanf(fichier, "%d%s", score, nom) == EOF)
        return 0;
    return 1;
}
