# makefile for cholesky
HOME = /accounts/grad/chip
UTIL = $(HOME)/lib/util/util_lib.a
DECOMP = $(HOME)/lib/decomp/cholesky
INCL = -I$(HOME)/lib/include
CC = cc

# Variables for optimization on SUN
# Reference:  Sunsoft Performace Library
# /opt/SUNWspro/READMEs/libsunperf_preface.ps (p. viii)
LINK = -lsunperf -dalign -lblas # use these for link command
COMPILE = -dalign # use this option for compile command on single processor
MPCOMPILE = -dalign -mt  # multiprocessor compile command

cholesky: cholesky.o $(DECOMP)/cholesky.o
	$(CC) -o cholesky cholesky.o $(DECOMP)/cholesky.o $(LINK) $(UTIL)

cholesky.o: cholesky.c
	$(CC) $(COMPILE) $(INCL) -c cholesky.c

$(DECOMP)/cholesky.o: $(DECOMP)/cholesky.c
	$(CC) $(COMPILE) $(INCL) -c -o $(DECOMP)/cholesky.o $(DECOMP)/cholesky.c

clean:
	rm *.o *.a *~ 


