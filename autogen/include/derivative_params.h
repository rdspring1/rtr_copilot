#ifndef DERIVATIVE_PARAMS_H
#define DERIVATIVE_PARAMS_H

// Specify the type of controller - linear, nonlinear, monitor
#include "linear_control.h"

extern const double A[NUM_STATES][NUM_STATES];
extern const double B[NUM_STATES][NUM_INPUTS];

#endif // DERIVATIVE_PARAMS_H
