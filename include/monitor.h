#ifndef _MONITOR_H_
#define _MONITOR_H_

#include "hyper_rect.h"

typedef double (*derivativeFunDef)(int dim, double* state);
typedef void (*UIPFunDef)(struct Interval* rv, int dim, struct HyperRect* box);

struct Monitor
{
	const unsigned NUM_STATES_;
	const double reachTimeStep;
	const struct Interval * const state_constraints;
	derivativeFunDef derivative;
	UIPFunDef updateInflectionPoints;
	struct HyperRect * const rset;
};

#endif // _MONITOR_H_
