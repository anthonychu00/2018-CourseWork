import math
import random



def monteCone():
    trials=1000
    hits=0
    for i in range(trials):#using a rectangular prism to encolse the fat cone
        x=random.uniform(-1,1)#x-coordinate
        y=random.uniform(-1,1)#y-coordinate
        z=random.uniform(0,1)#z-coordinate
        #print "x: " +str(x)
        #print "y: " +str(y)
        #print "z: " +str(z)
        if((z-.5)**2+y**2<=.25 and x<=2-8*math.sqrt(y**2+(z-.5)**2)):
            if(x**2+y**2<=1 and z<=1-math.sqrt(x**2+y**2)):
                hits+=1.0
                
    percentageHits=hits/trials
    print "Percentage of hits: "+str(percentageHits)
    return percentageHits *4 #since volume of rectangular prism is 4

def multipleTrials():
    trials=100
    total=0
    for i in range(trials):
        total+=monteCone()
    print "The volume of the cone is about "+ str(total/trials)

multipleTrials()
            
        
        
