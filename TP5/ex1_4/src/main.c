#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *px;
    px = (int *)malloc(sizeof(int));
    if (px == NULL) {
        printf("Erreur d'allocation.\n");
        return 1;
    }

    *px = 1;

    // Utilisation de %p plutot que %X pour etre standard vis a vis des pointeurs
    printf("Adresse de px : %p\n", (void *)&px);
    printf("Adresse pointee par le pointeur px : %p\n", (void *)px);
    printf("Valeur memorisee a l'adresse pointee par le pointeur px : %d\n\n", *px);

    free(px); // Bonne pratique
    return 0;
}
