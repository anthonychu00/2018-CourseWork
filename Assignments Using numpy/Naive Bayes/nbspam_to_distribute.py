#Construct a Spam filter using Naive Bayes Classifier
import math
import random



def text_process(text):
    stopwords={'ourselves', 'hers', 'between', 'yourself', 'but', 'again',\
       'there', 'about', 'once', 'during', 'out', 'very', 'having',\
       'with', 'they', 'own', 'an', 'be', 'some', 'for', 'do', 'its',\
       'yours', 'such', 'into', 'of', 'most', 'itself', 'other',\
       'off', 'is', 's', 'am', 'or', 'who', 'as', 'from', 'him', \
       'each', 'the', 'themselves', 'until', 'below', 'are', 'we', \
       'these', 'your', 'his', 'through', 'don', 'nor', 'me', 'were',\
       'her', 'more', 'himself', 'this', 'down', 'should', 'our', 'their',\
       'while', 'above', 'both', 'up', 'to', 'ours', 'had', 'she', 'all',\
       'no', 'when', 'at', 'any', 'before', 'them', 'same', 'and', 'been',\
       'have', 'in', 'will', 'on', 'does', 'yourselves', 'then', 'that',\
       'because', 'what', 'over', 'why', 'so', 'can', 'did', 'not', 'now',\
       'under', 'he', 'you', 'herself', 'has', 'just', 'where', 'too',\
       'only', 'myself', 'which', 'those', 'i', 'after', 'few', 'whom',\
       't', 'being', 'if', 'theirs', 'my', 'against', 'a', 'by', 'doing',\
       'it', 'how', 'further', 'was', 'here', 'than'}
    text = text.translate(string.maketrans('', ''), string.punctuation)
    #print text
    text = [word.lower() for word in text.split() if word.lower() not in stopwords]
    return text
 

def clean():
    f=open('spam2.csv','r')
    ham=open('ham_sms.txt','w')
    spam=open('spam_sms.txt','w')
    for s in f:
        start=s.index(',')
        u=s[start+1:]
        ulist=text_process(u)
        if s[:3]=='ham':
            ham.write(" ".join(ulist)+'\n')
        else:
            spam.write(" ".join(ulist)+'\n')
    ham.close()
    spam.close()


def separate():
    f=open('ham_sms.txt','r')
    g1=open('ham_sms_training','w')
    g2=open('ham_sms_test','w')
    for j in range(2413):
        s=f.readline()
        g1.write(s)
    for j in range(2414):
        s=f.readline()
        g2.write(s)
    g1.close()
    g2.close()
    f=open('spam_sms.txt','r')
    g1=open('spam_sms_training','w')
    g2=open('spam_sms_test','w')
    for j in range(373):
        s=f.readline()
        g1.write(s)
    for j in range(374):
        s=f.readline()
        g2.write(s)
    g1.close()
    g2.close()

    
def build_models():
    spamTrain=open('spam_sms_training','r')
    hamTrain=open('ham_sms_training','r')
    spamModel= dict()
    hamModel= dict()
    spamCount=0
    hamCount=0
    spamBegin=spamTrain.tell()
    hamBegin=hamTrain.tell()
    distinctWords=0
    spamLength=0
    hamLength=0
    for x in range(373):#train spam first and find spam length
        s=spamTrain.readline()
        sArr=s.split()
        for word in sArr:
            if word in spamModel:
                spamModel[word]+=1.0
            else:
                spamModel[word]=1.0
            spamLength+=1.0
                 
    for x in range(2413):#train ham second and find ham length
        s=hamTrain.readline()
        sArr=s.split()
        for word in sArr:
            if word in hamModel:
                hamModel[word]+=1.0
            else:
                hamModel[word]=1.0
            hamLength+=1.0

    spamTrain.seek(spamBegin)
    hamTrain.seek(hamBegin)
    #print(hamModel)
    
    for key in spamModel:#adds one to every existing word in spamModel
        spamModel[key]+=1.0
    for key in hamModel:#adds one to every existing word in hamModel
        hamModel[key]+=1.0

    
    for x in range(373):#smoothing ham by adding nonexistent words
        s=spamTrain.readline()
        sArr=s.split()
        for word in sArr:
            if word in hamModel:
                pass
            else:
                hamModel[word]=1.0

    for x in range(2413):#smoothing spam by adding nonexistent words
        s=hamTrain.readline()
        sArr=s.split()
        for word in sArr:
            if word in spamModel:
                pass
            else:
                spamModel[word]=1.0
                
    distinctWords=len(spamModel)#doesnt really matter which one you pull from since the lengths should be same

    for key in spamModel:#taking logarithm of spam
        spamModel[key]=math.log(spamModel[key]/(spamLength+distinctWords))
    for key in hamModel:#taking logarithm of spam
        hamModel[key]=math.log(hamModel[key]/(hamLength+distinctWords))
        
    
    #print distinctWords
    #print spamLength
    #print hamLength
    #print(spamModel)
    #print(hamModel)              
    tupleDict= (spamModel,hamModel)
    return tupleDict
    
