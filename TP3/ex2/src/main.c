#include <limits.h>
#include <stdio.h>

#include "../../common/saisie.h"

static long long convertir_en_secondes(int heures, int minutes, int secondes)
{
    return (long long)heures * 3600LL + (long long)minutes * 60LL + (long long)secondes;
}

int main(void)
{
    int heures = 0;
    int minutes = 0;
    int secondes = 0;
    const SaisieOptions options_heures = {SAISIE_ENTIER, 1, 1, 0.0, (double)INT_MAX, "Entrez un entier positif ou nul."};
    const SaisieOptions options_minutes = {SAISIE_ENTIER, 1, 1, 0.0, 59.0, "Entrez une valeur entre 0 et 59."};
    const SaisieOptions options_secondes = {SAISIE_ENTIER, 1, 1, 0.0, 59.0, "Entrez une valeur entre 0 et 59."};

    if (!saisie_lire("Heures   : ", &options_heures, &heures)
        || !saisie_lire("Minutes  : ", &options_minutes, &minutes)
        || !saisie_lire("Secondes : ", &options_secondes, &secondes)) {
        fprintf(stderr, "Fin de saisie inattendue.\n");
        return 1;
    }

    printf("%d h %d min %d s = %lld secondes\n", heures, minutes, secondes,
           convertir_en_secondes(heures, minutes, secondes));
    return 0;
}