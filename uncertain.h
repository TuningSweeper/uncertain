#ifndef UNCERTAIN_H
#define UNCERTAIN_H

#include <stdbool.h> // bool

typedef struct {
    double value;       // Value
    double std_dev;     // Standard deviation
} uncertainNumber;

uncertainNumber uncertain_createWithSD(double value, double std_dev);
uncertainNumber uncertain_createWithInterval(double value, double lower_bound, double upper_bound, double probability);
double uncertain_getValue(uncertainNumber num);
double uncertain_getStdDev(uncertainNumber num);
double uncertain_getLowerBound(uncertainNumber num, double probability);
double uncertain_getUpperBound(uncertainNumber num, double probability);
uncertainNumber uncertain_sum(uncertainNumber num1, uncertainNumber num2);
uncertainNumber uncertain_difference(uncertainNumber num1, uncertainNumber num2);
uncertainNumber uncertain_product(uncertainNumber num1, uncertainNumber num2);
uncertainNumber uncertain_fraction(uncertainNumber num1, uncertainNumber num2);
bool uncertain_ifLessThan(uncertainNumber num, double value, double probability);
bool uncertain_ifGreaterThan(uncertainNumber num, double value, double probability);
double uncertain_probabilityLessThan(uncertainNumber num, double value);
double uncertain_probabilityGreaterThan(uncertainNumber num, double value);
double uncertain_probabilityEqual(uncertainNumber num1, uncertainNumber num2, double tolerance, int num_samples);

#endif // UNCERTAIN_H