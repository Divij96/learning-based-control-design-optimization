# import numpy as np
# import numpy as np
# import matplotlib.pyplot as plt
# from mpl_toolkits.mplot3d import Axes3D

# class QuadcopterTrajectory:
#     def __init__(self, init_values):
#         # Randomize the coefficients a, b, c (same for x, y, z)
#         self.a, self.b, self.c = [init_values[0], init_values[1], init_values[2]]
#         # For a closed loop, d = 0 and e = 2a + b (for x, y, z)
#         self.d = 0
#         self.e = 2*self.a + self.b
#         # Similarly, for y and z
#         self.f, self.g, self.h = [init_values[5], init_values[4], init_values[5]]
#         self.i = 0
#         self.j = 2*self.f + self.g
#         # And for z
#         self.k, self.l, self.m = [init_values[6], init_values[7], init_values[8]]
#         self.n = 0
#         self.o = 2*self.k + self.l

#     def get_trajectory_point(self, t):
#         x = self.a*t**5 + self.b*t**2 + self.c*t + self.d
#         y = self.e*t**5 + self.f*t**2 + self.g*t + self.h
#         z = self.i*t**5 + self.j*t**2 + self.k*t + self.l
#         return np.array([x, y, z])

#     def get_trajectory_velocity(self, t):
#         v_x = 5*self.a*t**2 + 2*self.b*t + self.c
#         v_y = 5*self.e*t**2 + 2*self.f*t + self.g
#         v_z = 5*self.i*t**2 + 2*self.j*t + self.k
#         return np.array([v_x, v_y, v_z])


# traj_init_values = np.array([-1, 1, 1,
#                             0, 0, 0,
#                             -0.1, 0.1, 0])

# # Create a robot trajectory instance
# robot_trajectory = QuadcopterTrajectory(traj_init_values)

# # Time vector from 0 to 1 with 100 steps
# t = np.linspace(0, 10.24, 1024)

# # Get trajectory points
# trajectory_points = np.array([robot_trajectory.get_trajectory_point(ti) for ti in t])
# velocity_points = np.array([robot_trajectory.get_trajectory_velocity(ti) for ti in t])
# print(max(velocity_points[:, 0]), max(velocity_points[:, 1]), max(velocity_points[:, 2]))
# # Plotting
# fig = plt.figure(figsize=(10, 8))
# ax = fig.add_subplot(111, projection='3d')
# ax.plot(trajectory_points[:, 0], trajectory_points[:, 1], trajectory_points[:, 2], label='Trajectory')
# ax.set_xlabel('X')
# ax.set_ylabel('Y')
# ax.set_zlabel('Z')
# ax.legend()
# # ax.set_xlim(-5, 5)  # Set x-axis limits
# # ax.set_ylim(-5, 5)  # Set y-axis limits
# # ax.set_zlim(-5, 5)  # Set z-axis limits
# plt.title('Robot Trajectory')
# plt.show()


# class QuadcopterCircularTrajectory:
#     def __init__(self, center=np.array([0, 0, 0]), radius=1, height=0):
#         # Circle parameters
#         self.h, self.k, self.z_const = center  # (h, k) is the center of the circle in xy-plane, z_const is the constant z-height
#         self.radius = radius
#         self.omega = 2 * np.pi  # Angular velocity for one full circle in 1 time unit
#         self.height = height
#     def get_trajectory_point(self, t):
#         # Compute x and y using parametric equations for a circle
#         x = self.h + self.radius * np.cos(self.omega * t)
#         y = self.k + self.radius * np.sin(self.omega * t)
#         z = self.z_const + self.height  # Assuming constant z for circle in xy-plane
#         return np.array([x, y, z])

#     def get_trajectory_velocity(self, t):
#         # Compute derivatives of x and y w.r.t. t
#         v_x = -self.radius * self.omega * np.sin(self.omega * t)
#         v_y = self.radius * self.omega * np.cos(self.omega * t)
#         v_z = 0  # No change in z direction as the height is constant
#         return np.array([v_x, v_y, v_z])


