#include <stdio.h>
#include "../../common/saisie.h"

int main(void)
{
    int a;
    int b;

    lire_entier("a : ", &a);
    lire_entier("b : ", &b);

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
