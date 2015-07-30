#define PARAMS 2
#define PENDULUM "PENDULUM"
#define VANDERPOL "VANDERPOL"

#include "rt_face_lift.h"
#include "util.h"

#include "vanderpol_params.h"
#include "pendulum_params.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// Objective: Keep angle of inverted pendulum upright 
int main(int argc, char** argv)
{
	if(argc != PARAMS)
	{
		printf("Missing RTR Monitor Type Parameter\n");
	}
	else if(!strcmp(argv[1], PENDULUM))
	{
		extern struct Monitor pendulum_params;
		const double PENDULUM_REACH_TIME = 0.75;
		face_lift(&pendulum_params, PENDULUM_REACH_TIME);
	}
	else if(!strcmp(argv[1], VANDERPOL))
	{
		extern struct Monitor vanderpol_params;
		const double DELTA = 0.01;
		const double VANDERPOL_REACH_TIME = 2.0;
		const double MAX_VANDERPOL_REACH_TIME = 12.0;

		for(double n = 0; n < MAX_VANDERPOL_REACH_TIME; n += VANDERPOL_REACH_TIME)
		{
			face_lift(&vanderpol_params, VANDERPOL_REACH_TIME);
			compressRset(&vanderpol_params, DELTA);
		}
	}
	return 0;
}
