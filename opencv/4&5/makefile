main: main.o grad_fun.o
	g++ -o main grad_fun.o main.o `pkg-config --libs opencv`
grad_fun.o: grad_fun.cpp grad_fun.h
	g++ -c grad_fun.cpp `pkg-config --cflags opencv`
main.o: main.cpp grad_fun.h
	g++ -c main.cpp `pkg-config --cflags opencv` 
.PHONY: clean
clean:
	rm main.o main grad_fun.o
