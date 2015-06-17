#include "rt_face_lift.h"
#include "util.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// Objective: Keep angle of inverted pendulum upright 
int main(int argc, char** argv)
{
  assert(argc == 2);
  const int RNDS = atoi(argv[1]);

  // initial state
  double state[NUM_STATES] = {0};
  
  int i;
  for(i = 0; i < RNDS; ++i)
  {
    // TODO state = RT_REACH_ALG(state);
    print_state(i, state, NUM_STATES);
  }
  
  return 0;
}
