#include "util.h"

const double EPSILON = 0.00001;

bool check_bound(struct Interval i, double value)
{
  if(value > i.max)
  {
    return false;
  }
  else if(value < i.min)
  {
    return false;
  }
  else
  {
    return true;
  }
}

void print_rset(const int rnd)
{
  int i;
  for(i = 0; i < NUM_STATES; ++i)
  {
    printf("[%f %f]\t", rset.dims[i].min, rset.dims[i].max);
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
    if(x < 0)
    {
	return x *= -1.0;
    }
    return x;
}
