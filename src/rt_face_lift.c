#include "rt_face_lift.h"

void face_lift(double reachTimeRemaining)
{
	int rnds = 0;
	while(reachTimeRemaining > 0)
	{
		print_rset();
		assert(check_rset());

		// min / max derivative for each neighborhood to determine minimum reach-time
		struct Interval allDerivatives[NUM_STATES];
		struct Interval neighborhoodWidths[NUM_STATES];
		constructNeighborhoods(allDerivatives, neighborhoodWidths);

		// for each neighborhood, reach-time = neighborhood-width / (min/max) derivative
		double crossReachTime = minCrossReachTime(allDerivatives, neighborhoodWidths);
		assert(crossReachTime >= (reachTimeStep / 2.0));

		double advanceReachTime = min(crossReachTime, reachTimeRemaining);
		advanceBox(allDerivatives, advanceReachTime);

		reachTimeRemaining -= advanceReachTime;
		//printf("remaining time: %f\n", reachTimeRemaining);
	}
	//printf("Round: %d\t", rnds);
}

bool check_rset()
{
	int maxPts = floor(pow(2, NUM_STATES));
	for(int pt = 0; pt < maxPts; ++pt)
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
			print_state(HyperPoint);
			return false;
		}
	}
	return true;
}

// Step 1 - Determine the maximum derivative for each face of the HyperRectangle
// Step 2 - Construct the neighborhood HyperRectangles for each face
// Step 3 - Check inward facing neighborhoods for an outward facing derivative
// Step 3 - Check if a derivative is double the previous derivative along a neighborhood face
// Step 3 - Repeat Step 2 if the either condition occurs
void constructNeighborhoods(struct Interval* allDerivatives, struct Interval* neighborhoodWidths)
{
	// Calculate derivative for each flat face
	for(int d = 0; d < NUM_STATES; ++d)
	{
		for(int max = 0; max < 2; ++max)
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
			double neighborhoodWidth = faceDerivative * reachTimeStep;
			if(!max) // min
			{
				allDerivatives[d].min = faceDerivative;
				neighborhoodWidths[d].min = neighborhoodWidth;
			}
			else
			{
				allDerivatives[d].max = faceDerivative;
				neighborhoodWidths[d].max = neighborhoodWidth;
			}
		}
	}

	// Resample Derivatives
	// While Loop - Reconstruct Neighborhoods
	bool reconstruct = true;
	while(reconstruct)
	{
		reconstruct = false;
		// Construct neighborhoods
		for(int d = 0; d < NUM_STATES; ++d)
		{
			for(int max = 0; max < 2; ++max)
			{
				struct HyperRect neighborhood;
				neighborhood = rset;
				double width;

				// Which face in the dimension are we expanding?
				if(!max) // min
				{
					neighborhood.dims[d].max = neighborhood.dims[d].min;
					width = neighborhoodWidths[d].min;
				}
				else // max
				{
					neighborhood.dims[d].min = neighborhood.dims[d].max;
					width = neighborhoodWidths[d].max;
				}

				// Expand the main side of the neighborhood
				if(width > 0)
				{
					neighborhood.dims[d].max += width;
				}
				else
				{
					neighborhood.dims[d].min += width;
				}

				// Expand the other sides of the neighborhood
				for(int other_dim = 0; other_dim < NUM_STATES; ++other_dim)
				{
					if(other_dim != d)
					{
						if(neighborhoodWidths[other_dim].min < 0)
						{
							neighborhood.dims[other_dim].min += neighborhoodWidths[other_dim].min;
						}

						if(neighborhoodWidths[other_dim].max > 0)
						{
							neighborhood.dims[other_dim].max += neighborhoodWidths[other_dim].min;
						}
					}
					assert(neighborhood.dims[d].min <= neighborhood.dims[d].max);
				}

				struct Interval neighborhoodInterval = getMinMaxDerivative(d, &neighborhood);
				if(!max)
				{
					if(resample_derivative(&reconstruct, max, allDerivatives[d].min, neighborhoodInterval.min))
					{
						neighborhoodWidths[d].min = neighborhoodInterval.min * reachTimeStep;
					}
					allDerivatives[d].min = neighborhoodInterval.min;
				}
				else
				{
					if(resample_derivative(&reconstruct, max, allDerivatives[d].max, neighborhoodInterval.max))
					{
						neighborhoodWidths[d].max = neighborhoodInterval.max * reachTimeStep;
					}
					allDerivatives[d].max = neighborhoodInterval.max;
				}
			}
		}
	}

	// for each neighborhood, correct neighborhood-width
	for(int d = 0; d < NUM_STATES; ++d)
	{
		neighborhoodWidths[d].min = absolute(neighborhoodWidths[d].min);
		neighborhoodWidths[d].max = absolute(neighborhoodWidths[d].max);
	}
}

bool resample_derivative(bool* reconstruct, int max, double prevDerivative, double currDerivative)
{
	bool flip = false;
	if(!max)
	{
		// inward facing if derivative is positive
		flip = (prevDerivative > 0) && (currDerivative < 0);
	}
	else
	{
		// inward facing if derivative is negative
		flip = (prevDerivative < 0) && (currDerivative > 0);
	}
	bool doubleSize = absolute(currDerivative) > (absolute(prevDerivative) * 2.0);
	if(!(*reconstruct))
	{
		*reconstruct = (flip || doubleSize);
	}
	return (flip || doubleSize);
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
	for(int pt = 0; pt < maxPts; ++pt)
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
		double dv = derivative(dim, HyperPoint);
		rv.min = min(rv.min, dv);
		rv.max = max(rv.max, dv);
	}

	// TODO Check inflection points of the dynamical system
	return rv;
}

double minCrossReachTime(struct Interval* allDerivatives, struct Interval* neighborhoodWidths)
{
	double minTime = DBL_MAX;
	for(int d = 0; d < NUM_STATES; ++d)
	{
		double absMin = absolute(allDerivatives[d].min);
		if(absMin > EPSILON)
		{
			double minTimeDim = neighborhoodWidths[d].min / absMin;
			minTime = min(minTime, minTimeDim);
			//printf("width: %f div: %f min: %f\n", neighborhoodWidths[d].min, absMin, minTimeDim);
		}

		double absMax = absolute(allDerivatives[d].max);
		if(absMax > EPSILON)
		{
			double maxTimeDim = neighborhoodWidths[d].max / absMax;
			minTime = min(minTime, maxTimeDim);
			//printf("width: %f div: %f max: %f\n", neighborhoodWidths[d].max, absMax, maxTimeDim);
		}
	}
	//printf("minTime: %f\n", minTime);
	return minTime;
}

void advanceBox(struct Interval* allDerivatives, double reachTime)
{
	if(reachTime < DBL_MAX)
	{
		for(int d = 0; d < NUM_STATES; ++d)
		{
			rset.dims[d].min += reachTime * allDerivatives[d].min;
			rset.dims[d].max += reachTime * allDerivatives[d].max;
		}
	}
}
