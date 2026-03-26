#include <stdio.h>
#include <stdlib.h>

#define N 3

typedef struct maillon {
    int x;
    struct maillon *suiv;
} maillon;

int main(void)
{
    maillon *lc;
    maillon *tete;
    int cpt;

    /* initialisation du premier maillon */
    lc = (maillon *)malloc(sizeof(maillon));
    if (lc == NULL) {
        return 1;
    }
    tete = lc;

    // Creation des maillons en fin de liste
    for (cpt = 1; cpt < N; cpt++) {
        lc->suiv = (maillon *)malloc(sizeof(maillon));
        if (lc->suiv == NULL) {
            // Libérer la mémoire déjà allouée avant de quitter
            lc->suiv = NULL;
            maillon *tmp = tete;
            while (tmp != NULL) {
                maillon *suivant = tmp->suiv;
                free(tmp);
                tmp = suivant;
            }
            return 1;
        }
        lc = lc->suiv;
    }
        lc->suiv = NULL;

    cpt = 0;
    lc = tete;

    // remplissage des valeurs de chacun des maillons
    while (lc != NULL) {
        lc->x = cpt;
        cpt++;
        lc = lc->suiv;
    }

    lc = tete;

    // Affichage des maillons et liberation de la memoire
    while (lc != NULL) {
        maillon *suivant = lc->suiv;
        
        printf("Valeur du champ courant = %d\n", lc->x);
        printf("Adresse maillon courant = %p et du suivant = %p\n\n", (void *)lc, (void *)lc->suiv);
        
        free(lc); // Nettoyage de memoire en meme temps pour eviter les fuites
        lc = suivant;
    }

    return 0;
}
