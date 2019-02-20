import sys
import math
import random

generateLengths = [500, 1000, 2000, 4000, 5000, 7000, 9000, 11000, 15000]

def getDNA(x):
    if x == 1:
        return 'A'
    elif x == 2: 
        return 'T'
    elif x == 3:
        return 'G'
    elif x == 4:
        return 'C'

with open("./imp2input.txt", "w") as file:
    for length in generateLengths:
        for x in range(10):
            for i in range(length):
                randChar = random.randint(1, 4)
                file.write(getDNA(randChar))
            file.write(",")
            for i in range(length):
                randChar = random.randint(1, 4)
                file.write(getDNA(randChar))
            file.write("\n")