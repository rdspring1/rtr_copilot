#include "params.h"
#include "derivative_params.h"

struct HyperRect rset =
{
	{
		{1.0, 1.0},
		{0.20, 0.21},
	}
};

double reachTimeStep = 0.0075; // 100 steps
//double reachTimeStep = 0.0025; // 300 steps
//double reachTimeStep = 0.0006; // 1250 steps

// state contraints
const struct Interval state_constraints[NUM_STATES] =
{
	{-15.0, 15.0},
	{-15.0, 15.0},
};

double derivative(int dim, double* state)
{
	switch(dim)
	{
		case 0:
		{
			return x_derivative(state);
		}
		case 1:
		{
			return y_derivative(state);
		}
		default:
		{
			break;
		}
	}
}
