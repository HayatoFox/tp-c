#include <limits.h>
#include <stdio.h>

#include "../../common/saisie.h"

static void afficher_ligne(int espaces, int etoiles)
{
    for (int i = 0; i < espaces; ++i) {
        putchar(' ');
    }

    for (int i = 0; i < etoiles; ++i) {
        putchar('*');
    }

    putchar('\n');
}

static void motif_1(int n)
{
    for (int ligne = 0; ligne < n; ++ligne) {
        afficher_ligne(0, n);
    }
}

static void motif_2(int n)
{
    for (int ligne = 1; ligne <= n; ++ligne) {
        afficher_ligne(0, ligne);
    }

    for (int ligne = n - 1; ligne >= 1; --ligne) {
        afficher_ligne(0, ligne);
    }
}

static void motif_3(int n)
{
    for (int ligne = 1; ligne <= n; ++ligne) {
        afficher_ligne(n - ligne, ligne);
    }

    for (int ligne = n - 1; ligne >= 1; --ligne) {
        afficher_ligne(n - ligne, ligne);
    }
}

static void motif_4(int n)
{
    for (int ligne = 1; ligne <= n; ++ligne) {
        afficher_ligne(n - ligne, 2 * ligne - 1);
    }
}

static void motif_5(int n)
{
    for (int ligne = 1; ligne <= n; ++ligne) {
        afficher_ligne(n - ligne, 2 * ligne - 1);
    }

    for (int ligne = n - 1; ligne >= 1; --ligne) {
        afficher_ligne(n - ligne, 2 * ligne - 1);
    }
}

int main(void)
{
    int n = 0;
    int choix = -1;
    const SaisieOptions options_n = {SAISIE_ENTIER, 1, 1, 1.0, 20.0, "N doit etre compris entre 1 et 20."};
    const SaisieOptions options_choix = {SAISIE_ENTIER, 1, 1, 0.0, 5.0, "Choix invalide."};

    if (!saisie_lire("Entrez N (1..20) : ", &options_n, &n)) {
        fprintf(stderr, "Fin de saisie inattendue.\n");
        return 1;
    }

    while (choix != 0) {
        printf("\nChoisissez un motif :\n");
        printf("1 - Carre\n");
        printf("2 - Triangle gauche complet\n");
        printf("3 - Triangle droit complet\n");
        printf("4 - Pyramide\n");
        printf("5 - Losange\n");
        printf("0 - Quitter\n");

        if (!saisie_lire("Votre choix : ", &options_choix, &choix)) {
            fprintf(stderr, "Fin de saisie inattendue.\n");
            return 1;
        }

        switch (choix) {
        case 1:
            motif_1(n);
            break;
        case 2:
            motif_2(n);
            break;
        case 3:
            motif_3(n);
            break;
        case 4:
            motif_4(n);
            break;
        case 5:
            motif_5(n);
            break;
        case 0:
            break;
        }
    }

    return 0;
}