import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

class RobotTrajectory:
    def __init__(self):
        # Randomize the coefficients a, b, c (same for x, y, z)
        self.a, self.b, self.c = np.random.uniform(-10, 10, 3)
        # For a closed loop, d = 0 and e = 2a + b (for x, y, z)
        self.d = 0
        self.e = 2*self.a + self.b
        # Similarly, for y and z
        self.f, self.g, self.h = np.random.uniform(-10, 10, 3)
        self.i = 0
        self.j = 2*self.f + self.g
        # And for z
        self.k, self.l, self.m = np.random.uniform(-10, 10, 3)
        self.n = 0
        self.o = 2*self.k + self.l

    def get_trajectory_point(self, t):
        x = self.a*t**3 + self.b*t**2 + self.c*t + self.d
        y = self.e*t**3 + self.f*t**2 + self.g*t + self.h
        z = self.i*t**3 + self.j*t**2 + self.k*t + self.l
        return np.array([x, y, z])

    def get_trajectory_velocity(self, t):
        v_x = 3*self.a*t**2 + 2*self.b*t + self.c
        v_y = 3*self.e*t**2 + 2*self.f*t + self.g
        v_z = 3*self.i*t**2 + 2*self.j*t + self.k
        return np.array([v_x, v_y, v_z])

# Create a robot trajectory instance
robot_trajectory = RobotTrajectory()

# Time vector from 0 to 1 with 100 steps
t = np.linspace(0, 1, 100)

# Get trajectory points
trajectory_points = np.array([robot_trajectory.get_trajectory_point(ti) for ti in t])

# Plotting
fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')
ax.plot(trajectory_points[:, 0], trajectory_points[:, 1], trajectory_points[:, 2], label='Trajectory')
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.legend()
plt.title('Robot Trajectory')
plt.show()