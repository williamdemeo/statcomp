# makefile for test_utilities and junk
#HOME = /accounts/grad/chip
HOME = /home/chip/pub/computing
INCL = -I$(HOME)/lib/include
UTILCC = $(HOME)/lib/util/util_lib_cc.a
UTIL = $(HOME)/lib/util/util_lib.a

CC = cc
#CC = gcc
CCC = g++

# Variables for optimization on SUN
# Reference:  Sunsoft Performace Library
# /opt/SUNWspro/READMEs/libsunperf_preface.ps (p. viii)
LINK = -lsunperf -dalign -lblas # use this option for link command
COMPILE = -dalign # use this option for compile command on single processor
MPCOMPILE = -dalign -mt  # multiprocessor compile command

test_utilities: test_utilities.o
	$(CCC) -o test_utilities test_utilities.o $(UTILCC) -lm

test_utilities.o: test_utilities.cc
	$(CCC) $(INCL) -c test_utilities.cc

unsigned_long: unsigned_long.o
	$(CCC) -o unsigned_long unsigned_long.o $(UTILCC) -lm

unsigned_long.o: unsigned_long.cc
	$(CCC) $(INCL) -c unsigned_long.cc

junk: junk.o 
	$(CC) -o junk junk.o $(LINK) $(UTIL)

junk.o: junk.c
	$(CC) $(COMPILE) $(INCL) -c junk.c

clean:
	rm -f *.o *~
