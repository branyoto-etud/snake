#ifndef __GESTION__
#include "Regles.h"

#define __GESTION__

void save_regle(Regle regle);
void sauvegarde_score(char *text, int score);
int chargement_score(FILE* fichier, char* nom, int* score);
void trier_scores();

#endif
