all: compile
	./rt_reachability > data.txt
	./plotSolution.py

compile: util.c dynamics.c rt_face_lift.c rt_reachability.c
	gcc -std=c99 -pedantic dynamics.c util.c rt_face_lift.c rt_reachability.c -o rt_reachability

visual: util.c dynamics.c rt_face_lift.c vector_field.c
	gcc -std=c99 -pedantic dynamics.c util.c rt_face_lift.c vector_field.c -o vector_field
	./vector_field > data.txt
	./plotSolution.py "VectorField"

clean:
	rm -rf *.*~
	rm -rf rt_reachability
	rm -rf vector_field
