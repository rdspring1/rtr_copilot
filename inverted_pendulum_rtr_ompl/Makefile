OMPL_DIR = /usr
CXXFLAGS = -g -std=c++11
INCLUDE_FLAGS = -I${OMPL_DIR}/include
LD_FLAGS = -L${OMPL_DIR}/lib -lompl -lompl_app -lboost_program_options -lboost_system
CXX=g++

animate: rtr
	./rtr_test
	/usr/bin/python animate.py path.txt 

rtr: inverted_pendulum_model.o pid_ctrl.o
	$(CXX) $(CXXFLAGS) -o rtr_test inverted_pendulum_model.o pid_ctrl.o $(LD_FLAGS)

sim:
	/usr/bin/python inv_pen_sim.py

clean:
	rm -rf *.o
	rm -rf *.db
	rm -rf path.txt
	rm -rf rtr_test

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDE_FLAGS) $< -o $@
