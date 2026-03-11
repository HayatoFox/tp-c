#include <stdio.h>

int main(void)
{
    int a = 0;
    int b = 0;

    printf("a : ");
    if (scanf("%d", &a) != 1) {
        fprintf(stderr, "Saisie invalide pour a.\n");
        return 1;
    }

    printf("b : ");
    if (scanf("%d", &b) != 1) {
        fprintf(stderr, "Saisie invalide pour b.\n");
        return 1;
    }

    if (a <= 0 || b <= 0) {
        fprintf(stderr, "a et b doivent etre strictement positifs.\n");
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