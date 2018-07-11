from pylab import *
import matplotlib.pyplot as plt
import numpy.random as npr


def binom(n,k):
    prod = 1.0
    for j in range(k):
        prod = prod*(n-j)/(j+1)
    return prod

def wordPMF():
    distribution=[]
    for x in range(0,8):
        distribution.append((binom(15,x)*binom(85,7-x))/binom(100,7))
    bins=arange(0,8,1)
    stem(bins,distribution,linefmt='k-',markerfmt='ko',label='Experiment')
    xlabel("Number of words")
    ylabel("Chance")
    ylim(0,1)
    show()

def sumPMF():
    distribution=[]
    for x in range(3,8):
        distribution.append((binom(15,x)*binom(85,7-x))/binom(100,7))
    print sum(distribution)

def pmfChooser(n):#part 1.7
    distribution=[]
    for x in range(0,8):
        distribution.append((binom(15,x)*binom(85,7-x))/binom(100,7))
    expArray=npr.choice([0,1,2,3,4,5,6,7],n,p=distribution)

    print expArray
    print "Average is "+str(sum(expArray)/float(n))
    
        
    

#wordPMF()
#sumPMF()
pmfChooser(1000)
    
