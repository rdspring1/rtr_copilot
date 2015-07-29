#ifndef RT_FACE_LIFT_H
#define RT_FACE_LIFT_H

#include "monitor.h"
#include "util.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

void face_lift(struct Monitor* params, double reachTimeRemaining);
static bool check_rset(struct Monitor * const params);
static void constructNeighborhoods(struct Monitor * const params, struct Interval* allDerivatives, struct Interval* neighborhoodWidths);
static bool resample_derivative(bool* reconstruct, int max, double prevDerivative, double currDerivative);
static struct Interval getMinMaxDerivative(int dim, struct HyperRect* box);
static double minCrossReachTime(struct Interval* allDerivatives, struct Interval* neighborhoodWidths);
static void advanceBox(struct Monitor * const params, struct Interval* allDerivatives, double reachTime);
#endif // RT_FACE_LIFT_H
