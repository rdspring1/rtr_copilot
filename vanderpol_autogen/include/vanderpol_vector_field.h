#ifndef VANDERPOL_VECTOR_FIELD_H
#define VANDERPOL_VECTOR_FIELD_H

#include "rt_face_lift.h"
#include "vanderpol_params.h"

const struct Interval STATE_BOUNDS[VANDERPOL_NUM_STATES] =
{
	{-2.5, 2.5},
	{-2.5, 2.5},
};

const double STEP = 0.05;
const double SAMPLES = 30.0;

derivativeFunDef derivative = &vanderpol_derivative;
#endif // VANDERPOL_VECTOR_FIELD_H