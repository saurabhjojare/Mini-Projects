#Install necessary libraries

#!pip install nltk
#!pip install -U scikit-learn
#!pip install numpy

#Import necessary libraries

import sys
import io
import numpy as np
import nltk # NLTK is a leading platform for building Python programs to work with human language data.
import string # provides the ability to do complex variable substitutions and value formatting
import random
import warnings
warnings.filterwarnings('ignore')

#TfidfVectorizer

from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity

#Downloading and installing NLTK (Punkt, WordNet, Popular)

from nltk.stem import WordNetLemmatizer
nltk.download('punkt') # Using the Punkt tokenizer
nltk.download('wordnet') # Using the WordNet dictionary
nltk.download('popular', quiet=True) # for downloading packages

#Reading in the corpus

f = open('chatbot.txt','r',errors = 'ignore')
raw_doc = f.read()
raw_doc = raw_doc.lower() # Converts text lowercase

#Tokenisation

sent_tokens = nltk.sent_tokenize(raw_doc) # Converts doc to list of sentences
word_tokens = nltk.word_tokenize(raw_doc) # Converts doc to list of words

#Preprocessing

lemmer = nltk.stem.WordNetLemmatizer()
#WordNet is a semantically-oriented dictionary of English included in NLTK.
def LemTokens(tokens):
    return [lemmer.lemmatize(token) for token in tokens]
remove_punct_dict = dict((ord(punct), None) for punct in string.punctuation)

def LemNormalize(text):
    return LemTokens(nltk.word_tokenize(text.lower().translate(remove_punct_dict)))

#Keyword matching

GREETING_INPUTS = ("hello", "hi", "greetings", "sup", "what's up", "hey")
GREETING_RESPONSES = ["Hi", "Hey", "*nods*", "Hi there", "Hello"]

GREETING_INPUTS1 = ("good morning", "morning")
GREETING_RESPONSES1 = ["Good morning", "Morning"]

GREETING_INPUTS2 = ("how are you", "how you doing")
GREETING_RESPONSES2 = ["I'm fine", "Good, you?"]

def greeting(sentence):
    sentence_lower = sentence.lower()
    
    for greeting_input, greeting_responses in zip(
        [GREETING_INPUTS, GREETING_INPUTS1, GREETING_INPUTS2],
        [GREETING_RESPONSES, GREETING_RESPONSES1, GREETING_RESPONSES2]
    ):
        for greeting_word in greeting_input:
            if greeting_word in sentence_lower:
                return random.choice(greeting_responses)

#Generating Response

def response(user_response):
    robo_response=''
    sent_tokens.append(user_response)
    TfidfVec = TfidfVectorizer(tokenizer=LemNormalize, stop_words='english')
    tfidf = TfidfVec.fit_transform(sent_tokens)
    vals = cosine_similarity(tfidf[-1], tfidf)
    idx=vals.argsort()[0][-2]
    flat = vals.flatten()
    flat.sort()
    req_tfidf = flat[-2]
    if(req_tfidf==0):
        robo_response=robo_response+"I am sorry! I don't understand you"
        return robo_response
    else:
        robo_response = robo_response+sent_tokens[idx]    
        return robo_response



flag=True
print("Bot: Hello! How can I assist you today? \nTo exit type bye")
while(flag==True):
    user_response = input("You: ")
    user_response=user_response.lower()
    if(user_response!='bye'):
        if(user_response=='thanks' or user_response=='thank you' ):
            flag=False
            print("Bot: You're welcome!")
        else:
            if(greeting(user_response)!=None):
                print("Bot: "+greeting(user_response))
            else:
                print("Bot: ",end="")
                print(response(user_response))
                sent_tokens.remove(user_response)
    else:
        flag=False
        print("Bot: Bye!")
