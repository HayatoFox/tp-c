#include <stdio.h>
#include <ctype.h>

int main(void)
{
    int caractere;
    int nombre_voyelles = 0;

    printf("Entrez un texte termine par # :\n");

    while ((caractere = getchar()) != EOF && caractere != '#') {
        int c = tolower((unsigned char)caractere);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y') {
            ++nombre_voyelles;
        }
    }

    if (caractere == EOF) {
        printf("Attention : Le texte ne s'est pas termine par #.\n");
    }

    printf("Nombre de voyelles : %d\n", nombre_voyelles);
    return 0;
}
