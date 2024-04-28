/*
    example on how to do basic arithmetic operations on uncertain numbers

    find the dewpoint based on temperature and relative humidity
    then estimate the probability of condensation on a surface with known temperature
*/

#include "uncertain.h"
#include <stdio.h>

int main() {
    uncertainNumber temperature = uncertain_createWithInterval(22.0, 20.0, 24.0, 0.99);
    uncertainNumber humidity = uncertain_createWithInterval(55.0, 45.0, 65.0, 0.90);

    uncertainNumber surfacetemperature = uncertain_createWithInterval(16.0, 14.0, 18.0, 0.99);

    //simple approximation:   dp = temperature - ((100 - humidity) / 5);
    uncertainNumber temp = uncertain_createWithSD(100.0, 0.0);
    temp = uncertain_difference(temp, humidity);
    temp = uncertain_fraction(temp, uncertain_createWithSD(5.0, 0.0));
    uncertainNumber dp = uncertain_difference(temperature, temp);

    printf("temperature: value = %f, std_dev = %f, 95%% bounds: [%f %f]\n",
        uncertain_getValue(temperature), uncertain_getStdDev(temperature),
        uncertain_getLowerBound(temperature, 0.95), uncertain_getUpperBound(temperature, 0.95));
    printf("humidity: value = %f, std_dev = %f, 95%% bounds: [%f %f]\n",
        uncertain_getValue(humidity), uncertain_getStdDev(humidity),
        uncertain_getLowerBound(humidity, 0.95), uncertain_getUpperBound(humidity, 0.95));

    printf("dew point: value = %f, std_dev = %f, 90%% bounds: [%f %f]\n",
        uncertain_getValue(dp), uncertain_getStdDev(dp),
        uncertain_getLowerBound(dp, 0.90), uncertain_getUpperBound(dp, 0.90));
    printf("dew point: value = %f, std_dev = %f, 95%% bounds: [%f %f]\n",
        uncertain_getValue(dp), uncertain_getStdDev(dp),
        uncertain_getLowerBound(dp, 0.95), uncertain_getUpperBound(dp, 0.95));
    printf("dew point: value = %f, std_dev = %f, 99%% bounds: [%f %f]\n",
        uncertain_getValue(dp), uncertain_getStdDev(dp),
        uncertain_getLowerBound(dp, 0.99), uncertain_getUpperBound(dp, 0.99));


    printf("surfacetemperature: value = %f, std_dev = %f, 95%% bounds: [%f %f]\n",
        uncertain_getValue(surfacetemperature), uncertain_getStdDev(surfacetemperature),
        uncertain_getLowerBound(surfacetemperature, 0.95), uncertain_getUpperBound(surfacetemperature, 0.95));

    printf("probability for condensation on surface: %f (with 1 degree tolerance)\n",
        uncertain_probabilityEqual(dp, surfacetemperature, 1, 10000));

    return 0;
}
