#include "rt_face_lift.h"

/*
void face_lift()
{
  Box currentBox = initalBox;

  while(reachTimeRemaining > 0)
  {
    Box[] nebs = constructNeighborhoods(currentBox, reachTimeStep);
    crossReachTime = min(crossReachTime, reachTimeRemaining);
    advanceReachTime = min(crossReachTime, reachTimeRemaining);
    currentBox = advanceBox(nebs, advanceReachTime);
    
    reachTimeRemaining = reachTimeRemaining - reachTimeToAdvance;
  }
}

interval min_max_derivatives()
{
}
*/

double linear_derivative(int dim, double* state)
{
  // return value
  double rv = 0;

  // AX
  int i;
  for(i = 0; i < NUM_STATES; ++i)
  {
    rv += A[dim][i] * state[i];
  }

  // input saturation
  // u = KX 
  double u[NUM_INPUTS] = {0};
  generate_input(state, u);
  check_input(u);

  // Bu
  for(i = 0; i < NUM_INPUTS; ++i)
  {
    rv += B[dim][i] * u[i];
  }
  return rv;
}




