#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 30
#define MAX_VALEUR 50

static void initialiser_tableau(int tableau[N])
{
    for (int i = 0; i < N; ++i) {
        tableau[i] = rand() % (MAX_VALEUR + 1);
    }
}

static void afficher_tableau(const int tableau[N], const char *titre)
{
    printf("%s\n", titre);
    for (int i = 0; i < N; ++i) {
        printf("%d ", tableau[i]);
    }
    putchar('\n');
}

static void trier_insertion(const int source[N], int destination[N])
{
    destination[0] = source[0];

    for (int i = 1; i < N; ++i) {
        int valeur = source[i];
        int j = i - 1;

        while (j >= 0 && destination[j] > valeur) {
            destination[j + 1] = destination[j];
            --j;
        }

        destination[j + 1] = valeur;
    }
}

int main(void)
{
    int tableau[N];
    int tableau_trie[N];

    srand((unsigned int)time(NULL));
    initialiser_tableau(tableau);
    afficher_tableau(tableau, "Tableau initial :");
    trier_insertion(tableau, tableau_trie);
    afficher_tableau(tableau_trie, "Tableau trie (insertion) :");

    return 0;
}