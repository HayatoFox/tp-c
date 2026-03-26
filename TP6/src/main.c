#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../common/saisie.h"

#define TAILLE_TEXTE 50

typedef struct Personne {
    char nom[TAILLE_TEXTE];
    char prenom[TAILLE_TEXTE];
    int badge;
    int code_secret;
    long long date_dernier_passage; /* Sauvegardable facilement */

    struct Personne *precedent;
    struct Personne *suivant;
} Personne;

static void afficher_liste(Personne *tete)
{
    Personne *courant = tete;

    if (courant == NULL) {
        printf("\nLa liste est vide.\n");
        return;
    }

    printf("\n--- Liste des personnes enregistrees ---\n");
    while (courant != NULL) {
        printf("Badge: %04d | Nom: %s %s", courant->badge, courant->prenom, courant->nom);
        
        if (courant->date_dernier_passage != 0) {
            time_t t = (time_t)courant->date_dernier_passage;
            printf(" | Dernier passage: %s", ctime(&t));
        } else {
            printf(" | Aucun passage enregistre.\n");
        }
        
        courant = courant->suivant;
    }
}

static Personne* ajouter_personne(Personne *tete)
{
    Personne *nouveau = (Personne *)malloc(sizeof(Personne));
    if (nouveau == NULL) {
        printf("Erreur d'allocation memoire.\n");
        return tete;
    }

    nouveau->precedent = NULL;
    nouveau->suivant = NULL;
    nouveau->date_dernier_passage = 0;

    lire_texte("Nom : ", nouveau->nom, TAILLE_TEXTE);
    lire_texte("Prenom : ", nouveau->prenom, TAILLE_TEXTE);

    do {
        lire_entier("Numero de badge (4 chiffres, ex: 1234) : ", &nouveau->badge);
        if (nouveau->badge < 0 || nouveau->badge > 9999) {
            printf("Le numero de badge doit etre compose de 4 chiffres au maximum.\n");
        }
    } while (nouveau->badge < 0 || nouveau->badge > 9999);

    lire_entier("Code secret : ", &nouveau->code_secret);

    /* Insertion en tete de liste pour simplifier */
    if (tete == NULL) {
        return nouveau;
    } else {
        nouveau->suivant = tete;
        tete->precedent = nouveau;
        return nouveau;
    }
}

static Personne* supprimer_personne(Personne *tete)
{
    int badge_suppr;
    Personne *courant = tete;

    if (tete == NULL) {
        printf("La liste est deja vide.\n");
        return NULL;
    }

    lire_entier("Entrez le numero de badge a supprimer : ", &badge_suppr);

    while (courant != NULL && courant->badge != badge_suppr) {
        courant = courant->suivant;
    }

    if (courant == NULL) {
        printf("Badge %04d introuvable.\n", badge_suppr);
        return tete;
    }

    /* Le maillon a ete trouve, on relie le precedent et le suivant */
    if (courant->precedent != NULL) {
        courant->precedent->suivant = courant->suivant;
    } else {
        /* On supprime la tete */
        tete = courant->suivant;
    }

    if (courant->suivant != NULL) {
        courant->suivant->precedent = courant->precedent;
    }

    free(courant);
    printf("Personne avec le badge %04d supprimee avec succes.\n", badge_suppr);

    return tete;
}

static void modifier_code_secret(Personne *tete)
{
    int badge_recherche;
    Personne *courant = tete;

    lire_entier("Entrez le numero de badge de la personne : ", &badge_recherche);

    while (courant != NULL && courant->badge != badge_recherche) {
        courant = courant->suivant;
    }

    if (courant == NULL) {
        printf("Badge %04d introuvable.\n", badge_recherche);
        return;
    }

    printf("Modification du code secret de %s %s.\n", courant->prenom, courant->nom);
    lire_entier("Nouveau code secret : ", &courant->code_secret);
    printf("Code modifie avec succes.\n");
}

static void simuler_controle(Personne *tete)
{
    int badge_essai;
    int code_essai;
    Personne *courant = tete;

    lire_entier("Badge (Control d'acces) : ", &badge_essai);

    while (courant != NULL && courant->badge != badge_essai) {
        courant = courant->suivant;
    }

    if (courant == NULL) {
        printf("Acces refuse (Badge inconnu).\n");
        return;
    }

    lire_entier("Code secret : ", &code_essai);

    if (courant->code_secret == code_essai) {
        time_t t = time(NULL);
        courant->date_dernier_passage = (long long)t;
        printf("Acces autorise. Bienvenue %s %s.\n", courant->prenom, courant->nom);
        printf("Passage enregistre le : %s", ctime(&t));
    } else {
        printf("Acces refuse (Code incorrect).\n");
    }
}

