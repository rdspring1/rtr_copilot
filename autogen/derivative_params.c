#include "derivative_params.h"

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

