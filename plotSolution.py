#!/usr/bin/python

from mpl_toolkits.mplot3d import Axes3D, art3d
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import sys

lineSegs = [[[0, 0], [1, 0]], [[1, 0], [1, 1]], [[1, 1], [0, 1]], [[0, 1], [0, 0]]]

def plot(data, xaxis, yaxis):
    fig = plt.figure()
    ax = fig.gca()
    xmin, ymin, xmax, ymax = ax.get_position().bounds
    maxd = max(xmax, ymax)
    width = 6 * maxd / xmax
    height = 6 * maxd / ymax
    fig.set_size_inches((width, height))

    # Plotting the square
    for hyperRect in data:
        for lineSeg in lineSegs:
            x = []
            y = []
            for pt in lineSeg:
                x.append(hyperRect[xaxis][pt[0]])
                y.append(hyperRect[yaxis][pt[1]])
            ax.plot(x, y, 'k')
    plt.axis([-1,1,-1,1])
    plt.show()

# Read the data from the file
def readPath(filename):
    lines = [line.rstrip() for line in open(filename) if len(line.rstrip()) > 0]

    if len(lines) == 0:
        print "Empty File"
        sys.exit(1)

    data = [[[float(x) for x in interval[1:-1].split(' ')] for interval in line.strip().split('\t')] for line in lines]
    return data

if __name__ == '__main__':
    if len(sys.argv) > 3:
        filename = sys.argv[1]
	xaxis = int(sys.argv[2])
	yaxis = int(sys.argv[3])
    else:
        filename = 'data.txt'
	xaxis = 0
	yaxis = 1

    data = readPath(filename)
    plot(data, xaxis, yaxis)
