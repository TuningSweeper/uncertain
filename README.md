# Uncertain Numbers Library

Inspired by the Rust Uncertain crate, I was fascinated by the concept of uncertain numbers and began contemplating their potential use cases and applications. This library serves as a proof-of-concept demo, aiming to provide a playground for exploring possibilities of uncertain arithmetic using C on embedded systems.


## Introduction

Uncertain numbers are useful for representing quantities where the exact value is not known precisely, but here is some level of uncertainty associated with it. This library provides functions for creating uncertain numbers, performing arithmetic operations on them, and comparing them with certain values at specified 
probabilities.

Intended applications are mostly related to sensor data processing and decision making. Use uncertain arithmetic to handle data with inherent uncertainty, ensuring robust and accurate computations, or for making decisions based on probabilistic assessments of uncertain data.

The uncertain values are represented as tuples of a value and standard deviation or interval bounds. It's assumed that values are distributed normally (which is not always the case in real life or modern sensors).



## Function Reference

- `uncertain_createWithSD(double value, double std_dev)`: Create an uncertain number with a given value and standard deviation.
- `uncertain_createWithInterval(double value, double lower_bound, double upper_bound, double probability)`: Create an uncertain number with a given value and interval bounds.
- `uncertain_getValue(UncertainNumber num)`: Get the value of an uncertain number.
- `uncertain_getStdDev(UncertainNumber num)`: Get the standard deviation of an uncertain number.
- `uncertain_getLowerBound(UncertainNumber num, double probability)`: Get the lower bound of an uncertain number's interval with the specified probability.
- `uncertain_getUpperBound(UncertainNumber num, double probability)`: Get the upper bound of an uncertain number's interval with the specified probability.
- `uncertain_sum(UncertainNumber num1, UncertainNumber num2)`: Sum two uncertain numbers.
- `uncertain_difference(UncertainNumber num1, UncertainNumber num2)`: Find the difference between two uncertain numbers.
- `uncertain_product(UncertainNumber num1, UncertainNumber num2)`: Multiply two uncertain numbers.
- `uncertain_fraction(UncertainNumber num1, UncertainNumber num2)`: Divide two uncertain numbers.
- `uncertain_ifLessThan(UncertainNumber num, double value, double probability)`: Check if an uncertain number is less than a certain value with a given probability.
- `uncertain_ifGreaterThan(UncertainNumber num, double value, double probability)`: Check if an uncertain number is greater than a certain value with a given probability.
- `uncertain_probabilityLessThan(UncertainNumber num, double value)`: Get the probability that an uncertain number is below a certain value.
- `uncertain_probabilityGreaterThan(UncertainNumber num, double value)`: Get the probability that an uncertain number is above a certain value.
- `uncertain_probabilityEqual(UncertainNumber num1, UncertainNumber num2, double tolerance, int num_samples)`: Estimate the probability that two uncertain numbers are equal within a tolerance range using Monte Carlo simulation.


## Examples

### Example 1: Finding the area of a rectangle with uncertain sides
```
gcc -o test1 example1.c uncertain.c
./test1
x1: value = 10.000000, std_dev = 1.560608, 95% bounds: [7.433028 12.566972]
x2: value = 10.000000, std_dev = 0.058209, 95% bounds: [9.904255 10.095745]
x: value = 20.000000, std_dev = 1.561693, 95% bounds: [17.431243 22.568757]
y: value = 5.000000, std_dev = 0.000000, 95% bounds: [5.000000 5.000000]
area: value = 100.000000, std_dev = 7.808467, 99% bounds: [81.834788 118.165212]
```


### Example 2: Averaging values from a non-ideal sensor and checking the probability of freezing
```
gcc -o test2 example2.c uncertain.c
./test2
first num: value = 2.000000, std_dev = 1.215914, 95% bounds: [0.000000 4.000000]
average: value = 2.040000, std_dev = 0.384506, 95% bounds: [1.407544 2.672456]
first value probability of freezing: 0.025000
average value probability of freezing: 0.000000
```

### Example 3: Temperature, dew point, and probability of condensation
```
gcc -o test3 example3.c uncertain.c
./test3
temperature: value = 22.000000, std_dev = 0.859717, 95% bounds: [20.585892 23.414108]
humidity: value = 55.000000, std_dev = 7.803041, 95% bounds: [42.165139 67.834861]
dew point: value = 13.000000, std_dev = 1.781744, 90% bounds: [10.716603 15.283397]
dew point: value = 13.000000, std_dev = 1.781744, 95% bounds: [10.069292 15.930708]
dew point: value = 13.000000, std_dev = 1.781744, 99% bounds: [8.855044 17.144956]
surfacetemperature: value = 16.000000, std_dev = 0.859717, 95% bounds: [14.585892 17.414108]
probability for condensation on surface: 0.034900 (with 1 degree tolerance)
```


# License

This library is probably licensed under certain license. See me for details.