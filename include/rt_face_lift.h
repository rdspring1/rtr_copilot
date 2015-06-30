#ifndef RT_FACE_LIFT_H
#define RT_FACE_LIFT_H

#include "util.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

void face_lift();
static bool check_rset();
static void constructNeighborhoods(struct Interval* allDerivatives, struct Interval* neighborhoodWidths);
static bool resample_derivative(bool* reconstruct, int max, double prevDerivative, double currDerivative);
static struct Interval getMinMaxDerivative(int dim, struct HyperRect* box);
static double minCrossReachTime(struct Interval* allDerivatives, struct Interval* neighborhoodWidths);
static void advanceBox(struct Interval* allDerivatives, double reachTime);
#endif // RT_FACE_LIFT_H
