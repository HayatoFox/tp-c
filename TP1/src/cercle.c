#include <stdio.h>
#include "../../common/saisie.h"

#define PI 3.14159

int main(void)
{
    double rayon;

    lire_reel("Rayon du cercle : ", &rayon);

    printf("Perimetre : %.5f\n", 2.0 * PI * rayon);
    printf("Surface   : %.5f\n", PI * rayon * rayon);

    return 0;
}
