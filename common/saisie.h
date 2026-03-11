#ifndef SAISIE_H
#define SAISIE_H

#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    SAISIE_CARACTERE,
    SAISIE_ENTIER,
    SAISIE_REEL
} SaisieType;

typedef struct {
    SaisieType type;
    int borne_min_active;
    int borne_max_active;
    double borne_min;
    double borne_max;
    const char *message_erreur;
} SaisieOptions;

static int saisie_espaces_uniquement(const char *texte)
{
    while (*texte != '\0') {
        if (!isspace((unsigned char)*texte)) {
            return 0;
        }
        ++texte;
    }

    return 1;
}

static int saisie_lire_ligne(const char *invite, char *buffer, size_t taille)
{
    int caractere = 0;
    size_t longueur = 0;

    printf("%s", invite);

    if (fgets(buffer, taille, stdin) == NULL) {
        return 0;
    }

    longueur = strlen(buffer);
    if (longueur > 0 && buffer[longueur - 1] == '\n') {
        return 1;
    }

    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }

    return -1;
}

static int saisie_valider_bornes(double valeur, const SaisieOptions *options)
{
    if (options->borne_min_active != 0 && valeur < options->borne_min) {
        return 0;
    }

    if (options->borne_max_active != 0 && valeur > options->borne_max) {
        return 0;
    }

    return 1;
}

static int saisie_lire(const char *invite, const SaisieOptions *options, void *resultat)
{
    char buffer[128];
    char *fin = NULL;
    char *position = NULL;
    long entier = 0;
    double reel = 0.0;

    while (1) {
        int lecture = saisie_lire_ligne(invite, buffer, sizeof(buffer));

        if (lecture == 0) {
            return 0;
        }

        if (lecture < 0) {
            printf("%s\n", options->message_erreur);
            continue;
        }

        switch (options->type) {
        case SAISIE_CARACTERE:
            position = buffer;
            while (*position != '\0' && isspace((unsigned char)*position)) {
                ++position;
            }

            if (*position == '\0') {
                printf("%s\n", options->message_erreur);
                continue;
            }

            *(char *)resultat = *position;
            ++position;
            if (saisie_espaces_uniquement(position) == 0) {
                printf("%s\n", options->message_erreur);
                continue;
            }
            return 1;

        case SAISIE_ENTIER:
            entier = strtol(buffer, &fin, 10);
            if (fin == buffer || saisie_espaces_uniquement(fin) == 0 || entier < INT_MIN || entier > INT_MAX) {
                printf("%s\n", options->message_erreur);
                continue;
            }

            if (saisie_valider_bornes((double)entier, options) == 0) {
                printf("%s\n", options->message_erreur);
                continue;
            }

            *(int *)resultat = (int)entier;
            return 1;

        case SAISIE_REEL:
            reel = strtod(buffer, &fin);
            if (fin == buffer || saisie_espaces_uniquement(fin) == 0 || !isfinite(reel)) {
                printf("%s\n", options->message_erreur);
                continue;
            }

            if (saisie_valider_bornes(reel, options) == 0) {
                printf("%s\n", options->message_erreur);
                continue;
            }

            *(double *)resultat = reel;
            return 1;

        default:
            return 0;
        }
    }
}

#endif