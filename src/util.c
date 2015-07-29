#include "util.h"

const double EPSILON = 0.00001;

bool check_bound(struct Interval i, double value)
{
	return ((value > i.max) && (value < i.min)) ? false : true;
}

void print_rset(struct Monitor * const params)
{
	int i;
	for(i = 0; i < NUM_STATES; ++i)
	{
		printf("[%f %f]\t", params->rset->dims[i].min, params->rset->dims[i].max);
	}
	printf("\n");
}

void print_state(double* state)
{
	int i;
	for(i = 0; i < NUM_STATES; ++i)
	{
		printf("%f \t", state[i]);
	}
	printf("\n");
}

bool check_state(double* state)
{
	int i;
	for(i = 0; i < NUM_STATES; ++i)
	{
		if(!check_bound(state_constraints[i], state[i]))
		{
			return false;
		}
	}
	return true;
}

double min(double a, double b)
{
	return (a < b) ? a : b;
}

double max(double a, double b)
{
	return (a > b) ? a : b;
}

double absolute(double x)
{
	return (x < 0) ? (x * -1.0) : x;
}

void updateInterval(struct Interval* rv, double value)
{
	rv->min = min(rv->min, value);
	rv->max = max(rv->max, value);
}

void compressRset(struct Monitor * const params, const double DELTA)
{
	double avg0 = avg(&params->rset->dims[0]);
	//printf("%f %f %f \n", params->rset->dims[0].min, params->rset->dims[0].max, avg0);
	params->rset->dims[0].min = avg0;
	params->rset->dims[0].max = avg0 + DELTA;
	for(int d = 1; d < NUM_STATES; ++d)
	{
		double average = avg(&params->rset->dims[d]);
		//printf("%f %f %f\n", params->rset->dims[d].min, params->rset->dims[d].max, average);
		params->rset->dims[d].min = average;
		params->rset->dims[d].max = average;
	}
}
