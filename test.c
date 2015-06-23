#include "rt_face_lift.h"
#include "util.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// Objective: Keep angle of inverted pendulum upright 
int main(int argc, char** argv)
{
    const double REACH_TIME = 0.75;
    face_lift(REACH_TIME);
    return 0;
}
