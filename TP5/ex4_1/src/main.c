#include <stdio.h>
#include <stdlib.h>

typedef struct maillon {
    int x;
    struct maillon *suiv;
} maillon;

int main(void)
{
    maillon lc;
    lc.x = 1;

    printf("Valeur du champ x = %d\n\n", lc.x);
    
    lc.suiv = (maillon *)malloc(sizeof(maillon));
    if (lc.suiv == NULL) {
        printf("Erreur d'allocation.\n");
        return 1;
    }

    lc.suiv->x = 2;
    lc.suiv->suiv = NULL;
    
    printf("Valeur du champ x du deuxieme maillon = %d\n\n", lc.suiv->x);

    free(lc.suiv);

    return 0;
}
