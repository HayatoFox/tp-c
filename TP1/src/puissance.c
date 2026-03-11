#include <stdio.h>

int main(void)
{
    int x = 0;
    int n = 0;
    long long resultat = 1;

    printf("X : ");
    if (scanf("%d", &x) != 1) {
        fprintf(stderr, "Saisie invalide pour X.\n");
        return 1;
    }

    printf("N : ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Saisie invalide pour N.\n");
        return 1;
    }

    if (x <= 0 || n < 0) {
        fprintf(stderr, "X doit etre strictement positif et N positif.\n");
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        resultat *= x;
    }

    printf("%d^%d = %lld\n", x, n, resultat);
    return 0;
}