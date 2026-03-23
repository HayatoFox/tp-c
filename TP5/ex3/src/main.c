#include <stdio.h>

// Echange de deux valeurs entieres
static void echanger(int *pa, int *pb)
{
    int tmp;
    tmp = *pa;
    *pa = *pb;
    *pb = tmp;
}

// Echange de deux pointeurs d'entiers
static void echangerPointeurs(int **ppa, int **ppb)
{
    int *tmp;
    tmp = *ppa;
    *ppa = *ppb;
    *ppb = tmp;
}

int main(void)
{
    int x = 12;
    int y = 34;

    printf("--- Echange de variables ---\n");
    printf("Avant echange : x = %d ; y = %d\n", x, y);
    echanger(&x, &y);
    printf("Apres echange : x = %d ; y = %d\n\n", x, y);

    int a = 100;
    int b = 200;
    int *pa = &a;
    int *pb = &b;

    printf("--- Echange de pointeurs ---\n");
    printf("Avant echange : pa pointe vers %d ; pb pointe vers %d\n", *pa, *pb);
    echangerPointeurs(&pa, &pb);
    printf("Apres echange : pa pointe vers %d ; pb pointe vers %d\n", *pa, *pb);

    return 0;
}
