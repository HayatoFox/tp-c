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

static void trier_minima_successifs(int tableau[N])
{
    for (int i = 0; i < N - 1; ++i) {
        int indice_min = i;
        for (int j = i + 1; j < N; ++j) {
            if (tableau[j] < tableau[indice_min]) {
                indice_min = j;
            }
        }

        if (indice_min != i) {
            int temp = tableau[i];
            tableau[i] = tableau[indice_min];
            tableau[indice_min] = temp;
        }
    }
}

int main(void)
{
    int tableau[N];

    srand((unsigned int)time(NULL));
    initialiser_tableau(tableau);
    afficher_tableau(tableau, "Tableau initial :");
    trier_minima_successifs(tableau);
    afficher_tableau(tableau, "Tableau trie (minima successifs) :");

    return 0;
}