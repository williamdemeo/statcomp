# makefile for QR and QRpiv
#HOME = /accounts/grad/chip
HOME = /home/chip/pub/computing
UTIL = $(HOME)/lib/util/util_lib.a
DECOMP = $(HOME)/lib/decomp/QR
INCL = -I$(HOME)/lib/include -I$(HOME)/stat243/samples
CC = gcc

# Variables for optimization on SUN
# Reference:  Sunsoft Performace Library
# /opt/SUNWspro/READMEs/libsunperf_preface.ps (p. viii)
#LINK = -lsunperf -dalign -lblas # use these for link command
COMPILE = -dalign # use this option for compile command on single processor
MPCOMPILE = -dalign -mt  # multiprocessor compile command

# 2001.10.21: No longer using the Sunsoft Performance Library
#             Define new LINK variable here:
# Defines for use with ATLAS are in Make.inc
include Make.inc
COMPILE = 
QRpiv: QRpiv.o $(DECOMP)/House.o
	$(CC) -o QRpiv QRpiv.o $(DECOMP)/House.o $(UTIL) -L$(LIBdir) -lf77blas -lg2c -latlas -lm

QRpiv.o: QRpiv.c
	$(CC) $(COMPILE) $(INCL) -c QRpiv.c

QR: QR.o $(DECOMP)/House.o
	$(CC) -o QR QR.o $(DECOMP)/House.o $(UTIL) -L$(LIBdir) -lf77blas -lg2c -latlas -lm

QR.o: QR.c
	$(CC) $(COMPILE) $(INCL) -c QR.c

QRptime: QRptime.o $(DECOMP)/House.o
	$(CC) -o QRptime QRptime.o $(DECOMP)/House.o $(UTIL) -L$(LIBdir) -lf77blas -lg2c -latlas -lm

QRptime.o: QRptime.c
	$(CC) $(COMPILE) $(INCL) -c QRptime.c

QRtime: QRtime.o $(DECOMP)/House.o
	$(CC) -o QRtime QRtime.o $(DECOMP)/House.o $(UTIL) -L$(LIBdir) -lf77blas -lg2c -latlas -lm

QRtime.o: QRtime.c
	$(CC) $(COMPILE) $(INCL) -c QRtime.c

$(DECOMP)/House.o: $(DECOMP)/House.c
	$(CC) $(COMPILE) $(INCL) -c -o $(DECOMP)/House.o $(DECOMP)/House.c

clean:
	rm -f *.o *.a *~ 


