stat: stat.o
	clang++ -o stat stat.o 

stat.o: stat.cpp
	clang++ -c -std=c++11 -stdlib=libc++ stat.cpp
clean:
	rm *.o stat
