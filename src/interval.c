#include "interval.h"

bool contains(struct Interval* intv, double value)
{
	return (intv->min <= value) && (intv->max >= value);
}
