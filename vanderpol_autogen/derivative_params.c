#include "derivative_params.h"

double x_derivative(double* state)
{
	return state[1];
}

double y_derivative(double* state)
{
	return (1 - pow(state[0], 2)) * state[1] - state[0];
}
