#include <stdio.h>
#include <stdlib.h>

#include "../../../common/saisie.h"

#define N 5

typedef struct maillon {
    int x;
    struct maillon *suiv;
} maillon;

static void afficher_liste(maillon *tete)
{
    maillon *courant = tete;
    printf("\nContenu de la liste : ");
    while (courant != NULL) {
        printf("[%d] -> ", courant->x);
        courant = courant->suiv;
    }
    printf("NULL\n");
}

static maillon *supprimer_un_maillon(maillon *tete, int numero_a_supprimer)
{
    maillon *courant = tete;
    maillon *precedent = NULL;
    int index = 1;

    while (courant != NULL && index != numero_a_supprimer) {
        precedent = courant;
        courant = courant->suiv;
        index++;
    }

    if (courant != NULL && index == numero_a_supprimer) {
        if (precedent == NULL) {
            tete = courant->suiv;
        } else {
            precedent->suiv = courant->suiv;
        }
        
        printf("Le maillon no %d a ete supprime (valeur = %d).\n", numero_a_supprimer, courant->x);
        free(courant);
    } else {
        printf("Maillon numero %d introuvable.\n", numero_a_supprimer);
    }

    return tete;
}

static void liberer_liste(maillon *tete) {
    maillon *courant = tete;
    while (courant != NULL) {
        maillon *suivant = courant->suiv;
        free(courant);
        courant = suivant;
    }
}

int main(void)
{
    maillon *tete = NULL;
    maillon *courant = NULL;

    printf("Creation d'une liste de %d maillons...\n", N);

    for (int i = 1; i <= N; i++) {
        maillon *nouveau = (maillon *)malloc(sizeof(maillon));
        if (nouveau == NULL) {
            printf("Erreur memoire.\n");
            liberer_liste(tete);
            return 1;
        }
        nouveau->x = i * 10;
        nouveau->suiv = NULL;

        if (tete == NULL) {
            tete = nouveau;
            courant = nouveau;
        } else {
            courant->suiv = nouveau;
            courant = nouveau;
        }
    }

    afficher_liste(tete);

    int numero_a_supprimer;
    do {
        lire_entier("\nEntrez le numero du maillon a supprimer (entre 1 et N) : ", &numero_a_supprimer);
        if (numero_a_supprimer < 1 || numero_a_supprimer > N) {
            printf("Veuillez choisir un index valide!\n");
        }
    } while (numero_a_supprimer < 1 || numero_a_supprimer > N);

    tete = supprimer_un_maillon(tete, numero_a_supprimer);
    afficher_liste(tete);

    liberer_liste(tete);

    return 0;
}
