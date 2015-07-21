from numpy import sin, cos
import numpy as np
import matplotlib.pyplot as plt
import scipy.integrate as integrate
import matplotlib.animation as animation

xaxis = 5

class DoublePendulum:
    """Double Pendulum Class

    init_state is [x, theta, velocity, omega] in degrees,
    where x - position of the cart, theta is the angular position of the
    pendulum arm, velocity - velocity of the cart, and omega is the
    angular velocity of the pendulum
    """
    def __init__(self,
                 init_state = [0.0, 0.0, 0.0, 0.0],
                 l=0.3,  # length of pendulum in m
                 m=0.2,  # mass of pendulum in kg
		 L=0.5,  # length of the cart in m
                 M=0.8,  # mass of the cart in kg
		 friction = 7.68, # friction coefficient in N / m / sec
                 G=9.81, # acceleration due to gravity, in m/s^2
                 origin=(0, 0)): 
        self.init_state = np.asarray(init_state, dtype='float')
        self.params = (l, m, L, M, friction, G)
        self.origin = origin
        self.time_elapsed = 0
        self.state = self.init_state
	self.KP = -20.0
	self.KD = -5.0

    def control_update(self):
        """compute the control update for the given state"""
        (l, m, L, M, friction, G) = self.params
	u = self.KP * self.state[1] + self.KD * self.state[3]
	B = [0, 0, 1.0/M, 1/(M*l)]
	return np.dot(B,u)
    
    def position(self):
        """compute the current x,y positions of the pendulum arms"""
        (l, m, L, M, friction, G) = self.params

        x = np.cumsum([self.state[0],
                       L,
                       2*l * sin(self.state[1])])
        y = np.cumsum([self.origin[1],
                       self.origin[1],
                       2*l * cos(self.state[1])])
        return (x, y)

    def dstate_dt(self, state, t):
        """compute the derivative of the given state"""
        (l, m, L, M, friction, G) = self.params

        dt = np.zeros_like(state)
        dt[0] = state[2]
        dt[1] = state[3]

	A3 = [0, (m*G)/M, -friction/M, 0]
	dt[2] = np.dot(A3, state)

	A4 = [0, ((M+m)/(M*l))*G, friction/(M*l), 0]
	dt[3] = np.dot(A4, state)
        return dt + self.control_update()

    def bound_state(self):
	global xaxis
	if self.state[1] > (np.pi / 2.0):
	    self.state[1] = (np.pi / 2.0)
	elif self.state[1] < (-np.pi / 2.0):
	    self.state[1] = (-np.pi / 2.0)
	
	if self.state[0] > xaxis:
	    self.state[0] = xaxis
	elif self.state[0] < -xaxis:
	    self.state[0] = -xaxis

    def step(self, dt):
        """execute one time step of length dt and update state"""
        self.state = integrate.odeint(self.dstate_dt, self.state, [0, dt])[1]
	self.bound_state()
        self.time_elapsed += dt

#------------------------------------------------------------
# set up initial state and global variables
pendulum = DoublePendulum([0.0, np.radians(5.0), 0.0, 0.0])
dt = 1./200 

#------------------------------------------------------------
# set up figure and animation
fig = plt.figure()
ax = fig.add_subplot(111, aspect='equal', autoscale_on=False,
                     xlim=(-1.5 * xaxis, 1.5 * xaxis), ylim=(-2, 2))
ax.grid()

line, = ax.plot([], [], 'o-', lw=2)
time_text = ax.text(0.02, 0.95, '', transform=ax.transAxes)

def init():
    """initialize animation"""
    line.set_data([], [])
    time_text.set_text('')
    return line, time_text

def animate(i):
    """perform animation step"""
    global pendulum, dt
    pendulum.step(dt)
    
    line.set_data(*pendulum.position())
    time_text.set_text('time = %.1f' % pendulum.time_elapsed)
    return line, time_text

# choose the interval based on dt and the time to animate one step
from time import time
t0 = time()
animate(0)
t1 = time()
interval = 1000 * dt - (t1 - t0)

ani = animation.FuncAnimation(fig, animate, frames=300,
                              interval=interval, blit=False, init_func=init)

# save the animation as an mp4.  This requires ffmpeg or mencoder to be
# installed.  The extra_args ensure that the x264 codec is used, so that
# the video can be embedded in html5.  You may need to adjust this for
# your system: for more information, see
# http://matplotlib.sourceforge.net/api/animation_api.html
#ani.save('double_pendulum.mp4', fps=30, extra_args=['-vcodec', 'libx264'])

plt.show()
