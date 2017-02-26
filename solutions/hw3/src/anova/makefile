# Makefile for anova

HOME = /accounts/grad/chip
UTIL = $(HOME)/lib/util/util_lib.a
NORMAL = $(HOME)/lib/random/normal
UNIFORM = $(HOME)/lib/random/uniform
DECOMP = $(HOME)/lib/decomp/cholesky
MOMENT = $(HOME)/lib/moment
INCL = -I$(HOME)/lib/include
NAG =  -R/usr/local/lib -lnag -lF77 -lM77 -lsunmath -lm

CC = cc

anova: anova.o $(NORMAL)/normal.o $(UNIFORM)/unif.o $(MOMENT)/moment.o $(DECOMP)/cholesky.o $(UTIL)
	$(CC) -o anova  anova.o $(NORMAL)/normal.o $(UNIFORM)/unif.o $(MOMENT)/moment.o $(DECOMP)/cholesky.o $(UTIL) $(NAG)

anova.o: anova.c
	$(CC) $(INCL) -c anova.c 

$(NORMAL)/normal.o: $(NORMAL)/normal.c
	$(CC) $(INCL) -c -o $(NORMAL)/normal.o $(NORMAL)/normal.c 

$(UNIFORM)/unif.o: $(UNIFORM)/unif.c
	$(CC) $(INCL) -c -o $(UNIFORM)/unif.o $(UNIFORM)/unif.c 

$(MOMENT)/moment.o: $(MOMENT)/moment.c
	$(CC) -c -o $(MOMENT)/moment.o $(MOMENT)/moment.c

$(DECOMP)/cholesky.o: $(DECOMP)/cholesky.c
	$(CC) -c -o $(DECOMP)/cholesky.o $(DECOMP)/cholesky.c

clean:
	rm *.o *~
