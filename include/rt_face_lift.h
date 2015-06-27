#ifndef RT_FACE_LIFT_H
#define RT_FACE_LIFT_H

#include "util.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

void face_lift();
bool check_rset();
void constructNeighborhoods(struct Interval* allDerivatives, struct Interval* neighborhoodWidths);
bool resample_derivative(bool* reconstruct, int max, double prevDerivative, double currDerivative);
struct Interval getMinMaxDerivative(int dim, struct HyperRect* box);
double minCrossReachTime(struct Interval* allDerivatives, struct Interval* neighborhoodWidths);
void advanceBox(struct Interval* allDerivatives, double reachTime);
#endif // RT_FACE_LIFT_H
