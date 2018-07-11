import math
import random
import numpy as np

def generator():
    num=random.uniform(0,1)
    return math.pow(21,-num+1)-1

def generateMultiple(trials):#avg of one sample
    total=0
    for x in range(trials):
        total+=generator()
    return total/trials

##def multipleSampleOld(trials):
##    sampleArr=[]
##    total=0
##    num=0
##    differenceTotal=0
##    for x in range(trials):
##        num=generateMultiple(100)#change to 10000 for les than 10^-3, might run slow
##        total+=num
##        sampleArr.append(num)
##    avg=total/trials
##    print "Avg of all samples: "+str(avg)
##    for n in range(len(sampleArr)):
##        sampleArr[n]=sampleArr[n]-avg#subtracting mean from each value
##        sampleArr[n]=sampleArr[n]**2#squaring each difference
##        differenceTotal+=sampleArr[n]#adding upp squared differences to be averaged
##    differenceAvg=differenceTotal/trials
##    return math.sqrt(differenceAvg)

def multipleSample(trials):
    sampleArr=[]
    num=0
    differenceTotal=0
    for x in range(trials):
        num=generator()
        sampleArr.append(num)
    avg=sum(sampleArr)/trials
    print "Avg of all samples: "+str(avg)
    for n in range(len(sampleArr)):
        sampleArr[n]=sampleArr[n]-avg#subtracting mean from each value
        sampleArr[n]=sampleArr[n]**2#squaring each difference
        differenceTotal+=sampleArr[n]#adding upp squared differences to be averaged
    differenceAvg=differenceTotal/trials
    return math.sqrt(differenceAvg)




print "Standard dev: "+str(multipleSample(3500000))

        
        

