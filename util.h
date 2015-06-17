#ifndef _UTIL_H_
#define _UTIL_H_

#include "dynamics.h"

#include <stdbool.h>
#include <stdio.h>

bool check_bound(struct Interval i, double value);
double bound(struct Interval i, double value);
void check_input(double* values);
bool check_state(double* state);
void print_state(const int rnd, double* state, const int SIZE);
#endif // _UTIL_H_
