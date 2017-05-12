CC=g++ -pg -std=gnu++11
CFLAGS=-O3 -g -Wall
my_fm:EMS.o
	$(CC) $(CFLAGS) main.cpp EMS.o -o test.exe
%.o:%.cpp *.h
	$(CC) -c  $(CFLAGS) $< -o $@
clean:
	del *.o gmon.out
