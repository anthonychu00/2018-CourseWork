import random
import numpy as np
from numpy import linalg as LA

def matrixMaker(runs):
    #a=np.matrix=[[0.0 for x in range(runs+1)]for y in range(runs+1)]
    shape=(runs+1,runs+1)
    a=np.zeros(shape)
    a[0][1]=1.0
    a[runs][runs]=1.0
    for x in range(1,runs):
        a[x][1]=.5
        a[x][x+1]=.5
    return a

def noRun(runs):
    matrix=matrixMaker(runs)
    newMatrix=matrix
    
    for x in range(200):
        newMatrix=np.matmul(newMatrix,matrix)

    for x in range(len(newMatrix)):
        print newMatrix[x]

def waitForRun(runs):
    count=1
    maxRun=1
    currentRun=1
    prevFlip=random.randint(0,1)
    while maxRun!=runs:
        currentFlip=random.randint(0,1)
        if currentFlip==prevFlip:
            currentRun+=1
        else:
            currentRun=1
        if currentRun>maxRun:
            maxRun=currentRun
        count+=1
        prevFlip=currentFlip
    #print count
    return count

def averageWaitRun(runs):
    countArr=[]
    for x in range(1000):
        countArr.append(waitForRun(runs))
    print sum(countArr)/1000.0
        
def limitingDistribution(runs):
    matrix=matrixMaker(runs)
    matrix[runs][1]=.5
    matrix[runs][runs]=.5
    #print matrix
    u=LA.eig(np.transpose(matrix))
    print np.real(u[0])
    print np.real(u[1])
    v=[u[1][j][0] for j in range(len(matrix))]
    print np.real(v)
    print np.real(v)/sum(np.real(v))

def proportion(runs,trials):
    propArray=[0 for x in range(runs)]
    prevFlip=random.randint(0,1)
    currentRun=1
    for x in range(trials):
        currentFlip=random.randint(0,1)
        if(currentFlip==prevFlip):
            if currentRun>=runs:
                propArray[runs-1]+=1
            else:
                propArray[currentRun-1]+=1
            currentRun+=1
        else:
            if currentRun>=runs:
                propArray[runs-1]+=1
            else:
                propArray[currentRun-1]+=1
            currentRun=1
        prevFlip=currentFlip
    propArray=[x/float(trials) for x in propArray]
    print propArray
        
    
    
    
    
#matrix=matrixMaker(7)
#for x in range(len(matrix)):
#    print matrix[x]
#noRun(6)
#averageWaitRun(7)
#limitingDistribution(7)
proportion(7,1000)
    
