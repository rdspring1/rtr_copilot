#include "params.h"
#include "derivative_params.h"

struct HyperRect rset =
{
	{
		{1.0, 1.0},
		{0.20, 0.21},
	}
};

//double reachTimeStep = 0.0075; // 100 steps
double reachTimeStep = 0.0025; // 300 steps
//double reachTimeStep = 0.0006; // 1250 steps

// state contraints
const struct Interval state_constraints[NUM_STATES] =
{
	{-10.0, 10.0},
	{-10.0, 10.0},
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

void updateInflectionPoints(struct Interval* rv, int dim, struct HyperRect* box)
{
	if(contains(&box->dims[0], 1.0) && contains(&box->dims[1], -0.5))
	{
		double HyperPoint[NUM_STATES] = {1,-0.5};
		double dv = derivative(dim, HyperPoint);
		updateInterval(rv, dv);
	}

	if(contains(&box->dims[0], -1.0) && contains(&box->dims[1], 0.5))
	{
		double HyperPoint[NUM_STATES] = {-1,0.5};
		double dv = derivative(dim, HyperPoint);
		updateInterval(rv, dv);
	}

	double xmin = -1/(2 * box->dims[1].min);
	if(contains(&box->dims[0], xmin))
	{
		double HyperPoint[NUM_STATES] = {xmin, box->dims[1].min};
		double dv = derivative(dim, HyperPoint);
		updateInterval(rv, dv);
	}

	double xmax = -1/(2 * box->dims[1].max);
	if(contains(&box->dims[0], xmax))
	{
		double HyperPoint[NUM_STATES] = {xmax, box->dims[1].max};
		double dv = derivative(dim, HyperPoint);
		updateInterval(rv, dv);
	}
}
