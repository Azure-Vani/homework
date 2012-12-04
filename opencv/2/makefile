main: main.o
	g++ -o main main.o `pkg-config --libs opencv`
main.o: main.cpp cv.h
	g++ -c main.cpp `pkg-config --cflags opencv` 
.PHONY: clean
clean:
	rm main.o main
