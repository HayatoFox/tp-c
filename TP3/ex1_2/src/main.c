#include <stdio.h>

static void affiche_hello(void);

int main(void)
{
    affiche_hello();
    return 0;
}

static void affiche_hello(void)
{
    puts("Hello world");
}