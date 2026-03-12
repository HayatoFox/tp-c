#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "../../common/saisie.h"

#define CAPACITE_PERSONNES 20
#define TAILLE_TEXTE 21

typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

typedef struct {
    char nom[TAILLE_TEXTE];
    char prenom[TAILLE_TEXTE];
    Date naissance;
} Personne;

static Personne carnet[CAPACITE_PERSONNES];
static int nombre_personnes = 0;

static void trim_espaces(char *texte)
{
    char *debut = texte;
    size_t longueur = 0;

    while (*debut != '\0' && isspace((unsigned char)*debut)) {
        ++debut;
    }

    if (debut != texte) {
        memmove(texte, debut, strlen(debut) + 1U);
    }

    longueur = strlen(texte);
    while (longueur > 0 && isspace((unsigned char)texte[longueur - 1U])) {
        texte[longueur - 1U] = '\0';
        --longueur;
    }
}

static int chaine_vide(const char *texte)
{
    return texte[0] == '\0';
}

static int annee_bissextile(int annee)
{
    return (annee % 400 == 0) || ((annee % 4 == 0) && (annee % 100 != 0));
}

static int date_valide(Date date)
{
    static const int jours_par_mois[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int max_jours = 0;

    if (date.annee < 1900 || date.annee > 2100) {
        return 0;
    }

    if (date.mois < 1 || date.mois > 12) {
        return 0;
    }

    max_jours = jours_par_mois[date.mois - 1];
    if (date.mois == 2 && annee_bissextile(date.annee) != 0) {
        max_jours = 29;
    }

    return date.jour >= 1 && date.jour <= max_jours;
}

static int lire_texte_non_vide(const char *invite, char *destination, size_t taille)
{
    while (1) {
        if (!saisie_lire_texte(invite, destination, taille, "Texte invalide ou trop long.")) {
            return 0;
        }

        trim_espaces(destination);
        if (!chaine_vide(destination)) {
            return 1;
        }

        printf("Le texte ne doit pas etre vide.\n");
    }
}

static int lire_date(Date *date)
{
    const SaisieOptions options_jour = {SAISIE_ENTIER, 1, 1, 1.0, 31.0, "Jour invalide."};
    const SaisieOptions options_mois = {SAISIE_ENTIER, 1, 1, 1.0, 12.0, "Mois invalide."};
    const SaisieOptions options_annee = {SAISIE_ENTIER, 1, 1, 1900.0, 2100.0, "Annee invalide."};

    while (1) {
        if (!saisie_lire("Jour de naissance   : ", &options_jour, &date->jour)
            || !saisie_lire("Mois de naissance   : ", &options_mois, &date->mois)
            || !saisie_lire("Annee de naissance  : ", &options_annee, &date->annee)) {
            return 0;
        }

        if (date_valide(*date) != 0) {
            return 1;
        }

        printf("La date saisie n'est pas valide.\n");
    }
}

static void afficher_personne(const Personne *personne, int index)
{
    printf("[%d] %s %s - ne(e) le %02d/%02d/%04d\n", index + 1, personne->prenom, personne->nom,
           personne->naissance.jour, personne->naissance.mois, personne->naissance.annee);
}

static void afficher_toutes_les_personnes(void)
{
    if (nombre_personnes == 0) {
        printf("Aucune personne enregistree.\n");
        return;
    }

    for (int index = 0; index < nombre_personnes; ++index) {
        afficher_personne(&carnet[index], index);
    }
}

static int comparer_noms(const char *gauche, const char *droite)
{
    while (*gauche != '\0' && *droite != '\0') {
        int cg = tolower((unsigned char)*gauche);
        int cd = tolower((unsigned char)*droite);

        if (cg != cd) {
            return cg - cd;
        }

        ++gauche;
        ++droite;
    }

    return tolower((unsigned char)*gauche) - tolower((unsigned char)*droite);
}

static int comparer_dates(Date gauche, Date droite)
{
    if (gauche.annee != droite.annee) {
        return gauche.annee - droite.annee;
    }

    if (gauche.mois != droite.mois) {
        return gauche.mois - droite.mois;
    }

    return gauche.jour - droite.jour;
}

static void definir_personne(Personne *personne)
{
    if (!lire_texte_non_vide("Nom    : ", personne->nom, sizeof(personne->nom))
        || !lire_texte_non_vide("Prenom : ", personne->prenom, sizeof(personne->prenom))
        || !lire_date(&personne->naissance)) {
        personne->nom[0] = '\0';
        personne->prenom[0] = '\0';
    }
}

static void ajouter_personne(void)
{
    Personne nouvelle_personne;

    if (nombre_personnes >= CAPACITE_PERSONNES) {
        printf("Carnet plein. Impossible d'ajouter une personne.\n");
        return;
    }

    definir_personne(&nouvelle_personne);
    if (chaine_vide(nouvelle_personne.nom) || chaine_vide(nouvelle_personne.prenom)) {
        printf("Ajout annule suite a une fin de saisie.\n");
        return;
    }

    carnet[nombre_personnes] = nouvelle_personne;
    ++nombre_personnes;
    printf("Personne ajoutee.\n");
}

static void classer_par_date_de_naissance(void)
{
    for (int i = 0; i < nombre_personnes - 1; ++i) {
        for (int j = i + 1; j < nombre_personnes; ++j) {
            if (comparer_dates(carnet[i].naissance, carnet[j].naissance) > 0) {
                Personne temp = carnet[i];
                carnet[i] = carnet[j];
                carnet[j] = temp;
            }
        }
    }

    printf("Carnet trie par date de naissance.\n");
}

static int rechercher_personne_par_nom(const char *nom)
{
    for (int index = 0; index < nombre_personnes; ++index) {
        if (comparer_noms(carnet[index].nom, nom) == 0) {
            return index;
        }
    }

    return -1;
}

static void rechercher_modifier_afficher(void)
{
    char nom_recherche[TAILLE_TEXTE];
    char reponse = '\0';
    int index = -1;
    const SaisieOptions options_reponse = {SAISIE_CARACTERE, 0, 0, 0.0, 0.0, "Reponse invalide."};

    if (nombre_personnes == 0) {
        printf("Aucune personne enregistree.\n");
        return;
    }

    if (!lire_texte_non_vide("Nom a rechercher : ", nom_recherche, sizeof(nom_recherche))) {
        printf("Recherche annulee.\n");
        return;
    }

    index = rechercher_personne_par_nom(nom_recherche);
    if (index < 0) {
        printf("Aucune personne trouvee pour ce nom.\n");
        return;
    }

    afficher_personne(&carnet[index], index);

    if (!saisie_lire("Modifier cette personne ? (o/n) : ", &options_reponse, &reponse)) {
        printf("Modification annulee.\n");
        return;
    }

    if (reponse == 'o' || reponse == 'O') {
        Personne personne_modifiee = carnet[index];

        definir_personne(&personne_modifiee);
        if (chaine_vide(personne_modifiee.nom) || chaine_vide(personne_modifiee.prenom)) {
            printf("Modification annulee suite a une fin de saisie.\n");
            return;
        }

        carnet[index] = personne_modifiee;
        printf("Personne modifiee.\n");
        afficher_personne(&carnet[index], index);
    }
}

static void supprimer_personne(void)
{
    char nom_recherche[TAILLE_TEXTE];
    int index = -1;

    if (nombre_personnes == 0) {
        printf("Aucune personne enregistree.\n");
        return;
    }

    if (!lire_texte_non_vide("Nom a supprimer : ", nom_recherche, sizeof(nom_recherche))) {
        printf("Suppression annulee.\n");
        return;
    }

    index = rechercher_personne_par_nom(nom_recherche);
    if (index < 0) {
        printf("Aucune personne trouvee pour ce nom.\n");
        return;
    }

    for (int position = index; position < nombre_personnes - 1; ++position) {
        carnet[position] = carnet[position + 1];
    }

    --nombre_personnes;
    printf("Personne supprimee.\n");
}

static int lire_choix_menu(void)
{
    int choix = 0;
    const SaisieOptions options_choix = {SAISIE_ENTIER, 1, 1, 0.0, 5.0, "Choix invalide."};

    printf("\nCarnet d'adresses\n");
    printf("1 - Ajouter une personne\n");
    printf("2 - Afficher les personnes\n");
    printf("3 - Trier par date de naissance\n");
    printf("4 - Rechercher / modifier / afficher\n");
    printf("5 - Supprimer une personne\n");
    printf("0 - Quitter\n");

    if (!saisie_lire("Votre choix : ", &options_choix, &choix)) {
        return -1;
    }

    return choix;
}

int main(void)
{
    int choix = 0;

    do {
        choix = lire_choix_menu();
        if (choix < 0) {
            fprintf(stderr, "Fin de saisie inattendue.\n");
            return 1;
        }

        switch (choix) {
        case 1:
            ajouter_personne();
            break;
        case 2:
            afficher_toutes_les_personnes();
            break;
        case 3:
            classer_par_date_de_naissance();
            break;
        case 4:
            rechercher_modifier_afficher();
            break;
        case 5:
            supprimer_personne();
            break;
        case 0:
            break;
        default:
            break;
        }
    } while (choix != 0);

    return 0;
}