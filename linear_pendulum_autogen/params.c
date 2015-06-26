#include "params.h"
#include "linear.h"

struct HyperRect rset =
{
    {
	{-0.001, 0.001},
	{0.85, 0.85},
	{0, 0},
	{0, 0}
    }
};

//double reachTimeStep = 0.0075; // 100 steps
//double reachTimeStep = 0.0025; // 300 steps
double reachTimeStep = 0.0006; // 1250 steps

// state contraints
const struct Interval state_constraints[NUM_STATES] =
{
  {-1.0, 1.0},
  {-1.0, 1.0},
  {-30.0, 30.0},
  {-DBL_MAX, DBL_MAX}
};

double derivative(int dim, double* state)
{
    return linear_derivative(dim, state);
}
