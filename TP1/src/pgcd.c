#include <limits.h>
#include <stdio.h>

#include "../../common/saisie.h"

int main(void)
{
    int a = 0;
    int b = 0;
    const SaisieOptions options_positif = {SAISIE_ENTIER, 1, 1, 1.0, (double)INT_MAX, "Saisie invalide. Entrez un entier strictement positif."};

    if (!saisie_lire("a : ", &options_positif, &a)) {
        fprintf(stderr, "Fin de saisie inattendue.\n");
        return 1;
    }

    if (!saisie_lire("b : ", &options_positif, &b)) {
        fprintf(stderr, "Fin de saisie inattendue.\n");
        return 1;
    }

    while (a != b) {
        if (a > b) {
            a -= b;
        } else {
            b -= a;
        }
    }

    printf("PGCD = %d\n", a);
    return 0;
}