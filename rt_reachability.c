#include "rt_face_lift.h"
#include "util.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// Objective: Keep angle of inverted pendulum upright 
int main(int argc, char** argv)
{
	const double DELTA = 0.01;
	const double VANDERPOL_REACH_TIME = 2.0;
	const double MAX_VANDERPOL_REACH_TIME = 12.0;
	//const double PENDULUM_REACH_TIME = 0.75;
	//face_lift(PENDULUM_REACH_TIME);

	for(double n = 0; n < MAX_VANDERPOL_REACH_TIME; n += VANDERPOL_REACH_TIME)
	{
		face_lift(VANDERPOL_REACH_TIME);
		compressRset(DELTA);	
	}
	return 0;
}
