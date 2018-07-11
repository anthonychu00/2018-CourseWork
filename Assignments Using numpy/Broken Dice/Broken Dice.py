from pylab import *
import matplotlib.pyplot as plt
import numpy.random as npr
import numpy as np
import matplotlib.mlab as mlab
import math
import scipy
import scipy.stats

def plotPMF():
    bins=[1,2,4,5,6]
    #values=rollBrokenDie(1000)
    values=[1.0/6,2.0/6,1.0/6,1.0/6,1.0/6]
    stem([1,2,4,5,6],values,linefmt='k-',markerfmt='ko')
    plt.xlabel('Number on dice')
    plt.ylabel('Probability')
    plt.title('Rolling a damaged dice')
    show()
def rollBrokenDie(n):
    values=[1.0/6,2.0/6,1.0/6,1.0/6,1.0/6]
    expArray=npr.choice([1,2,4,5,6],n,p=values)
    #print expArray
    return expArray

def inBetween(lower,upper,n,diceRolls):
    inRange=0
    for x in range(n):
        total=sum(rollBrokenDie(diceRolls))
        if(total>=lower and total <=upper):
            inRange+=1.0
    print inRange/n

def plotNormal(n,expected,variance,diceRolls):
    sumArray=[]
    expectedValue=expected*diceRolls
    std=math.sqrt(variance*diceRolls)
    for x in range(n):
        sumArray.append(sum(rollBrokenDie(diceRolls)))
        sumArray[x]=(sumArray[x]-expectedValue)/std
        sumArray[x]=round(sumArray[x])
    print sumArray
    bins=arange(-2,4,1)
    h=histogram(sumArray,bins)
    mu = 0
    variance = 1
    sigma = math.sqrt(variance)
    x = np.linspace(mu - 3*sigma, mu + 3*sigma, 100)
    plt.plot(x,mlab.normpdf(x, mu, sigma))
    stem(range(-2,3),h[0]/1000.0,linefmt='k-',markerfmt='ko')
    title('Tossing a damaged die many times')
    xlabel('Standard deviations from mean')
    ylabel('Occurences')
    show()

def part2i(n,expected,variance,diceRolls):
    sumArray=[]
    expectedValue=expected*diceRolls
    std=math.sqrt(variance*diceRolls)
    for x in range(n):
        sumArray.append(sum(rollBrokenDie(diceRolls)))
        sumArray[x]=(sumArray[x]-expectedValue)/std
        sumArray[x]=round(sumArray[x])
    #print sumArray
    v=scipy.stats.probplot(sumArray,plot=plt)
    plt.show()
                        
    
    
    
        
part2i(1000,3.333,3.24,50)    
#plotNormal(1000,3.333,3.24,50)
#inBetween(150,200,1000,50)




