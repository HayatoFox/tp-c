#include <math.h>
#include <stdio.h>

#include "../../common/saisie.h"

static int comparer_entiers_en_int(int gauche, int droite)
{
    return gauche == droite ? 1 : 0;
}

static char comparer_entiers_en_char(int gauche, int droite)
{
    return gauche == droite ? 'V' : 'F';
}

static int comparer_flottants_en_int(double gauche, double droite)
{
    return fabs(gauche - droite) < 1e-9 ? 1 : 0;
}

static char comparer_flottants_en_char(double gauche, double droite)
{
    return fabs(gauche - droite) < 1e-9 ? 'V' : 'F';
}

int main(void)
{
    int entier_1 = 0;
    int entier_2 = 0;
    double flottant_1 = 0.0;
    double flottant_2 = 0.0;
    const SaisieOptions options_entier = {SAISIE_ENTIER, 0, 0, 0.0, 0.0, "Entrez un entier valide."};
    const SaisieOptions options_reel = {SAISIE_REEL, 0, 0, 0.0, 0.0, "Entrez un reel valide."};

    if (!saisie_lire("Premier entier  : ", &options_entier, &entier_1)
        || !saisie_lire("Second entier   : ", &options_entier, &entier_2)
        || !saisie_lire("Premier flottant: ", &options_reel, &flottant_1)
        || !saisie_lire("Second flottant : ", &options_reel, &flottant_2)) {
        fprintf(stderr, "Fin de saisie inattendue.\n");
        return 1;
    }

    printf("Comparaison entiers -> int  : %d\n", comparer_entiers_en_int(entier_1, entier_2));
    printf("Comparaison entiers -> char : %c\n", comparer_entiers_en_char(entier_1, entier_2));
    printf("Comparaison flottants -> int  : %d\n", comparer_flottants_en_int(flottant_1, flottant_2));
    printf("Comparaison flottants -> char : %c\n", comparer_flottants_en_char(flottant_1, flottant_2));

    return 0;
}