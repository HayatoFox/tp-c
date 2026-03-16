#include <stdio.h>
#include <limits.h>
#include "../../common/saisie.h"

int main(void)
{
    int x;
    int n;
    long long resultat = 1;

    lire_entier("X : ", &x);
    lire_entier("N : ", &n);

    if (x <= 0 || n < 0) {
        printf("X doit etre strictement positif et N positif ou nul.\n");
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        if (resultat > LLONG_MAX / x) {
            printf("Overflow detecte pendant le calcul.\n");
            return 1;
        }
        resultat *= x;
    }

    printf("%d^%d = %lld\n", x, n, resultat);
    return 0;
}
