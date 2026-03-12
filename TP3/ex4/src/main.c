#include <stdio.h>

#include "degre.h"

int main(void)
{
    double celsius = 25.0;
    double kelvin = 298.0;
    double fahrenheit = 77.0;

    printf("Tests du module de conversion\n");
    printf("%.2f C -> %.2f K\n", celsius, CelsiusAKelvin(celsius));
    printf("%.2f C -> %.2f F\n", celsius, CelsiusAFahrenheit(celsius));
    printf("%.2f K -> %.2f C\n", kelvin, KelvinACelsius(kelvin));
    printf("%.2f K -> %.2f F\n", kelvin, KelvinAFahrenheit(kelvin));
    printf("%.2f F -> %.2f C\n", fahrenheit, FahrenheitACelsius(fahrenheit));
    printf("%.2f F -> %.2f K\n", fahrenheit, FahrenheitAKelvin(fahrenheit));

    return 0;
}