#include "input_params.h"

const double K[NUM_INPUTS][NUM_STATES] =
{
	{0.4072, 7.2373, 18.6269, 3.6725}
	//{7.6, 13.54, 42.85, 8.25}
	//{3.16, 19.85, 69.92, 14.38}
	//{10.0, 27.72, 103.36, 23.04}
	//{0,0,0,0}
};

// input constraints
const struct Interval input_constraints[NUM_INPUTS] =
{
	{-4.95, 4.95}
};

