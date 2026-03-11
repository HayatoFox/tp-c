#include <stdio.h>

static int lire_operation(char *operation)
{
    printf("Operation (+, -, *, /, s pour sortir) : ");
    return scanf(" %c", operation);
}

static int lire_operandes(double *gauche, double *droite)
{
    printf("Premier operande : ");
    if (scanf("%lf", gauche) != 1) {
        return 0;
    }

    printf("Second operande : ");
    return scanf("%lf", droite) == 1;
}

int main(void)
{
    char operation = '\0';

    while (1) {
        double gauche = 0.0;
        double droite = 0.0;
        double resultat = 0.0;

        if (lire_operation(&operation) != 1) {
            fprintf(stderr, "Saisie invalide.\n");
            return 1;
        }

        if (operation == 's') {
            break;
        }

        if (!lire_operandes(&gauche, &droite)) {
            fprintf(stderr, "Operande invalide.\n");
            return 1;
        }

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