#ifndef _PARAMS_H_
#define _PARAMS_H_

#include "hyper_rect.h"
#include "interval.h"
#include "constants.h"
#include "util.h"

#include <float.h>

extern double reachTimeStep;
extern const struct Interval state_constraints[NUM_STATES];

void updateInflectionPoints(struct Interval* rv, int dim, struct HyperRect* box);
double derivative(int dim, double* state);
#endif // _PARAMS_H_
