#include <stdio.h>

int main(void)
{
    int i, j, k, tmp;
    int *pi, *pj, *pk, *ptmp;

    i = 31;
    j = 52;
    k = 17;

    pi = &i;
    pj = &j;
    pk = &k;

    printf("i=%d j=%d k=%d\n", i, j, k);
    printf("*pi=%d *pj=%d *pk=%d\n\n", *pi, *pj, *pk);

    // Echange des valeurs via les pointeurs
    tmp = *pi;
    *pi = *pj;
    *pj = *pk;
    *pk = tmp;

    printf("i=%d j=%d k=%d\n", i, j, k);
    printf("*pi=%d *pj=%d *pk=%d\n\n", *pi, *pj, *pk);

    // Echange des adresses des pointeurs
    ptmp = pi;
    pi = pj;
    pj = pk;
    pk = ptmp;

    printf("i=%d j=%d k=%d\n", i, j, k);
    printf("*pi=%d *pj=%d *pk=%d\n", *pi, *pj, *pk);

    return 0;
}
