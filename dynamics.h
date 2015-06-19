#ifndef _DYNAMICS_H_
#define _DYNAMICS_H_

#include "interval.h"

#include <float.h>
#include <stdbool.h>

#define NUM_STATES 4
#define NUM_INPUTS 1

struct HyperRect
{
    struct Interval dims[NUM_STATES];
};

extern struct HyperRect rset;
extern double reachTimeStep;
extern const double A[NUM_STATES][NUM_STATES];
extern const double B[NUM_STATES][NUM_INPUTS];
extern const double K[NUM_INPUTS][NUM_STATES];
extern const struct Interval state_constraints[NUM_STATES];
extern const struct Interval input_constraints[NUM_INPUTS];

void generate_input(double* state, double* u);
#endif // _DYNAMICS_H_
