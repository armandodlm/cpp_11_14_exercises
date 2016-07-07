Pricer: Pricer.o MarketOrder.o LimitOrderBook.o
	clang++ -o Pricer MarketOrder.o LimitOrderBook.o Pricer.o

Pricer.o: Pricer.cpp
	clang++ -c -std=c++11 -stdlib=libc++ Pricer.cpp

LimitOrderBook.o: LimitOrderBook.cpp
	clang++ -c -std=c++11 -stdlib=libc++ LimitOrderBook.cpp

MarketOrder.o: MarketOrder.cpp
	clang++ -c -std=c++11 -stdlib=libc++ MarketOrder.cpp
clean:
	rm *.o Pricer
