#include "vector_field.h"
#include <stdlib.h>

void build_vector_field(const int xaxis, const int yaxis)
{
	assert(xaxis >= 0);
	assert(yaxis >= 0);
	assert(xaxis < NUM_STATES);
	assert(yaxis < NUM_STATES);

	double xrange = STATE_BOUNDS[xaxis].max - STATE_BOUNDS[xaxis].min;
	double xstep = xrange / SAMPLES;

	double yrange = STATE_BOUNDS[yaxis].max - STATE_BOUNDS[yaxis].min;
	double ystep = yrange / SAMPLES;

	for(double i = 0; i < SAMPLES; ++i)
	{
		for(double j = 0; j < SAMPLES; ++j)
		{
			double hyperPoint[NUM_STATES] = {0};
			hyperPoint[xaxis] = STATE_BOUNDS[xaxis].min + i * xstep;
			hyperPoint[yaxis] = STATE_BOUNDS[yaxis].min + j * ystep;
			printf("[%f %f]\t", hyperPoint[xaxis], hyperPoint[yaxis]);

			double xdiv = derivative(xaxis, hyperPoint);
			double ydiv = derivative(yaxis, hyperPoint);

			hyperPoint[xaxis] += STEP * xdiv;
			hyperPoint[yaxis] += STEP * ydiv;
			printf("[%f %f]\n", hyperPoint[xaxis], hyperPoint[yaxis]);
		}
	}
}

int main(int argv, char** argc)
{
	const int xaxis = (argv >= 3) ? atoi(argc[1]) : 0;
	const int yaxis = (argv >= 3) ? atoi(argc[2]) : 1;
	build_vector_field(xaxis, yaxis);
	return 0;
}
