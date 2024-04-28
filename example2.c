/*
    example on how to work with measurements with uncertain values

    averaging values from non-ideal sensor and checking the probability of freezing
*/

#include "uncertain.h"
#include <stdio.h>

int main() {
    // array of values from sensor
    double values[] = { 2.0, 2.2, 1.8, 2.1, 2.0, 2.3, 1.9, 2.0, 2.1, 2.0 };

    // create uncertain numbers for each value
    // assume accuracy of sensor is +- 2 (with 95% probability)
    uncertainNumber nums[10];
    for (int i = 0; i < 10; i++) {
        nums[i] = uncertain_createWithInterval(values[i], values[i] - 2, values[i] + 2, 0.95);
    }

    // calculate average of values
    // get the sum
    uncertainNumber sum = uncertain_createWithSD(0.0, 0.0);
    for (int i = 0; i < 10; i++) {
        sum = uncertain_sum(sum, nums[i]);
    }
    // divide by 10
    uncertainNumber avg = uncertain_fraction(sum, uncertain_createWithSD(10.0, 0.0));

    printf("first num: value = %f, std_dev = %f, 95%% bounds: [%f %f]\n",
        uncertain_getValue(nums[0]), uncertain_getStdDev(nums[0]),
        uncertain_getLowerBound(nums[0], 0.95), uncertain_getUpperBound(nums[0], 0.95));


    printf("average: value = %f, std_dev = %f, 95%% bounds: [%f %f]\n",
        uncertain_getValue(avg), uncertain_getStdDev(avg),
        uncertain_getLowerBound(avg, 0.95), uncertain_getUpperBound(avg, 0.95));

    // probability of freezing? (average temperature < 0)
    printf("first value probability of freezing: %f\n", uncertain_probabilityLessThan(nums[0], 0.0));

    // probability of freezing? (average temperature < 0)
    printf("average value probability of freezing: %f\n", uncertain_probabilityLessThan(avg, 0.0));

    return 0;
}