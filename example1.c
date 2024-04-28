/*
    example on how to work with measurements with uncertain values
    
    find area of rectangle with somewhat uncertain sides
*/

#include "uncertain.h"
#include <stdio.h>

int main() {
    // x1 = 10 +- 2 (90% probability)
    uncertainNumber x1 = uncertain_createWithInterval(10.0, 8, 12, 0.9);

    // x1 = 10 +- 0.5 (100% probability)
    uncertainNumber x2 = uncertain_createWithInterval(10.0, 9.5, 10.5, 1);

    // y = 5 (exact value)
    uncertainNumber y = uncertain_createWithSD(5.0, 0);

    uncertainNumber x = uncertain_sum(x1, x2);          // x = x1 + x2
    uncertainNumber area = uncertain_product(x, y);     // area = x * y

    printf("x1: value = %f, std_dev = %f, 95%% bounds: [%f %f]\n",
        uncertain_getValue(x1), uncertain_getStdDev(x1),
        uncertain_getLowerBound(x1, 0.95), uncertain_getUpperBound(x1, 0.95));

    printf("x2: value = %f, std_dev = %f, 95%% bounds: [%f %f]\n",
        uncertain_getValue(x2), uncertain_getStdDev(x2),
        uncertain_getLowerBound(x2, 0.95), uncertain_getUpperBound(x2, 0.95));

    printf("x: value = %f, std_dev = %f, 95%% bounds: [%f %f]\n",
        uncertain_getValue(x), uncertain_getStdDev(x),
        uncertain_getLowerBound(x, 0.95), uncertain_getUpperBound(x, 0.95));

    printf("y: value = %f, std_dev = %f, 95%% bounds: [%f %f]\n",
        uncertain_getValue(y), uncertain_getStdDev(y),
        uncertain_getLowerBound(y, 0.95), uncertain_getUpperBound(y, 0.95));

    printf("area: value = %f, std_dev = %f, 95%% bounds: [%f %f]\n",
        uncertain_getValue(area), uncertain_getStdDev(area),
        uncertain_getLowerBound(area, 0.95), uncertain_getUpperBound(area, 0.95));

    printf("area: value = %f, std_dev = %f, 99%% bounds: [%f %f]\n",
        uncertain_getValue(area), uncertain_getStdDev(area),
        uncertain_getLowerBound(area, 0.99), uncertain_getUpperBound(area, 0.99));

    return 0;
}