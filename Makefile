all: compile

compile: clean
	mkdir build
	cd build && cmake .. && $(MAKE)

projection: compile
	./build/rtr_copilot > data.txt
	./plotSolution.py

visual: compile
	./build/vector_field > data.txt
	./plotSolution.py "VectorField"

clean:
	rm -rf build/
	rm -rf *.*~
	rm -rf data.txt
