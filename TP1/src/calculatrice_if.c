#include <stdio.h>
#include "../../common/saisie.h"

int main(void)
{
    char operation;

    while (1) {
        double gauche = 0.0;
        double droite = 0.0;
        double resultat = 0.0;

        lire_caractere("Operation (+, -, *, /, s pour sortir) : ", &operation);

        if (operation == 's') {
            break;
        }

        lire_reel("Premier operande : ", &gauche);
        lire_reel("Second operande : ", &droite);

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
