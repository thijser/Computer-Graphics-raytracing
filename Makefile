all:
	g++ *.cpp -lglut -lGLU -lGL
run:
	g++ *.cpp -lglut -lGLU -lGL
	./a.out
