all: clock movieTimes
	g++ -pedantic-errors -g main.cpp movieTimes clock -o main
clock: clock.h clock.cpp
	g++ -pedantic-errors -g -c clock.cpp -o clock
movieTimes: movieTimes.h movieTimes.cpp
	g++ -pedantic-errors -g -c movieTimes.cpp -o movieTimes