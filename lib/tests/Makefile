# makefile for junk
HOME = /accounts/grad/chip
HOMELIB = $(HOME)/lib
INCL = -I$(HOMELIB)/include
# CC = gcc
CC = cc
# Variables for optimization on SUN
# Reference:  Sunsoft Performace Library
# /opt/SUNWspro/READMEs/libsunperf_preface.ps (p. viii)
LINK = -lsunperf -dalign -lblas # use this option for link command
COMPILE = -dalign # use this option for compile command on single processor
MPCOMPILE = -dalign -mt  # multiprocessor compile command

# $(HOMELIB)/util/util_lib.a

junk: junk.o 
	$(CC) -o junk junk.o $(LINK) $(HOMELIB)/util/util_lib.a 

junk.o: junk.c
	$(CC) $(COMPILE) $(INCL) -c junk.c

clean:
	rm *.o *~
