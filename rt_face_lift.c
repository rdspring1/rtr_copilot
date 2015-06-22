#include "rt_face_lift.h"

void face_lift(double reachTimeRemaining)
{
    int rnds = 0;
    while(reachTimeRemaining > 0)
    {
	print_rset(++rnds);
	assert(check_rset());

	// min / max derivative for each neighborhood to determine minimum reach-time
	struct Interval allDerivatives[NUM_STATES];
	struct Interval neighborhoodWidths[NUM_STATES];
        constructNeighborhoods(allDerivatives, neighborhoodWidths);

	// for each neighborhood, reach-time = neighborhood-width / (min/max) derivative
        double crossReachTime = minCrossReachTime(allDerivatives, neighborhoodWidths);
        double advanceReachTime = min(crossReachTime, reachTimeRemaining);
        advanceBox(allDerivatives, advanceReachTime);
	
        reachTimeRemaining -= advanceReachTime;
	reachTimeStep /= 2.0;
    }
}

bool check_rset()
{
    int maxPts = floor(pow(2, NUM_STATES));
    int pt;
    for(pt = 0; pt < maxPts; ++pt)
    {
	double HyperPoint[NUM_STATES];
	int mask = 0x1;
	// Map integer pt to corresponding HyperPoint
	int d;
	for(d = 0; d < NUM_STATES; ++d)
	{
	    bool max = (pt & mask);
	    mask <<= 1;
	    HyperPoint[d] = (max) ? rset.dims[d].max : rset.dims[d].min;
	}

	if(!check_state(HyperPoint))
	{
	    return false;
	}
    }
        return true;
}

// TODO Rewrite function to construct neighborhoods properly
// TODO Step 3 - check inward facing neighborhood for outward facing derivative
// TODO Step 3 - check if a derivative is double the previous derivative along a neighborhood face
void constructNeighborhoods(struct Interval* allDerivatives, struct Interval* neighborhoodWidths)
{
    int d;
    for(d = 0; d < NUM_STATES; ++d)
    {
	int max;
	for(max = 0; max < 2; ++max)
	{
	    struct HyperRect neighborhood;
	    neighborhood = rset;

	    // Which face in the dimension are we expanding?
	    if(!max) // min
	    {
		neighborhood.dims[d].max = neighborhood.dims[d].min;
	    }
	    else // max
	    {
		neighborhood.dims[d].min = neighborhood.dims[d].max;
	    }

	    struct Interval faceInterval = getMinMaxDerivative(d, &neighborhood);
	    double faceDerivative = (!max) ? faceInterval.min : faceInterval.max;
	    double neighborhoodWidth = absolute(faceDerivative * reachTimeStep);

	    if(faceDerivative > 0)
	    {
		neighborhood.dims[d].max += neighborhoodWidth;
	    }
	    else
	    {
		neighborhood.dims[d].min -= neighborhoodWidth;
	    }

	    int other_dim;
	    for(other_dim = 0; other_dim < NUM_STATES; ++other_dim)
	    {
		if(other_dim != d)
		{
		    neighborhood.dims[other_dim].min -= neighborhoodWidth;
		    neighborhood.dims[other_dim].max += neighborhoodWidth;
		}
	    }
	    
	    struct Interval neighborhoodInterval = getMinMaxDerivative(d, &neighborhood);
	    if(!max)
	    {
		neighborhoodWidths[d].min = neighborhoodWidth;
		allDerivatives[d].min = neighborhoodInterval.min;
	    }
	    else
	    {
		neighborhoodWidths[d].max = neighborhoodWidth;
		allDerivatives[d].max = neighborhoodInterval.max;
	    }
	}
    }
}

struct Interval getMinMaxDerivative(int dim, struct HyperRect* box)
{
    // Iterate over 2^N points of HyperRectangle
    // Determine derivative for every HyperPoint
    // Return the min and max derivative for the HyperRectangle
    struct Interval rv;
    rv.min = DBL_MAX;
    rv.max = -DBL_MAX;

    int maxPts = floor(pow(2, NUM_STATES));
    int pt;
    for(pt = 0; pt < maxPts; ++pt)
    {
	double HyperPoint[NUM_STATES];
	int mask = 0x1;
	// Map integer pt to corresponding HyperPoint
	int d;
	for(d = 0; d < NUM_STATES; ++d)
	{
	    bool max = (pt & mask);
	    mask <<= 1;
	    HyperPoint[d] = (max) ? box->dims[d].max : box->dims[d].min;
	}
	double dv = linear_derivative(dim, HyperPoint);
	rv.min = min(rv.min, dv);
	rv.max = max(rv.max, dv);
    }
    
    return rv;
}

double linear_derivative(int dim, double* state)
{
  // return value
  double rv = 0;

  // AX
  int i;
  for(i = 0; i < NUM_STATES; ++i)
  {
    rv += A[dim][i] * state[i];
  }

  // input saturation
  // u = KX
  double u[NUM_INPUTS] = {0};
  generate_input(state, u);
  check_input(u);

  // Bu
  for(i = 0; i < NUM_INPUTS; ++i)
  {
    rv += B[dim][i] * u[i];
  }
  return rv;
}

double minCrossReachTime(struct Interval* allDerivatives, struct Interval* neighborhoodWidths)
{
    double minTime = DBL_MAX;
    int d;
    for(d = 0; d < NUM_STATES; ++d)
    {
	double absMin = absolute(allDerivatives[d].min);
	if(absMin > EPSILON)
        {
	    double minTimeDim = neighborhoodWidths[d].min / absMin; 
	    minTime = min(minTime, minTimeDim);
	}

	double absMax = absolute(allDerivatives[d].max);
	if(absMax > EPSILON)
	{
	    double maxTimeDim = neighborhoodWidths[d].max / absMax;
	    minTime = min(minTime, maxTimeDim);
	}
    }
    return minTime;
}

void advanceBox(struct Interval* allDerivatives, double reachTime)
{
    if(reachTime < DBL_MAX)
    {
	int d;
	for(d = 0; d < NUM_STATES; ++d)
	{
	    rset.dims[d].min = rset.dims[d].min + reachTime * allDerivatives[d].min;
	    rset.dims[d].max = rset.dims[d].max + reachTime * allDerivatives[d].max;
	}
    }
}