static void sauvegarder_liste(Personne *tete)
{
    FILE *f = fopen("acces.txt", "w");
    Personne *courant = tete;

    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
        return;
    }

    while (courant != NULL) {
        fprintf(f, "%d %d %lld %s\n%s\n", 
                courant->badge, 
                courant->code_secret, 
                courant->date_dernier_passage, 
                courant->prenom, 
                courant->nom);
        courant = courant->suivant;
    }

    fclose(f);
    printf("Liste sauvegardee dans 'acces.txt'.\n");
}

static Personne* charger_liste(Personne *tete)
{
    FILE *f = fopen("acces.txt", "r");
    if (f == NULL) {
        printf("Aucun fichier 'acces.txt' trouve ou erreur de lecture.\n");
        return tete;
    }

    /* Vider la liste actuelle avant de charger */
    while (tete != NULL) {
        Personne *suivant = tete->suivant;
        free(tete);
        tete = suivant;
    }

    Personne *dernier = NULL;

    while (1) {
        Personne *nouveau = (Personne *)malloc(sizeof(Personne));
        if (nouveau == NULL) {
            break;
        }

        /* 1. On lit les 3 nombres. L'espace à la fin du format est crucial : 
           il consomme les espaces ou le saut de ligne restants avant le prénom */
        if (fscanf(f, "%d %d %lld ", 
            &nouveau->badge, 
            &nouveau->code_secret, 
            &nouveau->date_dernier_passage) != 3) {
            
            free(nouveau);
            break;
        }

        /* 2. Lire le prénom (jusqu'à la fin de la ligne, gère les espaces) */
        if (fgets(nouveau->prenom, TAILLE_TEXTE, f) == NULL) {
            free(nouveau);
            break;
        }
        size_t len_p = strlen(nouveau->prenom);
        if (len_p > 0 && nouveau->prenom[len_p - 1] == '\n') {
            nouveau->prenom[len_p - 1] = '\0';
        }

        /* 3. Lire le nom (ligne suivante, gère les espaces) */
        if (fgets(nouveau->nom, TAILLE_TEXTE, f) == NULL) {
            free(nouveau);
            break;
        }
        size_t len_n = strlen(nouveau->nom);
        if (len_n > 0 && nouveau->nom[len_n - 1] == '\n') {
            nouveau->nom[len_n - 1] = '\0';
        }

        /* 4. Chainage du nouveau maillon */
        nouveau->suivant = NULL;
        nouveau->precedent = dernier;

        if (tete == NULL) {
            tete = nouveau;
        } else {
            dernier->suivant = nouveau;
        }
        dernier = nouveau;
    }

    fclose(f);
    printf("Liste chargee depuis 'acces.txt'.\n");
    return tete;
}

static void liberer_toute_la_liste(Personne *tete)
{
    Personne *courant = tete;
    while (courant != NULL) {
        Personne *suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }
}

int main(void)
{
    Personne *tete = NULL;
    int choix = -1;

    while (choix != 0) {
        printf("\n=== MENU CONTROLE D'ACCES ===\n");
        printf("1 - Afficher la liste des personnes\n");
        printf("2 - Ajouter une personne\n");
        printf("3 - Supprimer une personne\n");
        printf("4 - Modifier le code secret d'une personne\n");
        printf("5 - Simuler le controle d'acces (badge + code)\n");
        printf("6 - Sauvegarder la liste dans un fichier\n");
        printf("7 - Charger la liste depuis un fichier\n");
        printf("0 - Quitter\n");
        
        lire_entier("Votre choix : ", &choix);

        switch (choix) {
        case 1:
            afficher_liste(tete);
            break;
        case 2:
            tete = ajouter_personne(tete);
            break;
        case 3:
            tete = supprimer_personne(tete);
            break;
        case 4:
            modifier_code_secret(tete);
            break;
        case 5:
            simuler_controle(tete);
            break;
        case 6:
            sauvegarder_liste(tete);
            break;
        case 7:
            tete = charger_liste(tete);
            break;
        case 0:
            printf("Fermeture du programme.\n");
            break;
        default:
            printf("Choix invalide.\n");
            break;
        }
    }

    liberer_toute_la_liste(tete);

    return 0;
}
