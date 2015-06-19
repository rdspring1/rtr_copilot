#ifndef _UTIL_H_
#define _UTIL_H_

#include "dynamics.h"

#include <stdbool.h>
#include <stdio.h>

extern const double EPSILON;

bool check_bound(struct Interval i, double value);
double bound(struct Interval i, double value);
void check_input(double* values);
bool check_state(double* state);
void print_state(const int rnd);
double min(double a, double b);
double max(double a, double b);
#endif // _UTIL_H_
