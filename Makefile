all: compile

compile: clean
	mkdir build
	cd build && cmake .. && $(MAKE)

ompl: compile
	./build/ompl_rtr_monitor > path.txt
	/usr/bin/python ./inverted_pendulum_rtr_ompl/animate.py path.txt 

pendulum: compile
	./build/rt_reachability PENDULUM > data.txt
	./plotSolution.py

vanderpol: compile
	./build/rt_reachability VANDERPOL > data.txt
	./plotSolution.py

visual_pendulum: compile
	./build/vector_field PENDULUM > data.txt
	./plotSolution.py "VectorField"

visual_vanderpol: compile
	./build/vector_field VANDERPOL > data.txt
	./plotSolution.py "VectorField"

ctags:
	ctags -R -f ./.git/tags .

clean:
	rm -rf build/
	rm -rf *.*~
	rm -rf data.txt
	rm -rf path*.txt
