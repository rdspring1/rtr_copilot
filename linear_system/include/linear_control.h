#ifndef INPUT_H
#define INPUT_H

#include "input_params.h"

#include <stdbool.h>

double bound(struct Interval i, double value);
void check_input(double* values);
void generate_input(double* state, double* u);

#endif // INPUT_H
