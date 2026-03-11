#include <math.h>
#include <stdio.h>

#include "../../common/saisie.h"

int main(void)
{
    char operation = '\0';
    const SaisieOptions options_operation = {SAISIE_CARACTERE, 0, 0, 0.0, 0.0, "Operation invalide."};
    const SaisieOptions options_reel = {SAISIE_REEL, 0, 0, 0.0, 0.0, "Operande invalide."};

    while (1) {
        double gauche = 0.0;
        double droite = 0.0;
        double resultat = 0.0;

        if (!saisie_lire("Operation (+, -, *, /, s pour sortir) : ", &options_operation, &operation)) {
            break;
        }

        if (operation == 's') {
            break;
        }

        if (!saisie_lire("Premier operande : ", &options_reel, &gauche)
            || !saisie_lire("Second operande : ", &options_reel, &droite)) {
            fprintf(stderr, "Fin de saisie inattendue.\n");
            return 1;
        }

        if (operation == '+') {
            resultat = gauche + droite;
        } else if (operation == '-') {
            resultat = gauche - droite;
        } else if (operation == '*') {
            resultat = gauche * droite;
        } else if (operation == '/') {
            if (droite == 0.0) {
                printf("Erreur : division par zero.\n");
                continue;
            }
            resultat = gauche / droite;
        } else {
            printf("Erreur : operation inconnue.\n");
            continue;
        }

        printf("Resultat : %.5f\n", resultat);
    }

    return 0;
}