# makefile for regress.c
HOME = /accounts/grad/chip
UTIL = $(HOME)/lib/util/util_lib.a
DECOMP = $(HOME)/lib/decomp/QR
GAUSS = $(HOME)/lib/gauss
INCL = -I$(HOME)/lib/include
CC = cc

# Variables for optimization on SUN
# Reference:  Sunsoft Performace Library
# /opt/SUNWspro/READMEs/libsunperf_preface.ps (p. viii)
LINK = -lsunperf -dalign -lblas # use these for link command
COMPILE = -dalign # use this option for compile command on single processor
MPCOMPILE = -dalign -mt  # multiprocessor compile command

nlstest: nlstest.o $(DECOMP)/House.o $(GAUSS)/gn.o
	$(CC) -o nlstest nlstest.o $(DECOMP)/House.o $(GAUSS)/gn.o $(LINK) $(UTIL)

nlstest.o: nlstest.c
	$(CC) $(COMPILE) $(INCL) -c nlstest.c

$(DECOMP)/House.o: $(DECOMP)/House.c
	$(CC) $(COMPILE) $(INCL) -c -o $(DECOMP)/House.o $(DECOMP)/House.c

$(GAUSS)/gn.o: $(GAUSS)/gn.c
	$(CC) $(COMPILE) $(INCL) -c -o $(GAUSS)/gn.o $(GAUSS)/gn.c

clean:
	rm *.o *.a *~ 


