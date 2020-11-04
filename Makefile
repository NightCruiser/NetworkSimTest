simulator : main.o
	g++ main.o -o simulator -std=c++11 -pthread -Wall -pedantic