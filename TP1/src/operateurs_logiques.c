#include <stdio.h>

int main(void)
{
    int a = 5;
    int b = 6;
    int xor_booleen = (a != 0) != (b != 0);

    printf("5 & 6   -> %d\n", a & b);
    printf("5 && 6  -> %d\n", a && b);
    printf("5 | 6   -> %d\n", a | b);
    printf("5 || 6  -> %d\n", a || b);
    printf("5 ^ 6   -> %d\n", a ^ b);
    printf("5 ^^ 6  -> operateur inexistant en C, XOR booleen = %d\n", xor_booleen);
    printf("~5      -> %d\n", ~a);
    printf("!5      -> %d\n", !a);

    return 0;
}