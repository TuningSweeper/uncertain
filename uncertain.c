/*
    uncertain.c

    Uncertain number library. Enables basic arithmetic operations
    on uncertain numbers which are normally distributed.

    Mostly just a quick'n'dirty conceptual demo. May shrink if washed.
*/

#include "uncertain.h"
#include <math.h> // sqrt, pow, exp, erf, log, fabs
#include <stdbool.h> // bool
#include <stdlib.h> // srand for monte carlo simulation
#include <time.h> // time for seeding srand

// *******************************************************************************
// Local functions
// *******************************************************************************

// Macro to generate a random double within a specified range
#define random_double(min, max) ((min) + ((double)rand() / RAND_MAX) * ((max) - (min)))

// Function to generate a random double within a specified range
//double random_double(double min, double max) {
//    return min + (rand() / (RAND_MAX / (max - min)));
//}


// inverse error function
// found somewhere I cannot seem to find again
double erf_inv(double y) {
    double x = 0.0;
    double dx = 1.0;
    double err = 1e-15;

    x = 0.5 * sqrt(3.14159265) * y;

    while (fabs(dx) > err) {
        double f = erf(x) - y;
        double df = exp(-x * x);
        dx = f / df;
        x -= dx;
    }

    return x;
}

// *******************************************************************************
// SETTERS
// *******************************************************************************

// Fuction to create an uncertain number based on a value and a standard deviation
uncertainNumber uncertain_createWithSD(double value, double std_dev) {
    uncertainNumber num;

    num.value = value;
    num.std_dev = std_dev;

    return num;
}

// Function to create an uncertain number based on a value and interval
uncertainNumber uncertain_createWithInterval(double value, double lower_bound, double upper_bound, double probability) {
    uncertainNumber result;

    double z_score = erf_inv(2 * probability - 1) * sqrt(2);
    result.std_dev = (upper_bound - lower_bound) / (2 * z_score);
    result.value = value;

    return result;
}


// *******************************************************************************
// GETTERS
// *******************************************************************************

// Function to get the value of an uncertain number
double uncertain_getValue(uncertainNumber num) {
    return num.value;
}

// Function to get the standard deviation of an uncertain number
double uncertain_getStdDev(uncertainNumber num) {
    return num.std_dev;
}

// Function to get the lower bound of an uncertain number
double uncertain_getLowerBound(uncertainNumber num, double probability) {
    double z_score = erf_inv(2 * probability - 1) * sqrt(2);

    return num.value - num.std_dev * z_score;
}

// Function to get the upper bound of an uncertain number
double uncertain_getUpperBound(uncertainNumber num, double probability) {
    double z_score = erf_inv(2 * probability - 1) * sqrt(2);

    return num.value + num.std_dev * z_score;
}



// *******************************************************************************
// Arithmetic operations
// *******************************************************************************

// Function to sum uncertain numbers
uncertainNumber uncertain_sum(uncertainNumber num1, uncertainNumber num2) {
    uncertainNumber result;

    result.value = num1.value + num2.value;
    result.std_dev = sqrt(pow(num1.std_dev, 2) + pow(num2.std_dev, 2));

    return result;
}

// Function to find the difference between uncertain numbers
uncertainNumber uncertain_difference(uncertainNumber num1, uncertainNumber num2) {
    uncertainNumber result;

    result.value = num1.value - num2.value;
    result.std_dev = sqrt(pow(num1.std_dev, 2) + pow(num2.std_dev, 2));

    return result;
}

// Function to multiply uncertain numbers
uncertainNumber uncertain_product(uncertainNumber num1, uncertainNumber num2) {
    uncertainNumber result;

    result.value = num1.value * num2.value;
    result.std_dev = result.value * sqrt(pow(num1.std_dev / num1.value, 2) + pow(num2.std_dev / num2.value, 2));

    return result;
}

// Function to divide uncertain numbers
uncertainNumber uncertain_fraction(uncertainNumber num1, uncertainNumber num2) {
    uncertainNumber result;
    
    // prevent division by zero
    if (num2.value != 0) {
        result.value = num1.value / num2.value;
        result.std_dev = result.value * sqrt(pow(num1.std_dev / num1.value, 2) + pow(num2.std_dev / num2.value, 2));
    } else {
        result.value = NAN;
        result.std_dev = INFINITY;
    }    

    return result;
}

// *******************************************************************************
// Comparison operations
// *******************************************************************************

// Function to compare uncertain number with a certain value with a given probability
bool uncertain_ifLessThan(uncertainNumber num, double value, double probability) {
    double z_score = erf_inv(2 * probability - 1) * sqrt(2);
    double threshold = value - z_score * num.std_dev;
    
    return num.value < threshold;
}

// Function to compare uncertain number with a certain value with a given probability
bool uncertain_ifGreaterThan(uncertainNumber num, double value, double probability) {
    double z_score = erf_inv(2 * probability - 1) * sqrt(2);
    double threshold = value + z_score * num.std_dev;
    
    return num.value > threshold;
}

// Function to get the probability that the uncertain number is below a certain value
double uncertain_probabilityLessThan(uncertainNumber num, double value) {
    double z_score = (value - num.value) / num.std_dev;
    
    return (1 + erf(z_score / sqrt(2))) / 4;
}

// Function to get the probability that the uncertain number is above a certain value
double uncertain_probabilityGreaterThan(uncertainNumber num, double value) {
    double z_score = (value - num.value) / num.std_dev;
    
    return (1 - erf(z_score / sqrt(2))) / 4;
}



// Function to perform Monte Carlo simulation to estimate the probability that two uncertain numbers are equal within a tolerance range
double uncertain_probabilityEqual(uncertainNumber num1, uncertainNumber num2, double tolerance, int num_samples) {
    int equal_count = 0;
    
    srand(time(NULL));  // to seed the rng

    // Monte Carlo simulation
    for (int i = 0; i < num_samples; ++i) {
        double sample1 = random_double(num1.value - num1.std_dev, num1.value + num1.std_dev);
        double sample2 = random_double(num2.value - num2.std_dev, num2.value + num2.std_dev);
        
        if (fabs(sample1 - sample2) <= tolerance) equal_count++;
    }
    
    return (double)equal_count / num_samples;
}
