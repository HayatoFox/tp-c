#include <stdio.h>
#include "../../common/saisie.h"

int main(void)
{
    int n;
    long long somme;
    int k;

    lire_entier("n : ", &n);

    if (n < 0) {
        printf("Le nombre doit etre positif ou nul.\n");
        return 1;
    }

    /* Boucle for a indice incremente */
    somme = 0;
    for (int i = 1; i <= n; ++i) {
        somme += i;
    }
    printf("for croissant     : %lld\n", somme);

    /* Boucle for a indice decremente */
    somme = 0;
    for (int i = n; i >= 1; --i) {
        somme += i;
    }
    printf("for decroissant   : %lld\n", somme);

    /* Boucle while a indice incremente */
    somme = 0;
    k = 1;
    while (k <= n) {
        somme += k;
        ++k;
    }
    printf("while croissant   : %lld\n", somme);

    /* Boucle while a indice decremente */
    somme = 0;
    k = n;
    while (k >= 1) {
        somme += k;
        --k;
    }
    printf("while decroissant : %lld\n", somme);

    return 0;
}
