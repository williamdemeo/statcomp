# makefile for sweeptest
HOME = /accounts/grad/chip
UTIL = $(HOME)/lib/util/util_lib.a
SWEEP = $(HOME)/lib/sweep
INCL = -I$(HOME)/lib/include
CC = cc

# Variables for optimization on SUN
# Reference:  Sunsoft Performace Library
# /opt/SUNWspro/READMEs/libsunperf_preface.ps (p. viii)
LINK = -lsunperf -dalign -lblas # use these for link command
COMPILE = -dalign # use this option for compile command on single processor
MPCOMPILE = -dalign -mt  # multiprocessor compile command

sweeptest: sweeptest.o $(SWEEP)/sweep.o
	$(CC) -o sweeptest sweeptest.o $(SWEEP)/sweep.o $(LINK) $(UTIL)

sweeptest.o: sweeptest.c
	$(CC) $(COMPILE) $(INCL) -c sweeptest.c

$(SWEEP)/sweep.o: $(SWEEP)/sweep.c
	$(CC) $(COMPILE) $(INCL) -c -o $(SWEEP)/sweep.o $(SWEEP)/sweep.c

# debugging sweep and sweeptest

sweeptest_d: sweeptest_d.o $(SWEEP)/sweep_d.o
	$(CC) -o sweeptest_d sweeptest_d.o $(SWEEP)/sweep_d.o $(LINK) $(UTIL)

sweeptest_d.o: sweeptest.c
	$(CC) $(COMPILE) $(INCL) -o sweeptest_d.o -c -g sweeptest.c

$(SWEEP)/sweep_d.o: $(SWEEP)/sweep.c
	$(CC) $(COMPILE) $(INCL) -o $(SWEEP)/sweep_d.o -c -g $(SWEEP)/sweep.c

clean:
	rm *.o *.a *~ 

