# HOME = /accounts/grad/chip
HOME = /home/chip/pub/computing
HOMELIB = $(HOME)/lib
INCL = -I$(HOMELIB)/include
CC = gcc
CCC = g++
# CC = cc

# util_lib_cc is the g++ version of the utilities library
util_lib_cc.a: utilities_cc.o misc_cc.o
	ar ruvs util_lib_cc.a utilities_cc.o misc_cc.o

utilities_cc.o: utilities.cc
	$(CCC) $(INCL) -c -o utilities_cc.o utilities.cc

misc_cc.o: misc.cc
	$(CCC) $(INCL) -c -o misc_cc.o misc.cc


# util_lib is the gcc version of the utilities library
util_lib.a: utilities.o misc.o
	ar ruvs util_lib.a utilities.o misc.o

utilities.o: utilities.c
	$(CC) $(INCL) -c utilities.c 

misc.o: misc.c
	$(CC) $(INCL) -c misc.c


# program to compute machine constants
mconstants: mconstants.o
	$(CC) -o mconstants mconstants.o

mconstants.o: mconstants.c
	$(CC) -c mconstants.c


clean:
	rm -f *.o
