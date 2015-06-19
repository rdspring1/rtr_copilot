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

double bound(struct Interval i, double value)
{
  if(value > i.max)
  {
    return i.max;
  }
  else if(value < i.min)
  {
      return i.min;
  }
  else
  {
      return value;
  }
}

void print_state(const int rnd)
{
  printf("Round: %d\t", rnd);
  int i;
  for(i = 0; i < NUM_STATES; ++i)
  {
    printf("[%f %f] \t", rset.dims[i].min, rset.dims[i].max);
  }
  printf("\n");
}

void check_input(double* values)
{
  int i;
  for(i = 0; i < NUM_INPUTS; ++i)
  {
    values[i] = bound(input_constraints[i], values[i]);
  }
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
