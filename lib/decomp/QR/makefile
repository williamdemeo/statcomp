# makefile for householder
#HOME = /accounts/grad/chip
HOME = /home/chip/pub/computing
HOMELIB = $(HOME)/lib
INCL = -I$(HOMELIB)/include
CC = cc

# Variables for optimization on SUN
# Reference:  Sunsoft Performace Library
# /opt/SUNWspro/READMEs/libsunperf_preface.ps (p. viii)
LINK = -lsunperf -dalign -lblas
COMPILE = -dalign # use this option for compile command on single processor
MPCOMPILE = -dalign -mt  # multiprocessor compile command

# couldn't get this to work.  Only using House.c in other programs.
decomp.a: House.o 
	ar ruvs decomp.a House.o $(LINK)

House.o: House.c
	$(CC) $(COMPILE) $(INCL) -c House.c

clean:
	rm *.o *.a *~ 


