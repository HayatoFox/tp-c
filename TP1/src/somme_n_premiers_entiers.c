#include <stdio.h>

static long long somme_for_croissant(int n)
{
    long long somme = 0;

    for (int i = 1; i <= n; ++i) {
        somme += i;
    }

    return somme;
}

static long long somme_for_decroissant(int n)
{
    long long somme = 0;

    for (int i = n; i >= 1; --i) {
        somme += i;
    }

    return somme;
}

static long long somme_while_croissant(int n)
{
    int i = 1;
    long long somme = 0;

    while (i <= n) {
        somme += i;
        ++i;
    }

    return somme;
}

static long long somme_while_decroissant(int n)
{
    int i = n;
    long long somme = 0;

    while (i >= 1) {
        somme += i;
        --i;
    }

    return somme;
}

int main(void)
{
    int n = 0;

    printf("n : ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Saisie invalide.\n");
        return 1;
    }

    if (n < 0) {
        fprintf(stderr, "n doit etre positif ou nul.\n");
        return 1;
    }

    printf("for croissant     : %lld\n", somme_for_croissant(n));
    printf("for decroissant   : %lld\n", somme_for_decroissant(n));
    printf("while croissant   : %lld\n", somme_while_croissant(n));
    printf("while decroissant : %lld\n", somme_while_decroissant(n));

    return 0;
}