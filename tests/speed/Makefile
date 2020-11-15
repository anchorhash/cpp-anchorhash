all: speed_test 
	
speed_test: speed_test.cpp ../../AnchorHashQre.cpp ../../AnchorHashQre.hpp
	g++ -Wall -o2 speed_test.cpp ../../AnchorHashQre.cpp -o speed_test -std=c++11
			
# Cleaning old files before new make
clean:
	rm -f *.o 
	rm -f *.txt
	rm -f speed_test 
