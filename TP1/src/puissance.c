#include <limits.h>
#include <stdio.h>

#include "../../common/saisie.h"

static int multiplication_deborde(long long a, int b)
{
    return a > LLONG_MAX / b;
}

int main(void)
{
    int x = 0;
    int n = 0;
    long long resultat = 1;
    const SaisieOptions options_x = {SAISIE_ENTIER, 1, 1, 1.0, (double)INT_MAX, "Saisie invalide. Entrez un entier strictement positif."};
    const SaisieOptions options_n = {SAISIE_ENTIER, 1, 1, 0.0, (double)INT_MAX, "Saisie invalide. Entrez un entier positif ou nul."};

    if (!saisie_lire("X : ", &options_x, &x)) {
        fprintf(stderr, "Fin de saisie inattendue.\n");
        return 1;
    }

    if (!saisie_lire("N : ", &options_n, &n)) {
        fprintf(stderr, "Fin de saisie inattendue.\n");
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        if (multiplication_deborde(resultat, x) != 0) {
            fprintf(stderr, "Overflow detecte pendant le calcul.\n");
            return 1;
        }
        resultat *= x;
    }

    printf("%d^%d = %lld\n", x, n, resultat);
    return 0;
}