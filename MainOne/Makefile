all: main
main: main.o
	g++ -o main.ex main.o

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o main.o main.ex
