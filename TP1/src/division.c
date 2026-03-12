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
//On obtient les résultats suivants :
//X (float) = 3.000000
//Car on fait la division avec 10 et 3 entier donc le resiltat et 3 stocké en 3.0 pour le float et par defaut %f affiche 6 chiffres apres la virgule doonc 3.000000
//X (int) = 3
//Car on affiche la partie entière de X=3.0 qui est 3
//X (float) = 3.333333
// Cette fois on annonce 10.0 qui est un flotant le resultat de la division devient donc un float et non plus un entier, le resultat de la division est 3.333333333... mais par defaut %f affiche 6 chiffres apres la virgule doonc 3.333333
//X (float) = 3.333333
//Même résultat que la ligne précédente car les deux sont des flottants
//X (float) = 3.333333
//Même résultat que la ligne précédente car on a converti 10 en float avant de faire la division
//X (float) = 3.333333
//La difference entre  X = (float) 10 / 3; et  X = ((float) 10) / 3; est que dans le premier cas on convertit 10 en float avant de faire la division, tandis que dans le second cas on convertit 10 en float après la division. Cependant, dans les deux cas, le résultat final est le même car la division est effectuée avec des flottants.
//X (float) = 3.3
//En utilisant %.1f, on affiche seulement 1 chiffre après la virgule, donc le résultat est arrondi à 3.3
//X (float) = 3.33333
//En utilisant %.5f, on affiche 5 chiffres après la virgule, donc le résultat est arrondi à 3.33333
