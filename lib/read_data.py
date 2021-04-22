import sys
sys.path.append("../library/")
import pandas as pd
import glob
import numpy as np
from dataProcess import *


dataDirectory = "../data/"
observables = set()

#* Observables with repeater
observables.add("clusterSizeDist")
observables.add("clusterSizeDist2")

absolutePathList = {}
for observable in observables:
    absolutePathList[observable] = dataDirectory + observable + "/"


# * CSV Reader
def readCSV(fileName):
    data = pd.read_csv(fileName, sep=',', header=None, dtype=np.double)
    data = data.values.transpose()
    if (len(data) == 0):
        return None
    elif (len(data) == 1):
        return data[0]
    else:
        return tuple([row for row in data])


# * File Name Convections
def __NG__(size, prob):
    return "N{:.1e},P{:.5f}*-0.txt".format(size, prob)

# * Read Observables
def read(type, size, prob, repeater=None):
    file = glob.glob(absolutePathList[type] + __NG__(size, prob))
    # * Check found files
    if (len(file) != 1):
        print("There is problem at reading " + file[0])
        return
    else:
        print("Reading ", file[0])
        return readCSV(file[0])

if __name__ == "__main__":
    print("This is a module read_data.py")
