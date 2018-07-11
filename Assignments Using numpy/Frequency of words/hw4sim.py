from pylab import *
import matplotlib.pyplot as plt
import numpy.random as npr
import random as rand
import math

def binom(n,k):
    prod = 1.0
    for j in range(k):
        prod = prod*(n-j)/(j+1)
    return prod

def poissonCalculator(n,p,k):
    lam=n*p
    return (math.pow(lam,k)/math.factorial(k))*math.pow(e,-lam)
    
poissonCalculator(1000,.0027,1)

def hw4sim():#part 2.4
    matches=0
    for x in range(0,1001):
        if rand.random()<0.0027:
            matches+=1
    if matches>10:
        return 10
    else:
        return matches

def allPMF():#part 2.5
    distributionExact=[]
    distributionPoisson=[]
    distributionExp=[]
    interExp=[0,0,0,0,0,0,0,0,0,0,0]

    for x in range(0,11):
        distributionExact.append(binom(1000,x)*math.pow(.0027,x)*math.pow(1-.0027,1000-x))
    for x in range(0,11):
        distributionPoisson.append(poissonCalculator(1000,.0027,x))
    for x in range(0,1001):
        matches=hw4sim()
        interExp[matches]+=1
    distributionExp=[x/1000.0 for x in interExp]
                                   
    bins1=arange(0,11,1)
    bins2=arange(.1,11.1,1)
    bins3=arange(.2,11.2,1)
    stem(bins3,distributionExact,linefmt='k-',markerfmt='C0o',label='Exact')
    stem(bins2,distributionPoisson,linefmt='k-',markerfmt='ko',label='Poisson')
    stem(bins1,distributionExp,linefmt='k-',markerfmt='C1o',label='Experiment')
    title("Finding a word on a page starting with q")
    xlabel("Number of q words found")
    ylabel("Probability")
    ylim(0,1)
    legend()
    show()
    

    

    
    
#print(hw4sim())
allPMF()
    
