#include <stdio.h>

int main(void)
{
    float x_float_from_int_division = (float)(10 / 3);
    int x_int = 10 / 3;
    float x1 = 10.0f / 3.0f;
    float x2 = 10.0f / 3.0f;
    float x3 = (float)10 / 3.0f;
    float x4 = ((float)10) / 3.0f;

    printf("float X = 10 / 3         -> %.6f\n", x_float_from_int_division);
    printf("int   X = 10 / 3         -> %d\n", x_int);
    printf("float X = 10.0 / 3       -> %.6f\n", x1);
    printf("float X = 10.0 / 3.0     -> %.6f\n", x2);
    printf("float X = (float)10 / 3  -> %.6f\n", x3);
    printf("float X = ((float)10)/3  -> %.1f puis %.5f\n", x4, x4);

    return 0;
}