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

        switch (operation) {
        case '+':
            resultat = gauche + droite;
            break;
        case '-':
            resultat = gauche - droite;
            break;
        case '*':
            resultat = gauche * droite;
            break;
        case '/':
            if (droite == 0.0) {
                printf("Erreur : division par zero.\n");
                continue;
            }
            resultat = gauche / droite;
            break;
        default:
            printf("Erreur : operation inconnue.\n");
            continue;
        }

        printf("Resultat : %.5f\n", resultat);
    }

    return 0;
}
