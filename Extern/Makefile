ext: sourceOne.o sourceTwo.o
	clang++ -o ext sourceTwo.o sourceOne.o 

sourceOne.o: sourceOne.cpp
	clang++ -c -std=c++11 -stdlib=libc++ sourceOne.cpp

sourceTwo.o: sourceTwo.cpp
	clang++ -c -std=c++11 -stdlib=libc++ sourceTwo.cpp
clean:
	rm *.o ext
