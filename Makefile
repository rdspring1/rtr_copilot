all: compile

compile: clean
	mkdir build
	cd build && cmake .. && $(MAKE)

pendulum: compile
	./build/rt_reachability PENDULUM > data.txt
	./plotSolution.py

vanderpol: compile
	./build/rt_reachability VANDERPOL > data.txt
	./plotSolution.py

visual_pendulum: compile
	./build/pendulum_vector_field > data.txt
	./plotSolution.py "VectorField"

visual_vanderpol: compile
	./build/vanderpol_vector_field > data.txt
	./plotSolution.py "VectorField"

ctags:
	ctags -R -f ./.git/tags .

clean:
	rm -rf build/
	rm -rf *.*~
	rm -rf data.txt
