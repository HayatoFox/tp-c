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

static void trier_bulles(int tableau[N])
{
    int permutation = 1;

    while (permutation != 0) {
        permutation = 0;
        for (int i = 0; i < N - 1; ++i) {
            if (tableau[i] > tableau[i + 1]) {
                int temp = tableau[i];
                tableau[i] = tableau[i + 1];
                tableau[i + 1] = temp;
                permutation = 1;
            }
        }
    }
}

int main(void)
{
    int tableau[N];

    srand((unsigned int)time(NULL));
    initialiser_tableau(tableau);
    afficher_tableau(tableau, "Tableau initial :");
    trier_bulles(tableau);
    afficher_tableau(tableau, "Tableau trie (bulles) :");

    return 0;
}