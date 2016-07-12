main.ex: shared.o 
	clang++ -o main.ex shared.o 

shared.o: shared.cpp
	clang++ -c -std=c++14 -stdlib=libc++ shared.cpp
clean:
	rm *.o main.ex 
