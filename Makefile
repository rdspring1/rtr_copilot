all: compile
	./test > data.txt
	./plotSolution.py

compile: util.c dynamics.c rt_face_lift.c test.c
	gcc -std=c99 -pedantic dynamics.c util.c rt_face_lift.c test.c -o test

clean:
	rm -rf *.*~
	rm -rf test
