from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[3]

import gymnasium as gym
from gymnasium import spaces
from gymnasium import utils
from gymnasium.spaces import Box
import math as m
import random

import numpy as np
import math as m
import math

from shapely.geometry import Point
from shapely.geometry.polygon import Polygon
from shapely.geometry import LineString

from scipy.io import loadmat, savemat

import sys
sys.path.append(f'{REPO_ROOT}/cpp/bindings/build/python')
import forward_dynamics_6arm_wrapper

class Robot_6dof_Arm_Dynamics(utils.EzPickle, gym.Env):
    metadata = {
        "render_modes": [
            "human",
        ],
        "render_fps": 20,
    }

    def __init__(self, REWARD = np.array([0.7, 0.0, 0.3]), env_id = 0, arm_length = [1.0, 1.0], num_links=6 ,call_back = f"random_design"):
        super(Robot_6dof_Arm_Dynamics, self).__init__()

        utils.EzPickle.__init__(self)
        self.call_back = call_back
        self.action_num = num_links
        self.action_space = Box(low=-1, high=1, shape=(self.action_num,))

        self.observation_num = 6 * num_links + 5
        self.observation_space = Box(low=-1, high=1, shape=(self.observation_num,))
        self.model = forward_dynamics_6arm_wrapper
        self.freq = 1 # 50 Hz
        self.steps = 0
        self.env_id = env_id

        #reward function
        self.TARGET_COEFF = REWARD[0]
        self.SPEED_COEFF = REWARD[1]
        self.ACTION_PENALTY_COEFF = REWARD[2]

        # Define input parameters
        self.num_links = num_links

        # Define the random robot parameters based on the number of num_links

        self.max_length = 2*np.ones(self.num_links, dtype=np.double)
        self.min_length = 0.1*np.ones(self.num_links, dtype=np.double)

        # self.curr_joint_pos = np.ones(self.num_links, dtype=np.double)
        self.prev_joint_pos = np.zeros(self.num_links, dtype=np.double)
        self.init_joint_pos = np.zeros(self.num_links, dtype=np.double)
        self.curr_joint_vel = np.zeros(self.num_links, dtype=np.double)
        self.arm_length = 0.5 * np.ones(self.num_links, dtype=np.double)
        self.joint_torque = np.zeros(self.num_links, dtype=np.double)

        self.arm_length_sum = np.sum(self.max_length)
        self.rho = np.array(1500.0, dtype=np.double)
        self.radius = np.array(0.025, dtype=np.double)

        self.target_threshold = self.convert_range(0.1, 0, 2*self.arm_length_sum, 0, 1)

        # Initialize output arrays
        self.pos_tcp = np.empty(3, dtype=np.double)
        self.vel_tcp = np.array([0.0, 0.0, 0.0], dtype=np.double)
        self.target_pos_tcp = np.array([0.0, 0.0, 0.0], dtype=np.double)
        self.curr_joint_acc = np.zeros(num_links, dtype=np.double)
        self.link_pos_data = np.zeros(18, dtype=np.double)  # Link position data

        self.prev_pos_tcp = np.array([0.0, 0.0, 0.0], dtype=np.double)
        self.joint_axes = np.array([
                                    0, 1, 0, 0, 0, 1,
                                    0, 0, 0, 0, 0, 0,
                                    1, 0, 1, 1, 1, 0,
                                ], dtype=np.double)

        self.curr_joint_pos = np.array([0.0, -m.pi/4, 0.0, m.pi/3, -m.pi/3, 0.0], dtype=np.double)
        self.joint_angles = np.array([0.0, 0.0, 0.0, 0.0, 0.0, 0.0], dtype=np.double)

        # Initial time and time step
        self.dt = 0.001 # 50 Hz

        self.max_joint_pos = m.pi * np.ones(self.num_links, dtype=np.double)
        self.min_joint_pos = -m.pi * np.ones(self.num_links, dtype=np.double)
        self.max_joint_vel = 20.0 * np.ones(self.num_links, dtype=np.double)
        self.min_joint_vel = -20.0 * np.ones(self.num_links, dtype=np.double)

        self.pos_tcp_range_x = np.array([-self.arm_length_sum, self.arm_length_sum], dtype=np.double)
        self.pos_tcp_range_y = np.array([-self.arm_length_sum, self.arm_length_sum], dtype=np.double)
        self.vel_tcp_range_x = np.array([-10.0, 10.0], dtype=np.double)
        self.vel_tcp_range_y = np.array([-10.0, 10.0], dtype=np.double)

        # # Instantiate the FirstOrderDelay class
        self.max_torque = np.array([50.0, 50.0, 50.0, 50.0, 50.0, 50.0], dtype=np.double)
        self.min_torque = -self.max_torque
        self.filter = FirstOrderDelay(alpha=0.5)

        # Instantiate the FirstOrderDelay class
        # self.max_torque = m.pi * np.ones(self.num_links, dtype=np.double)
        # self.min_torque = -m.pi * np.ones(self.num_links, dtype=np.double)
        # self.filter = FirstOrderDelay(alpha=0.02)

        #define collision patterns
        self.collision_pattern_1 = self.collision_geometry_maze(2.5, start_x=-1.0, start_y=-0.75)

        self.continue_training = True
        np.set_printoptions(precision=2)

    def step(self, action):

        self.steps += 1
        done = False
        early_Stop = False
        collision = False

        joint_torque_action = self.convert_range(action, -1, 1, self.min_torque, self.max_torque)

        self.joint_torque  = np.zeros(self.num_links, dtype=np.double)
        # Call the wrapped function
        # self.joint_torque = self.filter.step(joint_torque_action)

        self.model.forward_dynamics_robot(self.rho, self.radius, self.arm_length,
                                        self.joint_axes,
                                        self.joint_angles, self.curr_joint_pos,
                                        self.curr_joint_vel, self.joint_torque,
                                        self.curr_joint_acc, self.link_pos_data)

        # Integrating the acceleration to get velocity
        self.curr_joint_vel = self.curr_joint_vel + self.curr_joint_acc * self.dt
        # self.curr_joint_vel = np.array(self.curr_joint_vel, dtype=np.double)
        # self.curr_joint_vel = np.clip(self.curr_joint_vel, self.min_joint_vel, self.max_joint_vel)

        # Integrating the velocity to get position
        self.curr_joint_pos = self.curr_joint_pos + self.curr_joint_vel * self.dt
        # self.curr_joint_pos = np.array(self.curr_joint_pos, dtype=np.double)
        # self.curr_joint_pos = np.clip(self.curr_joint_pos, self.min_joint_pos, self.max_joint_pos)
        #print only 2 significant digits of data
        self.prev_joint_pos = self.curr_joint_pos

        start_point = (0, 0)
        end_points = []
        accumulated_angle = 0  # Initialize accumulated angle

        for i, length in enumerate(self.arm_length):
            accumulated_angle += self.curr_joint_pos[i]  # Accumulate joint angles
            end_point = (
                start_point[0] + length * math.cos(accumulated_angle),
                start_point[1] + length * math.sin(accumulated_angle)
            )
            start_point = end_point
        self.pos_tcp = np.array([end_point[0], end_point[1], 0.0], dtype=np.double)

        self.vel_tcp = (self.pos_tcp - self.prev_pos_tcp) / self.dt
        self.prev_pos_tcp = self.pos_tcp

        #check for collisions
        start_point = (0, 0)
        end_points = []
        accumulated_angle = 0  # Initialize accumulated angle
        for i, length in enumerate(self.arm_length):
            accumulated_angle += self.curr_joint_pos[i]  # Accumulate joint angles
            end_point = (
                start_point[0] + length * math.cos(accumulated_angle),
                start_point[1] + length * math.sin(accumulated_angle)
            )

            end_points.append(end_point)
            # Current segment of the robot arm
            current_segment = LineString([start_point, end_point])

            # Check for intersection with each line segment in the zigzag patterns
            for pattern in [self.collision_pattern_1]:
                for j in range(len(pattern) - 1):
                    zigzag_segment = LineString([pattern[j], pattern[j+1]])
                    if current_segment.intersects(zigzag_segment):
                        # print(f"Intersection found between arm segment {i} and zigzag segment {j}")
                        collision = True

            start_point = end_point

        # joint position should be converted to range -pi to pi for e.g. pi to 3pi or 3pi to 5pi tpshould be converted to -pi to pi

        # self.curr_joint_pos = np.fmod(self.curr_joint_pos + np.pi, 2 * np.pi) - np.pi

        obs_joint_torque = self.convert_range(self.joint_torque, self.min_torque, self.max_torque, -1, 1)
        obs_joint_pos   = self.convert_range(self.curr_joint_pos, self.min_joint_pos, self.max_joint_pos, -1, 1)
        obs_joint_vel   = self.convert_range(self.curr_joint_vel, self.min_joint_vel, self.max_joint_vel, -1, 1)
        obs_arm_length  = self.convert_range(self.arm_length, self.min_length, self.max_length, -1, 1)
        obs_joint_acc   = self.convert_range(self.curr_joint_acc, self.min_joint_vel, self.max_joint_vel, -1, 1)
        obs_tcp_pos     = np.array([self.convert_range(self.pos_tcp[0], self.pos_tcp_range_x[0], self.pos_tcp_range_x[1], -1, 1)
                                    ,self.convert_range(self.pos_tcp[1], self.pos_tcp_range_y[0], self.pos_tcp_range_y[1], -1, 1)
                                    ,0])
        obs_target_pos  = np.array([self.convert_range(self.target_pos_tcp[0], self.pos_tcp_range_x[0], self.pos_tcp_range_x[1], -1, 1)
                                    ,self.convert_range(self.target_pos_tcp[1], self.pos_tcp_range_y[0], self.pos_tcp_range_y[1], -1, 1)
                                    ,0])
        obs_vel_tcp     = np.array([self.convert_range(self.vel_tcp[0], self.vel_tcp_range_x[0], self.vel_tcp_range_x[1], -1, 1)
                                    ,self.convert_range(self.vel_tcp[1], self.vel_tcp_range_y[0], self.vel_tcp_range_y[1], -1, 1)
                                    ,0])
        obs_link_pos_task_space = np.concatenate(end_points)
        obs_link_pos_task_space = np.array(self.convert_range(obs_link_pos_task_space, self.pos_tcp_range_x[0], self.pos_tcp_range_x[1], -1, 1))

        obs_pos_vec = obs_tcp_pos - obs_target_pos
        target_dist = np.linalg.norm(self.target_pos_tcp - self.pos_tcp)
        target_dist = self.convert_range(target_dist, 0, 2*self.arm_length_sum, 0, 1)
        obs_target_dist = np.array([target_dist], dtype=np.double)

        reward_target = 1 / (target_dist + 1e-6)
        reward_target = np.clip(reward_target, 0, 1/self.target_threshold)
        reward_target = self.convert_range(reward_target, 0, 1/self.target_threshold, 0, 1)
        # reward_target = 1 - obs_target_dist

        if obs_target_dist < self.target_threshold:
            reward_target = 1.0

        reward = self.TARGET_COEFF * reward_target

        # if collision:
        #     reward = -1.0
        #     done = True

        polygon_vertices = self.collision_pattern_1

        if not self.is_point_inside_polygon(end_point, polygon_vertices[1:-1]):
            reward = 0.0

        observation = np.concatenate([obs_pos_vec[:2], obs_vel_tcp[:2],
                                      obs_target_dist , obs_joint_pos, obs_joint_vel,
                                      obs_link_pos_task_space, obs_joint_torque,
                                      obs_arm_length])

        info = {'joint_pos': self.curr_joint_pos, 'arm_length': self.arm_length,
                'joint_torque': self.joint_torque, 'pos_tcp': self.pos_tcp, 'vel_tcp': self.vel_tcp,
                'target_pos': self.target_pos_tcp, 'collision_pattern_1': self.collision_pattern_1,
                'link_pos_data': self.link_pos_data}

        observation = observation.astype(np.float32)
        reward = float(reward)

        if (np.any(np.isnan(observation)) or np.any(np.isinf(observation))):
            print("nan or inf detected in step", self.arm_length)
            print(observation)
            observation = np.ones(self.observation_num)
            reward = -1.0
            reward = float(reward)
            done = True
            early_Stop = True
        return observation, reward, done, early_Stop, info

    def reset(self, seed=None):

        self.steps = 0


        # observation = np.ones(self.observation_num)
        observation = np.ones(self.observation_num)

        if (np.any(np.isnan(observation)) or np.any(np.isinf(observation))):
            print("nan or inf detected in reset", self.arm_length)
            print(observation)
            observation = np.ones(self.observation_num)
            print(observation)


        info = {'joint_pos': self.curr_joint_pos, 'arm_length': self.arm_length,
                'joint_torque': self.joint_torque, 'pos_tcp': self.pos_tcp, 'vel_tcp': self.vel_tcp,
                'target_pos': self.target_pos_tcp}

        return observation, info

    def set_arm_length(self, arm_length):
        self.arm_length = [1.0,
                            arm_length[0],
                            arm_length[1],
                            arm_length[2]]

    def get_arm_length(self):
        return self.arm_length

    def set_env_id(self, env_id):
        self.env_id = env_id

    def get_env_id(self):
        return self.env_id

    def get_target_pos_tcp(self):
        return self.target_pos_tcp

    def render(self, mode='human'):
        pass

    def close(self):
        pass

    def deg_to_rad(self, deg):
        return deg * m.pi / 180.0

    def generate_target_position(self, radius, theta):
        x = radius * np.cos(theta)
        y = radius * np.sin(theta)
        return np.array([x, y, 0.0])

    def convert_range(self,x, min_x, max_x, min_y, max_y):
        return (x - min_x) / (max_x - min_x) * (max_y - min_y) + min_y

    def set_target_pos_tcp(self, theta, radius):
        self.target_pos_tcp = self.generate_target_position(radius, theta)

    def get_target_pos_tcp(self):
        return self.target_pos_tcp

    def set_init_joint_pos(self, joint_pos):
        self.init_joint_pos = joint_pos

    def get_curr_joint_pos(self):
        return self.curr_joint_pos

    def collision_geometry(self, length, start_x=0, start_y=0):
        # Define the starting point of the zigzag pattern
        start_x = start_x
        start_y = start_y

        # Define the points for the zigzag pattern
        points = [
            (start_x, start_y),
            (start_x + length, start_y + length),  # First line segment
            (start_x + 2 * length, start_y),       # Second line segment
            (start_x + 3 * length, start_y + length),  # Third line segment
            (start_x + 4 * length, start_y)        # Fourth line segment
        ]

        return points

    def collision_geometry_maze(self, length, start_x=0, start_y=0):
        start_x = start_x
        start_y = start_y

        points = [
            (2.6, 0),
            (2.6, 2),
            (start_x + 2*length, 2),
            (start_x + 2*length, 1),
            (start_x + 2.5*length, 1),
            (start_x + 2.5*length, 4),
            (-1.0, 4),
            (-1.0, 2),
            (-1.0, 0),

        ]

        return points

    def is_point_inside_polygon(self, point, polygon_vertices):
        """
        Check if a point is inside a polygon

        :param point: A tuple (x, y) representing the point
        :param polygon_vertices: A list of tuples [(x1, y1), (x2, y2), ...] representing the vertices of the polygon
        :return: True if the point is inside the polygon, False otherwise
        """
        shapely_point = Point(point)
        shapely_polygon = Polygon(polygon_vertices)
        return shapely_polygon.contains(shapely_point)

    def set_continue_training(self, continue_training):
        self.continue_training = continue_training

    def get_continue_training(self):
        return self.continue_training

class FirstOrderDelay:
    def __init__(self, alpha, initial_output=0):
        self.alpha = alpha
        self.previous_output = initial_output

    def step(self, current_input):
        current_output = (1 - self.alpha) * self.previous_output + self.alpha * current_input
        self.previous_output = current_output
        return current_output

class RobotTrajectory:
    def __init__(self):
        # Randomize the coefficients a, b, c (same for x, y, z)
        self.a, self.b, self.c = np.random.uniform(-1, 1, 3)
        # For a closed loop, d = 0 and e = 2a + b (for x, y, z)
        self.d = 0
        self.e = 2*self.a + self.b
        # Similarly, for y and z
        self.f, self.g, self.h = np.random.uniform(-1, 1, 3)
        self.i = 0
        self.j = 2*self.f + self.g
        # And for z
        self.k, self.l, self.m = np.random.uniform(-1, 1, 3)
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