#The message is a string that has already been
#parsed into non-stop words, such as one of the lines
#of the training or test files.  The model is a dictionary
#modeling a class, as returned by build_model. prior is
#the prior probability of membership in the class
    
def score(msg,model,prior):
    score=0.0
    strArr=msg.split()
    for word in strArr:
        if word in model:
            score+=model[word]
        else:
            pass
    return score+math.log(prior)
        


#Now evaluate the classifier. Do 1000 trials or randomly selecting
#a message from the entire test corpus  (2414 ham messages, 374 spam).
#Score each message to classify it as ham or spam.  Print out four
#values--the proportion of ham messages correctly identified as ham,
#misidentified as spam, and the proportion of spam messages correctly
#identified as spam, and misidentified as ham:
    
def evaluate():
    modelTuple=build_models()#modelTuple[0] is spam, modelTuple[1] is ham
    spamTest=open('spam_sms_test','r')
    hamTest=open('ham_sms_test','r')
    unionList=[]
    unionDict=dict()
    msg=""
    spamPrior=.2
    hamPrior=.8
    spamScore=hamScore=spamCorrect=hamCorrect=spamIncorrect=hamIncorrect=0
    
    spamBegin=spamTest.tell()
    hamBegin=hamTest.tell()
    
    for s in spamTest:
        s=s.strip()
        unionList.append(s)
        unionDict[s]="spam"
    for s in hamTest:
        s=s.strip()
        unionList.append(s)
        unionDict[s]="ham"
    for x in range(1000):
        msg=random.choice(unionList)
        spamScore=score(msg,modelTuple[0],spamPrior)
        hamScore=score(msg,modelTuple[1],hamPrior)
        if spamScore>hamScore and unionDict[msg]=="spam":#correctly identified as spam
            spamCorrect+=1.0
        elif spamScore>hamScore and unionDict[msg]=="ham":#misidentified as ham
            spamIncorrect+=1.0
        elif hamScore>spamScore and unionDict[msg]=="ham":#correctly identified as ham
            hamCorrect+=1.0
        elif hamScore>spamScore and unionDict[msg]=="spam":#incorrectly identified as spam
            hamIncorrect+=1.0
    #print spamCount
    #print hamCount

    spamTest.seek(spamBegin)
    hamTest.seek(hamBegin)
            
    print "Proportion of ham messages identified as ham is " + str(hamCorrect/(hamCorrect+hamIncorrect))
    print "Proportion of ham messages misidentified as spam is " + str(hamIncorrect/(hamCorrect+hamIncorrect))
    print "Proportion of spam messages identified as spam is " + str(spamCorrect/(spamCorrect+spamIncorrect))
    print "Proportion of spam messages misidentified as ham is " + str(spamIncorrect/(spamCorrect+spamIncorrect))
    
    print "Correctly identified spam " +str(spamCorrect)
    print "Incorrectly identified spam " +str(spamIncorrect)
    print "Correctly identified ham " +str(hamCorrect)
    print "Incorrectly identified ham "+str(hamIncorrect)
    
    

    
evaluate()

    
    
