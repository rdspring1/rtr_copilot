#ifndef _PENDULUM_VECTOR_FIELD_H
#define _PENDULUM_VECTOR_FIELD_H

#include "rt_face_lift.h"

const struct Interval STATE_BOUNDS[NUM_STATES] =
{
	{0, 1.25},
	{0, 1.2},
	{-20, 20},
	{-30, 30}
};

const double STEP = 0.05;
const double SAMPLES = 15.0;

#endif // _PENDULUM_VECTOR_FIELD_H
