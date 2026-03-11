#include <stdio.h>

#define PI 3.14159

int main(void)
{
    double rayon = 0.0;

    printf("Rayon du cercle : ");
    if (scanf("%lf", &rayon) != 1) {
        fprintf(stderr, "Saisie invalide.\n");
        return 1;
    }

    if (rayon < 0.0) {
        fprintf(stderr, "Le rayon doit etre positif ou nul.\n");
        return 1;
    }

    printf("Perimetre : %.5f\n", 2.0 * PI * rayon);
    printf("Surface   : %.5f\n", PI * rayon * rayon);

    return 0;
}