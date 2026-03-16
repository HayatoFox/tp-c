#include <stdio.h>
#include "../../common/saisie.h"

int main(void)
{
    long long a;
    long long b;

    lire_entier_long("a : ", &a);
    lire_entier_long("b : ", &b);

    if (a <= 0 || b <= 0) {
        printf("Veuillez entrer des nombres strictement positifs.\n");
        return 1;
    }

    while (a != b) {
        if (a > b) {
            a -= b;
        } else {
            b -= a;
        }
    }

    printf("PGCD = %lld\n", a);
    return 0;
}
