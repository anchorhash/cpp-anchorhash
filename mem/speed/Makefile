all: speed_test

speed_test: speed_test.cpp ../AnchorHash.cpp ../AnchorHash.hpp
	g++ -Wall -o2 speed_test.cpp ../AnchorHash.cpp -o speed_test -std=c++11

# Cleaning old files before new make
clean:
	rm -f *.o
	rm -f *.txt
	rm -f speed_test
