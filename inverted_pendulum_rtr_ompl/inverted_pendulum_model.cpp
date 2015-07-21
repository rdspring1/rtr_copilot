#include <ompl/control/SpaceInformation.h>
#include <ompl/base/spaces/SE2StateSpace.h>
#include <ompl/control/spaces/RealVectorControlSpace.h>
#include <ompl/control/ODESolver.h>
#include <ompl/control/SimpleSetup.h>
#include <ompl/tools/benchmark/Benchmark.h>
#include <omplapp/config.h>
#include <ompl/config.h>
#include <iostream>
#include <valarray>
#include <limits>
#include <fstream>
#include <vector>
#include <math.h>

const double epsilon = 0.01;
const double radius = 0.1;
const double square = 0.125;
const double g = 9.81;

// Pendulum Limits
const double torque_limit = M_PI;
const double pen_velocity_limit = 2*M_PI;

typedef std::pair<double, double> Point2D;
typedef std::vector<Point2D> Rect;

namespace ob = ompl::base;
namespace oc = ompl::control;

double dist(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

// Definition of the ODE for the pendulum
void PendulumODE (const oc::ODESolver::StateType& q, const oc::Control* control, oc::ODESolver::StateType& qdot)
{
	const double* u = control->as<oc::RealVectorControlSpace::ControlType>()->values;
	const double theta = q[0];
	const double omega = q[1];

	// Zero out qdot
	qdot.resize (q.size (), 0);

	qdot[0] = omega;
	qdot[1] = -g*cos(theta) + u[0];
}

// This is a callback method invoked after numerical integration.
void PendulumPostIntegration (const ob::State* /*state*/, const oc::Control* /*control*/, const double /*duration*/, ob::State *result)
{
	// Normalize orientation between -pi and pi
	ob::SO2StateSpace SO2;
	SO2.enforceBounds (result->as<ob::CompoundState>()->as<ob::SO2StateSpace::StateType>(0));
}

bool isStateValidPen(const ob::State *state)
{
	/// cast the abstract state type to the type we expect
	const ompl::base::CompoundState* cstate;
	cstate = state->as<ompl::base::CompoundState>();

	/// extract the first component of the state and cast it to what we expect - angle orientation
	const ob::SO2StateSpace::StateType *rot = cstate->as<ob::SO2StateSpace::StateType>(0);

	/// extract the second component of the state and cast it to what we expect - angular velocity
	const ob::RealVectorStateSpace::StateType *vel = cstate->as<ob::RealVectorStateSpace::StateType>(1);

	if(vel->values[0] > pen_velocity_limit)
		return false;
	else if(vel->values[0] < -pen_velocity_limit)
		return false;
	else
		return true;
}

/// @cond IGNORE
// torque
class PenControlSpace : public oc::RealVectorControlSpace
{
	public:
		PenControlSpace(const ob::StateSpacePtr &stateSpace) : oc::RealVectorControlSpace(stateSpace, 1) {}
};
/// @endcond

void planWithSimpleSetupPen(int plannertype, std::vector<Rect> obstacles, std::string title = "Default", bool benchmark = false)
{
	// theta, angular veloctiy
	ompl::base::StateSpacePtr space;
	ompl::base::StateSpacePtr so2(new ompl::base::SO2StateSpace());
	ompl::base::StateSpacePtr r(new ompl::base::RealVectorStateSpace(1));

	ompl::base::RealVectorBounds velocity_limit(1);
	velocity_limit.setLow(-pen_velocity_limit);
	velocity_limit.setHigh(pen_velocity_limit);
	r->as<ompl::base::RealVectorStateSpace>()->setBounds(velocity_limit);

	space = so2 + r;

	// create a control space
	oc::ControlSpacePtr cspace(new PenControlSpace(space));

	// set the bounds for the control space
	ob::RealVectorBounds cbounds(1);
	cbounds.setLow(0);
	cbounds.setHigh(torque_limit);
	cspace->as<PenControlSpace>()->setBounds(cbounds);

	// define a simple setup class
	oc::SimpleSetup ss(cspace);

	// set state validity checking for this space
	ss.setStateValidityChecker(isStateValidPen);

	// Use the ODESolver to propagate the system.  Call KinematicCarPostIntegration
	// when integration has finished to normalize the orientation values.
	oc::ODESolverPtr odeSolver(new oc::ODEBasicSolver<> (ss.getSpaceInformation(), &PendulumODE));
	ss.setStatePropagator(oc::ODESolver::getStatePropagator(odeSolver));

	/// create a start state
	ob::ScopedState<> start(space);
	start[0] = -M_PI/2;
	start[1] = 0.0;

	/// create a  goal state; use the hard way to set the elements
	ob::ScopedState<> goal(space);
	goal[0] = M_PI/2;
	goal[1] = 0.0;

	/// set the start and goal states
	ss.setStartAndGoalStates(start, goal, 0.15);

	ss.getSpaceInformation()->setPropagationStepSize(0.01);
	ompl::base::PlannerPtr planner(new ompl::control::RGRRT(ss.getSpaceInformation()));
	ss.setPlanner(planner);

	ss.setup();

	/// attempt to solve the problem within one second of planning time
	ob::PlannerStatus solved = ss.solve(20.0);

	if (solved)
	{
		std::cout << "Found solution:" << std::endl;
		ompl::control::PathControl& path = ss.getSolutionPath();
		path.printAsMatrix(std::cout);

		// print path to file
		std::ofstream fout("path.txt");
		fout << "Pen" << std::endl;
		path.printAsMatrix(fout);
		fout.close();
	}
}

int main(int, char **)
{
	std::cout << "OMPL version: " << OMPL_VERSION << std::endl;
	planWithSimpleSetupPen(0, obstacles[0], "Benchmark-Pendulum", true);
	return 0;
}
