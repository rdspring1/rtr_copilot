#ifndef INPUT_PARAMS_H
#define INPUT_PARAMS_H

#include "interval.h"
#include "constants.h"

extern const double K[NUM_INPUTS][NUM_STATES];
extern const struct Interval input_constraints[NUM_INPUTS];

#endif // INPUT_PARAMS_H
