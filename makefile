CC=g++ -pg -std=gnu++11
CFLAGS=-O3  -Wall
my_fm:EMS.o
	$(CC) $(CFLAGS) main.cpp EMS.o -o test
%.o:%.cpp *.h
	$(CC) -c  $(CFLAGS) $< -o $@
