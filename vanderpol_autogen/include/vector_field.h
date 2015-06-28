#ifndef VECTOR_FIELD_H
#define VECTOR_FIELD_H

#include "rt_face_lift.h"

const struct Interval STATE_BOUNDS[NUM_STATES] =
{
	{-2.5, 2.5},
	{-2.5, 2.5},
};

const double STEP = 0.05;
const double SAMPLES = 30.0;

#endif // VECTOR_FIELD_H
