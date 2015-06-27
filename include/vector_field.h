#ifndef VECTOR_FIELD_H
#define VECTOR_FIELD_H

#include "rt_face_lift.h"

const struct Interval STATE_BOUNDS[NUM_STATES] =
{
	{-1.25, 1.25},
	{-1.2, 1.2},
	{-20, 20},
	{-30, 30}
};

const double STEP = 0.05;
const double SAMPLES = 15.0;

#endif // VECTOR_FIELD_H
