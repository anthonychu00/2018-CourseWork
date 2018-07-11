from pylab import *
import matplotlib.pyplot as plt
import numpy.random as npr
import math

def poissonCalculator(n,p,k):
    lam=n*p
    print (math.pow(lam,k)/math.factorial(k))*math.pow(e,-lam)
    
poissonCalculator(1000,.0027,1)
    
