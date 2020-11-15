all: balance 
	
balance: balance.cpp ../../AnchorHashQre.cpp ../../AnchorHashQre.hpp
	g++ -Wall -o2 balance.cpp ../../AnchorHashQre.cpp -o balance -std=c++11
			
# Cleaning old files before new make
clean:
	rm -f *.o 
	rm -f *.txt
	rm -f balance 
