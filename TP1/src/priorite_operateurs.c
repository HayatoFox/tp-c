#include <stdio.h>

int main(void)
{
    int x1 = -3 + 4 * 5 - 6;
    int x2 = (-3 + 4) * 5 - 6;
    int x3 = -3 + (4 * 5) - 6;
    int x4 = -3 + 4 * (5 - 6);

    printf("X = -3 + 4 * 5 - 6      -> %d\n", x1);
    printf("X = (-3 + 4) * 5 - 6    -> %d\n", x2);
    printf("X = -3 + (4 * 5) - 6    -> %d\n", x3);
    printf("X = -3 + 4 * (5 - 6)    -> %d\n", x4);

    return 0;
}