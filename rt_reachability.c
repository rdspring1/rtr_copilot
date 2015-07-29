#include "rt_face_lift.h"
#include "util.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// Objective: Keep angle of inverted pendulum upright 
int main(int argc, char** argv)
{
	//double reachTimeStep = 0.0075; // 100 steps
	double reachTimeStep = 0.0025; // 300 steps
	//double reachTimeStep = 0.0006; // 1250 steps

	struct Interval vanderpol_dims[NUM_STATES] =
	{
		{1.0, 1.0},
		{0.20, 0.21}
	};

	struct HyperRect vanderpol_rset =
	{
		{
			{1.0, 1.0},
			{0.20, 0.21}
		}
	};

	   const struct Interval vanderpol_constraints[NUM_STATES] =
	   {
	   {-10.0, 10.0},
	   {-10.0, 10.0}
	   };

	struct Monitor vanderpol_params =
	{
		NUM_STATES,
		reachTimeStep,
		vanderpol_constraints,
		&derivative,
		&updateInflectionPoints,
		&vanderpol_rset
	};

	const double DELTA = 0.01;
	const double VANDERPOL_REACH_TIME = 2.0;
	const double MAX_VANDERPOL_REACH_TIME = 12.0;
	//const double PENDULUM_REACH_TIME = 0.75;
	//face_lift(PENDULUM_REACH_TIME);

	for(double n = 0; n < MAX_VANDERPOL_REACH_TIME; n += VANDERPOL_REACH_TIME)
	{
		face_lift(&vanderpol_params, VANDERPOL_REACH_TIME);
		compressRset(&vanderpol_params, DELTA);
	}
	return 0;
}
