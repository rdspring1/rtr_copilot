#!/usr/bin/python

from mpl_toolkits.mplot3d import Axes3D, art3d
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import sys
import math

lineSegs = [[[0, 0], [1, 0]], [[1, 0], [1, 1]], [[1, 1], [0, 1]], [[0, 1], [0, 0]]]

def sign(value):
    if value > 0:
        return 1
    elif value < 0:
        return -1
    else:
        return 0

def round_scale(value, axis_range):
    most_sig = int(math.floor(math.log10(abs(value))))
    return round(value, -most_sig)

def plot(data, xaxis, yaxis):
    fig = plt.figure()
    ax = fig.gca()
    axis = [sys.float_info.max, sys.float_info.min, sys.float_info.max, sys.float_info.min]

    # Plotting the HyperRectangle points
    for hyperRect in data:
        for lineSeg in lineSegs:
            x = []
            y = []
            for pt in lineSeg:
		xval = hyperRect[xaxis][pt[0]]
		yval = hyperRect[yaxis][pt[1]]
                axis[0] = min(axis[0], xval)
		axis[1] = max(axis[1], xval)
		axis[2] = min(axis[2], yval)
		axis[3] = max(axis[3], yval)
                x.append(xval)
                y.append(yval)
            ax.plot(x, y, 'k')

    # expand axis to fit the entire plot
    border = 0.25
    rangeX = abs(axis[1] - axis[0])
    rangeY = abs(axis[3] - axis[2])
    axis[0] = axis[0] - rangeX * border
    axis[1] = axis[1] + rangeX * border
    axis[2] = axis[2] - rangeY * border
    axis[3] = axis[3] + rangeY * border

    # round axis to nice values
    #axis[0] = round_scale(axis[0], rangeX)
    #axis[1] = round_scale(axis[1], rangeX)
    #axis[2] = round_scale(axis[2], rangeY)
    #axis[3] = round_scale(axis[3], rangeY)

    plt.axis(axis)
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
    if len(sys.argv) > 2:
	xaxis = int(sys.argv[1])
	yaxis = int(sys.argv[2])
    else:
	xaxis = 0
	yaxis = 1

    filename = 'data.txt'
    data = readPath(filename)
    plot(data, xaxis, yaxis)
