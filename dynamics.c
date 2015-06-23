#include "dynamics.h"

struct HyperRect rset =
{
    {
	{-0.1, 0.1},
	{0.85, 0.85},
	{0, 0},
	{0, 0}
    }
};

double reachTimeStep = 0.0075; // 100 steps
//double reachTimeStep = 0.0025; // 300 steps
//double reachTimeStep = 0.0006; // 1250 steps

// x' = Ax + Bu
const double A[NUM_STATES][NUM_STATES] =
{
  {0,1,0,0},
  {0,-10.95,-2.75,0.0043},
  {0,0,0,1},
  {0,24.92,28.58,-0.044}
};

const double B[NUM_STATES][NUM_INPUTS] =
{
  {0},
  {1.94},
  {0},
  {-4.44}
};

const double K[NUM_INPUTS][NUM_STATES] =
{
  {0.4072, 7.2373, 18.6269, 3.6725}
};

// state contraints
const struct Interval state_constraints[NUM_STATES] =
{
  {-1.0, 1.0},
  {-1.0, 1.0},
  {-30.0, 30.0},
  {-DBL_MAX, DBL_MAX}
};

// input constraints
const struct Interval input_constraints[NUM_INPUTS] =
{
  {-4.95, 4.95}
};

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
}
