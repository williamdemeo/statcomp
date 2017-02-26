# Makefile for random

HOME = /accounts/grad/chip
UTIL = $(HOME)/lib/util/util_lib.a
NORMAL = $(HOME)/lib/random/normal
UNIFORM = $(HOME)/lib/random/uniform
INCL = -I$(HOME)/lib/include
MOMENT = $(HOME)/lib/moment
CC = cc

random: random.o $(NORMAL)/normal.o $(UNIFORM)/unif.o $(MOMENT)/moment.o $(UTIL)
	$(CC) -o random  random.o $(NORMAL)/normal.o $(UNIFORM)/unif.o $(MOMENT)/moment.o $(UTIL) -lm

random.o: random.c
	$(CC) $(INCL) -c random.c 

$(NORMAL)/normal.o: $(NORMAL)/normal.c
	$(CC) $(INCL) -c -o $(NORMAL)/normal.o $(NORMAL)/normal.c 

$(UNIFORM)/unif.o: $(UNIFORM)/unif.c
	$(CC) $(INCL) -c -o $(UNIFORM)/unif.o $(UNIFORM)/unif.c 

$(MOMENT)/moment.o: $(MOMENT)/moment.c
	$(CC) -c -o $(MOMENT)/moment.o $(MOMENT)/moment.c

clean:
	rm *.o *~
