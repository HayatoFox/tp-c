#include <math.h>
#include <stdio.h>

int main(void)
{
    int entier = 5 % 2;
    double reste_reel = fmod(5.0, 2.0);

    printf("int X = 5 %% 2           -> %d\n", entier);
    printf("float X = 5.0 %% 2       -> expression invalide en C\n");
    printf("Equivalent avec fmod     -> %.1f\n", reste_reel);

    return 0;
}