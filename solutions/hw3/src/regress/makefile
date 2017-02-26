# makefile for regress.c
HOME = /accounts/grad/chip
UTIL = $(HOME)/lib/util/util_lib.a
DECOMP = $(HOME)/lib/decomp/QR
INCL = -I$(HOME)/lib/include
CC = cc

# Variables for optimization on SUN
# Reference:  Sunsoft Performace Library
# /opt/SUNWspro/READMEs/libsunperf_preface.ps (p. viii)
LINK = -lsunperf -dalign -lblas # use these for link command
COMPILE = -dalign # use this option for compile command on single processor
MPCOMPILE = -dalign -mt  # multiprocessor compile command

regress: regress.o $(DECOMP)/House.o
	$(CC) -o regress regress.o $(DECOMP)/House.o $(LINK) $(UTIL)

regress.o: regress.c
	$(CC) $(COMPILE) $(INCL) -c regress.c

$(DECOMP)/House.o: $(DECOMP)/House.c
	$(CC) $(COMPILE) $(INCL) -c -o $(DECOMP)/House.o $(DECOMP)/House.c

clean:
	rm *.o *.a *~ 


