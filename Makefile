all:
	g++ *.cpp -lglut -lGLU -lGL -w
run:
	g++ *.cpp -lglut -lGLU -lGL -w
	./a.out
