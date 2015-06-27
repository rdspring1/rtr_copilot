#ifndef _PARAMS_H_
#define _PARAMS_H_

#include "interval.h"
#include "constants.h"

#include <float.h>

struct HyperRect
{
	struct Interval dims[NUM_STATES];
};

extern struct HyperRect rset;
extern double reachTimeStep;
extern const struct Interval state_constraints[NUM_STATES];

double derivative(int dim, double* state);
#endif // _PARAMS_H_
