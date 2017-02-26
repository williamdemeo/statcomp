protein <- read.table("prob1.dat",header=T)

attach(protein)

# First look at a simple scatter plot of protein vs. enzyme
motif()
plot(prot,enz)
dev.off()

