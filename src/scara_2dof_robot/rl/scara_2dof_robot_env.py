from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[3]

import gymnasium as gym
from gymnasium import spaces
from gymnasium import utils
from gymnasium.spaces import Box
import math as m
import random
import time

import matplotlib.pyplot as plt
import matplotlib.animation as animation
from mpl_toolkits.mplot3d import Axes3D

import numpy as np
import sys
import math as m
import time
from scipy.io import loadmat, savemat

sys.path.append(f'{REPO_ROOT}/devel/lib')
import scara_robot_2dof_FD_wrapper

class Scara_2Dof_Robot_Env(utils.EzPickle, gym.Env):
    metadata = {
        "render_modes": [
            "human",
        ],
        "render_fps": 20,
    }

    def __init__(self, REWARD = np.array([0.7, 0.0, 0.3]), env_id = 0, arm_length = [1.25, 1.25], call_back = f"constant_design"):
        super(Scara_2Dof_Robot_Env, self).__init__()

        utils.EzPickle.__init__(self)
        self.call_back = call_back
        self.action_space = Box(low=-1, high=1, shape=(2,))

        self.observation_space = Box(low=-1, high=1, shape=(16,))
        self.model = scara_robot_2dof_FD_wrapper
        self.freq = 20 # 50 Hz
        self.steps = 0
        self.env_id = env_id

        #reward function
        self.TARGET_COEFF = REWARD[0]
        self.SPEED_COEFF = REWARD[1]
        self.ACTION_PENALTY_COEFF = REWARD[2]

        # Define input parameters

        self.max_length = np.array([5.0, 5.0], dtype=np.double)
        self.min_length = np.array([1.0, 1.0], dtype=np.double)
        self.curr_joint_pos = np.array([0.0, 0.0], dtype=np.double)
        self.init_joint_pos = np.array([0.0, 0.0], dtype=np.double)
        self.curr_joint_vel = np.array([0.0, 0.0], dtype=np.double)
        self.rho = np.array(2000.0, dtype=np.double)
        self.radius = np.array(0.02, dtype=np.double)
        self.arm_length = np.array(arm_length, dtype=np.double)
        self.arm_length_sum = np.sum(self.max_length)
        self.workspace_radius = 2.0
        self.target_threshold = self.convert_range(0.2, 0, 2*self.arm_length_sum, 0, 1)

        # Initialize output arrays
        self.pos_tcp = np.empty(3, dtype=np.double)
        self.vel_tcp = np.array([0.0, 0.0, 0.0], dtype=np.double)
        self.target_pos_tcp = np.array([0.0, 0.0, 0.0], dtype=np.double)
        self.curr_joint_acc = np.array([0.0, 0.0], dtype=np.double)
        self.prev_pos_tcp = np.array([0.0, 0.0, 0.0], dtype=np.double)

        # Initial time and time step
        self.dt = 0.001 # 1 ms

        self.max_joint_pos = np.array([m.pi, m.pi], dtype=np.double)
        self.min_joint_pos = np.array([-m.pi, -m.pi], dtype=np.double)
        self.min_joint_vel = np.array([-20.0, -20.0], dtype=np.double)
        self.max_joint_vel = np.array([20.0, 20.0], dtype=np.double)
        self.max_torque = np.array([10.0, 10.0], dtype=np.double)
        self.min_torque = np.array([-10.0, -10.0], dtype=np.double)
        self.pos_tcp_range_x = np.array([-self.arm_length_sum, self.arm_length_sum], dtype=np.double)
        self.pos_tcp_range_y = np.array([-self.arm_length_sum, self.arm_length_sum], dtype=np.double)
        self.vel_tcp_range_x = np.array([-10.0, 10.0], dtype=np.double)
        self.vel_tcp_range_y = np.array([-10.0, 10.0], dtype=np.double)

        # Instantiate the FirstOrderDelay class
        self.filter = FirstOrderDelay(alpha=0.1)

        np.set_printoptions(precision=2)

    def step(self, action):

        self.steps += 1
        done = False
        early_Stop = False

        joint_torque_action = self.convert_range(action, -1, 1, self.min_torque, self.max_torque)


        for _ in range(self.freq):
            # Call the wrapped function
            self.joint_torque = self.filter.step(joint_torque_action)

            self.model.scara_robot_2dof_FD(self.curr_joint_pos, self.curr_joint_vel,
                                        self.rho, self.radius, self.arm_length,
                                        self.joint_torque, self.curr_joint_acc, self.pos_tcp)

            # Integrating the acceleration to get velocity
            self.curr_joint_vel = self.curr_joint_vel + self.curr_joint_acc * self.dt
            self.curr_joint_vel = np.array(self.curr_joint_vel, dtype=np.double)
            self.curr_joint_vel = np.clip(self.curr_joint_vel, self.min_joint_vel, self.max_joint_vel)

            # Integrating the velocity to get position
            self.curr_joint_pos = self.curr_joint_pos + self.curr_joint_vel * self.dt
            self.curr_joint_pos = np.array(self.curr_joint_pos, dtype=np.double)

            #differentiate the position to get velocity
            self.vel_tcp = (self.pos_tcp - self.prev_pos_tcp) / self.dt
            self.prev_pos_tcp = self.pos_tcp.copy()

        # joint position shiuld be converted to range -pi to pi for e.g. pi to 3pi or 3pi to 5pi tpshould be converted to -pi to pi

        self.curr_joint_pos = np.fmod(self.curr_joint_pos + np.pi, 2 * np.pi) - np.pi

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

        obs_pos_vec = obs_tcp_pos - obs_target_pos
        target_dist = np.linalg.norm(self.target_pos_tcp - self.pos_tcp)
        target_dist = self.convert_range(target_dist, 0, 2*self.arm_length_sum, 0, 1)
        obs_target_dist = np.array([target_dist], dtype=np.double)

        reward_target = 1 / (target_dist + 1e-6)
        reward_target = np.clip(reward_target, 0, 1/self.target_threshold)
        reward_target = self.convert_range(reward_target, 0, 1/self.target_threshold, 0, 1)

        # reward_target = 1 - target_dist

        if target_dist < self.target_threshold:
            penalty_time = +1
        else:
            penalty_time = -1

        input_penalty = np.linalg.norm(np.average(abs(obs_joint_torque)))

        reward = self.TARGET_COEFF * reward_target - self.ACTION_PENALTY_COEFF * input_penalty

        #curriculam learning
        #shortest path to target is a straight line

        if target_dist > self.target_threshold:
            if np.dot(self.target_pos_tcp-self.pos_tcp, self.vel_tcp) < 0:
                reward = -1.0
                done = True
                early_Stop = True

        # + self.ACTION_PENALTY_COEFF * input_penalty
        # print(f"target_dist: {obs_pos_vec[0]:<7.4f}{obs_pos_vec[1]:<7.4f}, dist: {np.linalg.norm(self.target_pos_tcp - self.pos_tcp):<7.2f}, reward_tar: {reward_target:<7.2f}, reward_input: {input_penalty:<7.2f}, reward_total: {reward:<7.2f}")

        # print(f"pos_vec: {obs_pos_vec[0]:<7.4f}{obs_pos_vec[1]:<7.4f}, dist: {np.linalg.norm(self.target_pos_tcp - self.pos_tcp):<7.2f}, joint_pos: {obs_joint_pos[0]:<7.2f}{obs_joint_pos[1]:<7.2f}")

        # observation = np.concatenate([obs_joint_pos, obs_joint_vel, obs_tcp_pos[:2], obs_vel_tcp[:2], obs_target_pos[:2], obs_pos_vec[:2]])
        observation = np.concatenate([obs_joint_torque, obs_pos_vec[:2], obs_tcp_pos[:2], obs_target_pos[:2] ,obs_vel_tcp[:2] , obs_joint_pos, obs_joint_vel, obs_arm_length])

        info = {'joint_pos': self.curr_joint_pos, 'arm_length': self.arm_length,
                'joint_torque': self.joint_torque, 'pos_tcp': self.pos_tcp, 'vel_tcp': self.vel_tcp,
                'target_pos': self.target_pos_tcp}

        observation = observation.astype(np.float32)
        reward = float(reward)

        #end the episode if the joints goes out of bounds
        # if (self.curr_joint_pos[0] > self.max_joint_pos[0] or self.curr_joint_pos[0] < self.min_joint_pos[0] or
        #     self.curr_joint_pos[1] > self.max_joint_pos[1] or self.curr_joint_pos[1] < self.min_joint_pos[1]):
        #     done = True
        #     early_Stop = True
        #     reward = -1.0
        #     reward = float(reward)
        #     return observation, reward, done, early_Stop, info

        if (np.any(np.isnan(observation)) or np.any(np.isinf(observation))):
            print("nan or inf detected in step", self.arm_length)
            print(observation)
            observation = np.ones(16)
            reward = -1.0
            reward = float(reward)
            done = True
            early_Stop = True
        return observation, reward, done, early_Stop, info

    def reset(self, seed=None):

        self.steps = 0

        # reset the robot
        self.curr_joint_pos = np.array([0.0, 0.0], dtype=np.double)
        self.curr_joint_vel = np.array([0.0, 0.0], dtype=np.double)
        self.curr_joint_acc = np.array([0.0, 0.0], dtype=np.double)
        self.pos_tcp = np.empty(3, dtype=np.double)
        self.joint_torque = np.array([0.0, 0.0], dtype=np.double)

        #Randomize the arm length
        if self.call_back == "random_design":
            self.arm_length = np.array([random.uniform(self.min_length[0], self.max_length[0]),
                                        random.uniform(self.min_length[1], self.max_length[1])], dtype=np.double)

        if self.call_back == "constant_design" or self.call_back == "random_design":
            # target positions should lie in a circle of radius r cenetered at (0,0)
            theta = random.uniform(0, 2*np.pi)  # Random angle
            # self.workspace_radius = np.sum(self.arm_length)
            radius = random.uniform(0, self.workspace_radius)
            self.target_pos_tcp = self.generate_target_position(radius, theta)
            self.init_joint_pos = np.array([random.uniform(self.min_joint_pos[0], self.max_joint_pos[0]),
                                            random.uniform(self.min_joint_pos[1], self.max_joint_pos[1])], dtype=np.double)

        # restrict arm length to 2 significant digits
        self.arm_length = np.round(self.arm_length, 2)
        self.curr_joint_pos = self.init_joint_pos
        self.vel_tcp = np.array([0.0, 0.0, 0.0], dtype=np.double)
        # Call the wrapped function
        self.model.scara_robot_2dof_FD(self.curr_joint_pos, self.curr_joint_vel,
                                    self.rho, self.radius, self.arm_length,
                                    self.joint_torque, self.curr_joint_acc,
                                    self.pos_tcp)


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

        obs_pos_vec = obs_tcp_pos - obs_target_pos
        target_dist = np.linalg.norm(self.target_pos_tcp - self.pos_tcp)
        target_dist = self.convert_range(target_dist, 0, 2*self.arm_length_sum, 0, 1)
        obs_target_dist = np.array([target_dist], dtype=np.double)

        observation = np.concatenate([obs_joint_torque, obs_pos_vec[:2], obs_tcp_pos[:2], obs_target_pos[:2] ,obs_vel_tcp[:2] , obs_joint_pos, obs_joint_vel, obs_arm_length])
        if (np.any(np.isnan(observation)) or np.any(np.isinf(observation))):
            print("nan or inf detected in reset", self.arm_length)
            print(observation)
            observation = np.ones(16)
            print(observation)


        info = {'joint_pos': self.curr_joint_pos, 'arm_length': self.arm_length,
                'joint_torque': self.joint_torque, 'pos_tcp': self.pos_tcp, 'vel_tcp': self.vel_tcp,
                'target_pos': self.target_pos_tcp}

        return observation, info

    def set_arm_length(self, arm_length):
        self.arm_length = arm_length

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

class FirstOrderDelay:
    def __init__(self, alpha, initial_output=0):
        self.alpha = alpha
        self.previous_output = initial_output

    def step(self, current_input):
        current_output = (1 - self.alpha) * self.previous_output + self.alpha * current_input
        self.previous_output = current_output
        return current_output
