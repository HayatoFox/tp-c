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

/*
 * Petite structure de config pour eviter de multiplier les fonctions de saisie.
 * On choisit le type attendu, les bornes si besoin, et le message a afficher.
 */

typedef struct {
    SaisieType type;
    int borne_min_active;
    int borne_max_active;
    double borne_min;
    double borne_max;
    const char *message_erreur;
} SaisieOptions;

/*
 * Verifie qu'apres la valeur lue il ne reste que des espaces ou un retour a la ligne.
 * Ca permet d'accepter "15" ou "15   ".
 */
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

/*
 * Lit une ligne complete dans un buffer.
 *
 * Valeurs de retour :
 *  1  -> lecture normale
 *  0  -> fin de fichier / entree fermee
 * -1  -> la ligne etait trop longue pour le buffer
 */
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

    /*
     * Si on n'a pas lu le '\n', c'est que l'utilisateur a tape trop de caracteres.
     * On vide donc la fin de la ligne pour ne pas casser la prochaine saisie.
     */
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }

    return -1;
}

/*
 * Variante simple pour lire une chaine de caracteres.
 * On reutilise la lecture de ligne, puis on enleve le retour a la ligne final si besoin.
 */
static int saisie_lire_texte(const char *invite, char *buffer, size_t taille, const char *message_erreur)
{
    while (1) {
        int lecture = saisie_lire_ligne(invite, buffer, taille);
        size_t longueur = 0;

        if (lecture == 0) {
            return 0;
        }

        if (lecture < 0) {
            printf("%s\n", message_erreur);
            continue;
        }

        longueur = strlen(buffer);
        if (longueur > 0 && buffer[longueur - 1] == '\n') {
            buffer[longueur - 1] = '\0';
        }

        return 1;
    }
}

/*
 * Teste les bornes seulement si elles ont ete activees.
 * Ca permet d'utiliser la meme fonction aussi bien pour un entier libre
 * que pour une valeur comprise entre deux limites.
 */
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

/*
 * Fonction principale du module.
 *
 * Le principe :
 * 1. on lit une ligne complete
 * 2. on essaie de convertir selon le type demande
 * 3. on verifie qu'il n'y a pas de texte parasite apres la valeur
 * 4. on verifie les bornes si elles existent
 * 5. si tout va bien, on range le resultat dans la variable passee en parametre
 *
 * Retour :
 * 1 si une valeur valide a ete lue
 * 0 si on tombe sur EOF / fin de saisie
 */
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
            /* EOF ou entree fermee */
            return 0;
        }

        if (lecture < 0) {
            /* Ligne trop longue : on affiche l'erreur puis on redemande. */
            printf("%s\n", options->message_erreur);
            continue;
        }

        switch (options->type) {
        case SAISIE_CARACTERE:
            /*
             * Pour un caractere, on saute les espaces au debut.
             * Ensuite on prend le premier vrai caractere trouve.
             */
            position = buffer;
            while (*position != '\0' && isspace((unsigned char)*position)) {
                ++position;
            }

            if (*position == '\0') {
                printf("%s\n", options->message_erreur);
                continue;
            }

            /* On stocke le caractere lu dans la variable fournie par l'appelant. */
            *(char *)resultat = *position;
            ++position;

            /* Si autre chose suit derriere, on considere la saisie invalide. */
            if (saisie_espaces_uniquement(position) == 0) {
                printf("%s\n", options->message_erreur);
                continue;
            }
            return 1;

        case SAISIE_ENTIER:
            /* strtol convertit la chaine en entier et laisse fin sur le premier caractere non lu. */
            entier = strtol(buffer, &fin, 10);
            if (fin == buffer || saisie_espaces_uniquement(fin) == 0 || entier < INT_MIN || entier > INT_MAX) {
                printf("%s\n", options->message_erreur);
                continue;
            }

            /* Si des bornes ont ete demandees, on les verifie ici. */
            if (saisie_valider_bornes((double)entier, options) == 0) {
                printf("%s\n", options->message_erreur);
                continue;
            }

            *(int *)resultat = (int)entier;
            return 1;

        case SAISIE_REEL:
            /* Meme principe qu'au-dessus, mais pour les valeurs reelles. */
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

static void lire_entier(const char *invite, int *resultat)
{
    SaisieOptions opt = {SAISIE_ENTIER, 0, 0, 0.0, 0.0, "Saisie invalide, veuillez recommencer."};
    if (!saisie_lire(invite, &opt, resultat)) {
        exit(1);
    }
}

static void lire_reel(const char *invite, double *resultat)
{
    SaisieOptions opt = {SAISIE_REEL, 0, 0, 0.0, 0.0, "Saisie invalide, veuillez recommencer."};
    if (!saisie_lire(invite, &opt, resultat)) {
        exit(1);
    }
}

static void lire_caractere(const char *invite, char *resultat)
{
    SaisieOptions opt = {SAISIE_CARACTERE, 0, 0, 0.0, 0.0, "Saisie invalide, veuillez recommencer."};
    if (!saisie_lire(invite, &opt, resultat)) {
        exit(1);
    }
}

#endif 