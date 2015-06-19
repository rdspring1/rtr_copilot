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
  const double RUNTIME = 2000; // 20 ms
  face_lift(RUNTIME); 
  return 0;
}
