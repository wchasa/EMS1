CC=g++ -pg -std=gnu++11
CFLAGS=-O0 -g -Wall
my_fm:EMS.o
	g++ -O0 -g -Wall main.cpp EMS.o -o test
%.o:%.cpp *.h
	$(CC) -c  $(CFLAGS) $< -o $@