import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import os

# Assuming the Trajectory class definition is here or imported

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import os

class Trajectory:
    def __init__(self, df):
        self.df = df

    def reverse(self):
        start_time = self.df["t"].iloc[0]
        end_time = self.df["t"].iloc[-1]
        self.df = self.df.iloc[::-1].reset_index(drop=True)
        self.df["t"] = start_time + end_time - self.df["t"]
        self.df["v_x"] *= -1
        self.df["v_y"] *= -1
        self.df["v_z"] *= -1
        return self

    def mirror_x(self):
        self.df["p_x"] *= -1
        self.df["v_x"] *= -1
        self.df["a_lin_x"] *= -1
        return self

    def mirror_y(self):
        self.df["p_y"] *= -1
        self.df["v_y"] *= -1
        self.df["a_lin_y"] *= -1
        return self

    def translate(self, x, y, z):
        self.df["p_x"] += x
        self.df["p_y"] += y
        self.df["p_z"] += z
        return self

    def close_trajectory(self):
        last_line = self.df.tail(1).copy()
        last_line['t'] = self.df.iloc[-1]['t'] + (self.df.iloc[-1]['t'] - self.df.iloc[-2]['t'])
        last_line['p_x'] = round(self.df.iloc[-1]['p_x'], 2)
        last_line['p_y'] = round(self.df.iloc[-1]['p_y'], 2)
        last_line['p_z'] = round(self.df.iloc[-1]['p_z'], 2)
        last_line['v_x'] = 0.
        last_line['v_y'] = 0.
        last_line['v_z'] = 0.
        last_line['a_lin_x'] = 0.
        last_line['a_lin_y'] = 0.
        last_line['a_lin_z'] = 0.
        last_line['total_vel'] = 0.
        last_line['total_acc'] = 0.

        self.df = pd.concat([self.df, last_line]).reset_index(drop=True)

    def compute_total(self):
        self.df['total_vel'] = (self.df['v_x'] ** 2 + self.df['v_y'] ** 2 + self.df['v_z'] ** 2) ** .5
        self.df['total_acc'] = (self.df['a_lin_x'] ** 2 + self.df['a_lin_y'] ** 2 + self.df['a_lin_z'] ** 2) ** .5

    def add_gradients(self):
         # Compute the velocity vector
        self.df["v_x"] = np.gradient(self.df["p_x"], self.df["t"])
        self.df["v_y"] = np.gradient(self.df["p_y"], self.df["t"])
        self.df["v_z"] = np.gradient(self.df["p_z"], self.df["t"])

        # Calculate the acceleration as the derivatives of the velocities
        self.df["a_lin_x"] = np.gradient(self.df["v_x"], self.df["t"])
        self.df["a_lin_y"] = np.gradient(self.df["v_y"], self.df["t"])
        self.df["a_lin_z"] = np.gradient(self.df["v_z"], self.df["t"])

    def add_distance(self):
        self.df["distance"] = .0
        for i in range(1, len(self.df.index)):
            prev = self.df.iloc[i - 1]
            cur = self.df.iloc[i]
            dif = cur - prev
            self.df.loc[self.df.index[i], "distance"] = (
                prev["distance"] +
                np.sqrt(
                    dif["p_x"] ** 2 +
                    dif["p_y"] ** 2 +
                    dif["p_z"] ** 2
                )
            )

    def add_heading(self, look_ahead=0.):
        self.add_distance()
        for i in range(len(self.df.index) - 1):
            d = self.df.iloc[i]["distance"]
            for j in range(i, len(self.df.index)):
                if self.df.iloc[j]["distance"] - d > look_ahead:
                    break
            dx = self.df.iloc[j]["p_x"] - self.df.iloc[i]["p_x"]
            dy = self.df.iloc[j]["p_y"] - self.df.iloc[i]["p_y"]
            self.df.loc[self.df.index[i], "heading"] = np.arctan2(dy, dx)
        self.df.loc[self.df.index[-1], "heading"] = self.df.iloc[-2]["heading"]
        self.df['heading_rate'] = np.gradient(self.df["heading"], self.df["t"])

    def plot(self, title="Trajectory"):
        def subplot(i, j, to_plot, type):
            for series in to_plot:
                axs[i][j].plot(self.df['t'].values, self.df[series].values)

            axs[i][j].set_title(type + " plot")
            axs[i][j].grid()
            axs[i][j].set_xlabel('time')
            axs[i][j].set_ylabel(type)
            axs[i][j].legend(to_plot)

        _, axs = plt.subplots(2, 3, figsize=(17, 10))

        axs[0][0].set_title(title)
        axs[0][0].set_aspect('equal')
        axs[0][0].plot(self.df['p_x'].values, self.df['p_y'].values)
        axs[0][0].grid()
        axs[0][0].set_xlabel('x')
        axs[0][0].set_ylabel('y')

        subplot(i=0, j=1, to_plot=['p_x', 'p_y', 'p_z'], type="Position")
        subplot(i=1, j=0, to_plot=['v_x', 'v_y', 'v_z', 'total_vel'], type="Velocity")
        subplot(i=1, j=1, to_plot=['a_lin_x', 'a_lin_y', 'a_lin_z'], type="Acceleration")

        axs[1][2].set_title("Heading Rate")
        axs[1][2].plot(self.df['t'].values, self.df['heading_rate'].values)
        axs[1][2].grid()
        axs[1][2].set_xlabel('t')
        axs[1][2].set_ylabel('heading rate (rad/s)')

        axs[0][2].set_title("Heading")
        axs[0][2].plot(self.df['t'].values, self.df['heading'].values)
        axs[0][2].grid()
        axs[0][2].set_xlabel('t')
        axs[0][2].set_ylabel('heading (rad)')

        plt.show()

    def save(self, path):
        if not path.endswith(".csv"):
            path += ".csv"
        os.makedirs("csv", exist_ok=True)
        path = os.path.join('csv', path)
        self.df.to_csv(path, index=False)

    def copy(self):
        return Trajectory(self.df.copy())

    def last(self):
        return self.df.iloc[-1]

    def __len__(self):
        return self.df.shape[0]

    def __str__(self):
        return self.df

    def __add__(self, other):
        df = other.df.copy()
        df.t += self.last().t
        return Trajectory(df=pd.concat([self.df, df]).reset_index(drop=True))



