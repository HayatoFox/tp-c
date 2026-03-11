#include <ctype.h>
#include <stdio.h>

static int est_voyelle(int caractere)
{
    int c = tolower((unsigned char)caractere);

    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

int main(void)
{
    int caractere = 0;
    int nombre_voyelles = 0;

    printf("Entrez un texte termine par # :\n");

    while ((caractere = getchar()) != EOF && caractere != '#') {
        if (est_voyelle(caractere)) {
            ++nombre_voyelles;
        }
    }

    if (caractere == EOF) {
        fprintf(stderr, "Le texte doit se terminer par #.\n");
        return 1;
    }

    printf("Nombre de voyelles : %d\n", nombre_voyelles);
    return 0;
}