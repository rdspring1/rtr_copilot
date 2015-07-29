#ifndef _HYPER_RECT_H_
#define _HYPER_RECT_H_

#include "constants.h"
#include "interval.h"

struct HyperRect
{
	struct Interval dims[NUM_STATES];
};

#endif // _HYPER_RECT_H_
