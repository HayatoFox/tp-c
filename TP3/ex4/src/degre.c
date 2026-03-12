#include "degre.h"

double CelsiusAKelvin(double temperature)
{
    return temperature + 273.0;
}

double CelsiusAFahrenheit(double temperature)
{
    return (9.0 / 5.0) * temperature + 32.0;
}

double KelvinACelsius(double temperature)
{
    return temperature - 273.0;
}

double KelvinAFahrenheit(double temperature)
{
    return CelsiusAFahrenheit(KelvinACelsius(temperature));
}

double FahrenheitACelsius(double temperature)
{
    return (5.0 / 9.0) * (temperature - 32.0);
}

double FahrenheitAKelvin(double temperature)
{
    return CelsiusAKelvin(FahrenheitACelsius(temperature));
}