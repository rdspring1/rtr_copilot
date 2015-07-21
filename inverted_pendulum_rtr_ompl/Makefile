OMPL_DIR = /usr
CXXFLAGS = -g -std=c++11
INCLUDE_FLAGS = -I${OMPL_DIR}/include
LD_FLAGS = -L${OMPL_DIR}/lib -lompl -lompl_app -lboost_program_options -lboost_system
CXX=g++

sim:
	/usr/bin/python inv_pen_sim.py

rtr: inverted_pendulum_model.o inv_pen_ctrl.o
	$(CXX) $(CXXFLAGS) -o rtr_test inverted_pendulum_model.o inv_pen_ctrl.o $(LD_FLAGS)

clean:
	rm -rf *.o
	rm -rf *.db

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDE_FLAGS) $< -o $@
