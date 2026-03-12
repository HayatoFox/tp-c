#include <stdio.h>

#include "../../common/saisie.h"
#include "degre.h"

static int lireChoix(void)
{
    int choix = 0;
    const SaisieOptions options_choix = {SAISIE_ENTIER, 1, 1, 0.0, 6.0, "Choix invalide."};

    printf("\nConversions disponibles :\n");
    printf("1 - Celsius vers Kelvin\n");
    printf("2 - Celsius vers Fahrenheit\n");
    printf("3 - Kelvin vers Celsius\n");
    printf("4 - Kelvin vers Fahrenheit\n");
    printf("5 - Fahrenheit vers Celsius\n");
    printf("6 - Fahrenheit vers Kelvin\n");
    printf("0 - Quitter\n");

    if (!saisie_lire("Votre choix : ", &options_choix, &choix)) {
        return -1;
    }

    return choix;
}

static void executerChoix(int choix)
{
    double temperature = 0.0;
    double resultat = 0.0;
    const SaisieOptions options_temperature = {SAISIE_REEL, 0, 0, 0.0, 0.0, "Entrez une temperature valide."};

    if (!saisie_lire("Temperature a convertir : ", &options_temperature, &temperature)) {
        printf("Fin de saisie inattendue.\n");
        return;
    }

    switch (choix) {
    case 1:
        resultat = CelsiusAKelvin(temperature);
        printf("%.2f C = %.2f K\n", temperature, resultat);
        break;
    case 2:
        resultat = CelsiusAFahrenheit(temperature);
        printf("%.2f C = %.2f F\n", temperature, resultat);
        break;
    case 3:
        resultat = KelvinACelsius(temperature);
        printf("%.2f K = %.2f C\n", temperature, resultat);
        break;
    case 4:
        resultat = KelvinAFahrenheit(temperature);
        printf("%.2f K = %.2f F\n", temperature, resultat);
        break;
    case 5:
        resultat = FahrenheitACelsius(temperature);
        printf("%.2f F = %.2f C\n", temperature, resultat);
        break;
    case 6:
        resultat = FahrenheitAKelvin(temperature);
        printf("%.2f F = %.2f K\n", temperature, resultat);
        break;
    default:
        break;
    }
}

int main(void)
{
    int choix = 0;

    do {
        choix = lireChoix();
        if (choix < 0) {
            fprintf(stderr, "Fin de saisie inattendue.\n");
            return 1;
        }

        if (choix != 0) {
            executerChoix(choix);
        }
    } while (choix != 0);

    return 0;
}