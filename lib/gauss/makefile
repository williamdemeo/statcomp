# makefile for gn
HOME = /accounts/grad/chip
HOMELIB = $(HOME)/lib
INCL = -I$(HOMELIB)/include
CC = cc

# Variables for optimization on SUN
# Reference:  Sunsoft Performace Library
# /opt/SUNWspro/READMEs/libsunperf_preface.ps (p. viii)
LINK = -lsunperf -dalign -lblas
COMPILE = -dalign # use this option for compile command on single processor
MPCOMPILE = -dalign -mt  # multiprocessor compile command

gn.o: gn.c
	$(CC) $(COMPILE) $(INCL) -c gn.c

clean:
	rm *.o *.a *~ 