def main():
    # Create a sample dataframe for a trajectory
    data = {
        't': np.linspace(0, 10, 100),
        'p_x': np.sin(np.linspace(0, 10, 100)),
        'p_y': np.cos(np.linspace(0, 10, 100)),
        'p_z': np.linspace(0, 5, 100),
        'v_x': np.cos(np.linspace(0, 10, 100)),
        'v_y': -np.sin(np.linspace(0, 10, 100)),
        'v_z': np.full(100, 0.5),
        'a_lin_x': -np.sin(np.linspace(0, 10, 100)),
        'a_lin_y': -np.cos(np.linspace(0, 10, 100)),
        'a_lin_z': np.zeros(100),
    }
    df = pd.DataFrame(data)

    # Initialize the Trajectory object
    trajectory = Trajectory(df)

    # Perform some operations
    trajectory.reverse()
    trajectory.mirror_x()
    trajectory.translate(1, 2, 3)
    trajectory.compute_total()
    trajectory.add_gradients()
    trajectory.add_distance()
    trajectory.add_heading(look_ahead=1.0)
    trajectory.close_trajectory()

    # Plot the trajectory
    trajectory.plot(title="Modified Trajectory")

    # Save the trajectory to a file
    trajectory.save("modified_trajectory.csv")

if __name__ == "__main__":
    main()
