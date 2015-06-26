#include "linear_control.h"

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

void check_input(double* values)
{
  int i;
  for(i = 0; i < NUM_INPUTS; ++i)
  {
    values[i] = bound(input_constraints[i], values[i]);
  }
}

void generate_input(double* state, double* u)
{
  int i,j;
  for(i = 0; i < NUM_INPUTS; ++i)
  {
    for(j = 0; j < NUM_STATES; ++j)
    {
      u[i] += K[i][j] * state[j];
    }
  }
  check_input(u);
}
