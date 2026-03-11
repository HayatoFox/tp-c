#include <stdio.h>

#include "../../common/saisie.h"

#define PI 3.14159

int main(void)
{
    double rayon = 0.0;
    const SaisieOptions options_rayon = {SAISIE_REEL, 1, 0, 0.0, 0.0, "Saisie invalide. Recommencez."};

    if (!saisie_lire("Rayon du cercle : ", &options_rayon, &rayon)) {
        fprintf(stderr, "Fin de saisie inattendue.\n");
        return 1;
    }

    printf("Perimetre : %.5f\n", 2.0 * PI * rayon);
    printf("Surface   : %.5f\n", PI * rayon * rayon);

    return 0;
}