from numpy import sin, cos
import numpy as np
import matplotlib.pyplot as plt
import scipy.integrate as integrate
import matplotlib.animation as animation
import math
import fileinput

xaxis = 5
L = 0.5
l = 0.5

#------------------------------------------------------------
data_points = [[float(x) for x in line.split(' ')] for line in fileinput.input()]

# set up figure and animation
fig = plt.figure()
ax = fig.add_subplot(111, aspect='equal', autoscale_on=False,
                     xlim=(-xaxis, xaxis), ylim=(-4, 4))
ax.grid()

line, = ax.plot([], [], 'o-', lw=2)

def init():
    """initialize animation"""
    line.set_data([], [])
    return line

def animate(i):
    """perform animation step"""
    line.set_data(get_data_pt(i))
    return line

def get_data_pt(i):
    x = np.cumsum([data_points[i][0], L, l * sin(data_points[i][1])])
    y = np.cumsum([0, 0, l * cos(data_points[i][1])])
    return (x, y)

from time import time
t0 = time()
animate(0)
t1 = time()
interval = len(data_points) * (t1 - t0)

# choose the interval based on dt and the time to animate one step
ani = animation.FuncAnimation(fig, animate, frames=len(data_points),
                              interval=interval, blit=False, init_func=init)

# save the animation as an mp4.  This requires ffmpeg or mencoder to be
# installed.  The extra_args ensure that the x264 codec is used, so that
# the video can be embedded in html5.  You may need to adjust this for
# your system: for more information, see
# http://matplotlib.sourceforge.net/api/animation_api.html
#ani.save('double_pendulum.mp4', fps=30, extra_args=['-vcodec', 'libx264'])

plt.show()
