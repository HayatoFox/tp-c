#include <stdio.h>

#define N 5

int main(void)
{
    // 1 - Adresses de variables simples
    int i = 5;
    int j = 12;

    printf("La variable i est situee a l'adresse %p et vaut %d\n", (void *)&i, i);
    printf("La variable j est situee a l'adresse %p et vaut %d\n\n", (void *)&j, j);

    // 2 - Adresses d'elements d'un tableau
    int t[N] = {10, 20, 30, 40, 50};
    printf("--- Tableau int ---\n");
    for (int k = 0; k < N; k++) {
        printf("t[%d] = %d ; &t[%d] = %p\n", k, t[k], k, (void *)&t[k]);
    }

    // 3 - Essais avec d'autres types (short, double)
    short int t_short[N] = {10, 20, 30, 40, 50};
    printf("\n--- Tableau short int ---\n");
    for (int k = 0; k < N; k++) {
        printf("t_short[%d] = %d ; &t_short[%d] = %p\n", k, t_short[k], k, (void *)&t_short[k]);
    }

    double t_double[N] = {10.0, 20.0, 30.0, 40.0, 50.0};
    printf("\n--- Tableau double ---\n");
    for (int k = 0; k < N; k++) {
        printf("t_double[%d] = %.1f ; &t_double[%d] = %p\n", k, t_double[k], k, (void *)&t_double[k]);
    }

    return 0;
}
