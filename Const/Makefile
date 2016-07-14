cons: const.o
	clang++ -o cons const.o 

const.o: const.cpp
	clang++ -c -std=c++11 -stdlib=libc++ const.cpp
clean:
	rm *.o cons 
