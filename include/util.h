#ifndef _UTIL_H_
#define _UTIL_H_

#include "monitor.h"
#include "params.h"
#include <stdbool.h>
#include <stdio.h>

extern const double EPSILON;

bool check_bound(struct Interval i, double value);
bool check_state(double* state);
void print_state(double* state);
void print_rset(struct Monitor * const params);
double min(double a, double b);
double max(double a, double b);
double absolute(double x);
void updateInterval(struct Interval* rv, double value);
void compressRset(struct Monitor * const params, const double DELTA);
#endif // _UTIL_H_
