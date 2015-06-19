#include "util.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

void face_lift();
void constructNeighborhoods(struct Interval* allDerivatives, struct Interval* neighborhoodWidths);
struct Interval getMinMaxDerivative(int dim, struct HyperRect* box);
double minCrossReachTime(struct Interval* allDerivatives, struct Interval* neighborhoodWidths);
void advanceBox(struct Interval* allDerivatives, double reachTime);
double linear_derivative(int dim, double* state);
