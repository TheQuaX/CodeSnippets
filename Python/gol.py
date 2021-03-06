import random
import time
import os

def initGrid(cols,rows,array):
    for i in range(rows):
        arrayRow=[]
        for j in range(cols):
            if (i==0 or j==0 or (i== rows-1) or (j== cols-1)):
                arrayRow+=[-1]
            else:
                ran=random.randint(0,3)
                if ran ==0:
                    arrayRow+=[1]
                else:
                    arrayRow+=[0]
        array+=[arrayRow]


def printGen(cols,rows,array,genNo):
    os.system("cls")
    print("Game of Life -- Generation " + str(genNo +1))

    for i in range(rows):
        for j in range(cols):
            if array[i][j] == -1:
                print("#", end=" ")
            elif array[i][j] == 1:
                print(".", end=" ")
            else:
                print(" ", end=" ")
        print("\n")
        
def processNextGen(cols,rows,cur,nxt):
    for i in range(1,rows-1):
        for j in range(1,cols-1):
            nxt[i][j]= processNeighbours(i,j,cur)

def processNeighbours(x,y,array):
    nCount=0
    for j in range(y-1,y+2):
        if not(i==x and j==y):
            if array[i][j] != -1:
                nCount+=array[i][j]
    if array[x][y] ==1 and nCount<2:
        return 0
    if array[x][y] ==1 and nCount>3:
        return 0
    if array[x][y]==0 and nCount==3:
        return 1
    else:
        return array[x][y]

ROWS=15
COLS=15
GENERATIONS=100
DELAY=0.2

thisGen =[]
nextGen=[]

initGrid(COLS, ROWS, thisGen)
initGrid(COLS, ROWS, nextGen)

for gens in range(GENERATIONS):
    printGen(COLS, ROWS, thisGen, gens)
    processNextGen(COLS, ROWS, thisGen, nextGen)
    time.sleep(DELAY)
    thisGen, nextGen = nextGen, thisGen
                                       
