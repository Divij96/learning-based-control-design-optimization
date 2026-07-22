#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Nov 23 16:06:12 2023

@author: adrianbuda
"""

from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[2]

import numpy as np

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

from random import randrange
# import tf2_ros
# import tf.transformations as tf_trans
import sys
import os
sys.path.append(f'{REPO_ROOT}/cpp/bindings/build/python')

import Aerofoil_Model_wrapper as mw  #needs to be changed

class AerofoilEnv(utils.EzPickle, gym.Env):
    metadata = {
        "render_modes": [
            "human",
        ],
        "render_fps": 20,
    }

    def __init__(self, REWARD = np.array([0.0, 0.0]), env_id = 0, mass = 15.94, x_cg = 0.35, x_ea = 0.45, k_h = 1, k_alpha = 1, call_back = f"constant_design"):
        super(AerofoilEnv, self).__init__()

        utils.EzPickle.__init__(self)
        self.call_back = call_back
        self.action_space = Box(low=-1, high=1, shape=(1,))
        if self.call_back == "constant_design":
            self.observation_space = Box(low=-1, high=1, shape=(7,))
        else:
            self.observation_space = Box(low=-1, high=1, shape=(12,))

        self.model = mw.cart_pole_system_dynamics0()   #needs to be changed
        self.freq = 1
        self.steps = 0
        self.env_id = env_id

        #reward function
        self.TARGET_CL = REWARD[0]
        self.ACTION_PENALTY = REWARD[1]

        self.desired_CL = 0

        #Design parameters
        self.mass = mass
        self.MIN_MASS = 1
        self.MAX_MASS = 100

        self.x_cg = x_cg
        self.MIN_X_CG = 0
        self.MAX_X_CG = 1

        self.x_ea = x_ea
        self.MIN_X_EA = 0
        self.MAX_X_EA = 1

        self.k_h = k_h
        self.MIN_K_H = 0.1
        self.MAX_K_H = 10

        self.k_alpha = k_alpha
        self.MIN_K_ALPHA = 0.1
        self.MAX_K_ALPHA = 10


        self.opt_change_len = False

        #action
        self.delta = 0
        self.prev_action = 0
        self.MIN_DELTA = -m.pi/8
        self.MAX_DELTA = m.pi/8

        #observation
        self.pitch = 0
        self.pitch_dot = 0
        self.plunge = 0
        self.plunge_dot = 0
        self.delta = 0
        self.delta_dot = 0
        self.CL = 0

        self.MIN_PITCH = -m.pi/8
        self.MAX_PITCH = m.pi/8

        self.MIN_DELTA = -m.pi/8
        self.MAX_DELTA = m.pi/8

        np.set_printoptions(precision=2)

    def convert_range(self,x, min_x, max_x, min_y, max_y):
        return (x - min_x) / (max_x - min_x) * (max_y - min_y) + min_y

    def step(self, action):
        self.steps += 1
        done = False
        early_Stop = False
        action = np.clip(action, -1, 1)
        reward_action = action
        action = self.convert_range(action ,-1, 1 ,self.MIN_DELTA, self.MAX_DELTA)


        self.model.set_A_ae(self.A_ae)
        self.model.set_B_ae(self.B_ae)
        self.model.set_C_ae(self.C_ae)
        self.model.set_delta(action)

        for _ in range(self.freq):
            self.model.step()

        self.pitch = self.model.get_pitch()
        self.pitch_dot = self.model.get_pitch_dot()
        self.plunge = self.model.get_plunge()
        self.plunge_dot = self.model.get_plunge_dot()
        self.delta = self.model.get_delta()
        self.delta_dot = self.model.get_delta_dot()

        self.CL = self.model.get_CL()
        self.prev_action = 0

        obs_pitch = np.clip(self.pitch, -m.pi/8, m.pi/8)
        obs_pitch = self.convert_range(obs_pitch, -m.pi/8, m.pi/8, -1, 1)

        obs_pitch_dot = np.clip(self.pitch_dot, -m.pi, m.pi)
        obs_pitch_dot = self.convert_range(obs_pitch_dot, -m.pi, m.pi, -1, 1)

        obs_plunge = np.clip(self.plunge, -10, 10)
        obs_plunge = self.convert_range(obs_plunge, -10, 10, -1, 1)

        obs_plunge_dot = np.clip(self.plunge_dot, -5, 5)
        obs_plunge_dot = self.convert_range(obs_plunge_dot, -5, 5, -1, 1)

        obs_delta = np.clip(self.delta, -m.pi/8, m.pi/8)
        obs_delta = self.convert_range(obs_delta, -m.pi/8, m.pi/8, -1, 1)

        obs_delta_dot = np.clip(self.pitch_dot, -m.pi, m.pi)
        obs_delta_dot = self.convert_range(obs_delta_dot, -m.pi, m.pi, -1, 1)

        obs_CL = self.convert_range(obs_delta_dot, -10, 10, -1, 1)

        obs_mass = np.array([self.convert_range(self.mass, self.MIN_MASS, self.MAX_MASS, -1, 1)])
        obs_x_cg = np.array([self.convert_range(self.x_cg, self.MIN_X_CG, self.MAX_X_CG, -1, 1)])
        obs_x_ea = np.array([self.convert_range(self.x_ea, self.MIN_X_EA, self.MAX_X_EA, -1, 1)])
        obs_k_h = np.array([self.convert_range(self.k_h, self.MIN_K_H, self.MAX_K_H -1, 1)])
        obs_k_alpha = np.array([self.convert_range(self.k_alpha, self.MIN_K_ALPHA, self.MAX_K_ALPHA, -1, 1)])

        #reward function
        high_action_penalty_reward = -self.ACTION_PENALTY * reward_action
        if self.pitch > self.MIN_PITCH and self.pitch < self.MAX_PITCH and self.delta > self.MIN_DELTA and self.delta < self.MAX_DELTA:
            desired_CL_reward = (obs_CL-self.desired_CL) * self.TARGET_CL
        else:
            desired_CL_reward = 0


        reward = high_action_penalty_reward + desired_CL_reward

        if(self.pitch < self.MIN_PITCH or self.pitch > self.MAX_PITCH or self.delta < self.MIN_DELTA or self.delta > self.MAX_DELTA):
            reward = -1.0
            done = True
            early_Stop = True


        if self.call_back == "constant_design":
            observation = np.concatenate([obs_pitch, obs_pitch_dot, obs_plunge, obs_plunge_dot, obs_delta, obs_delta_dot, obs_CL])
        else:
            observation = np.concatenate([obs_pitch, obs_pitch_dot, obs_plunge, obs_plunge_dot, obs_delta, obs_delta_dot, obs_CL, obs_mass, obs_x_cg, obs_x_ea, obs_k_h, obs_k_alpha])

        if (np.any(np.isnan(self.pitch)) or np.any(np.isinf(self.pitch)) or
            np.any(np.isnan(self.pitch_dot)) or np.any(np.isinf(self.pitch_dot)) or
            np.any(np.isnan(self.plunge)) or np.any(np.isinf(self.plunge)) or
            np.any(np.isnan(self.plunge_dot)) or np.any(np.isinf(self.plunge_dot)) or
            np.any(np.isnan(self.delta)) or np.any(np.isinf(self.delta)) or
            np.any(np.isnan(self.delta_dot)) or np.any(np.isinf(self.delta_dot))):
            print("nan or inf detected in reset")
            observation = np.ones(12)
            self.prev_action = action
            if self.call_back == "constant_design":
                observation = np.ones(7)
            else:
                observation = np.ones(12)

            reward = -1.0
            reward = float(reward)
            done = True
            early_Stop = True

        self.prev_action = reward_action
        observation = observation.astype(np.float32)
        reward = float(reward)
        return observation, reward, done, early_Stop, {"pitch": self.pitch, "plunge": self.plunge, "delta": self.delta, "CL": self.CL}

    def reset(self, seed=None):
        self.steps = 0

        # if self.call_back != "constant_design":
        #     if not self.opt_change_len:
        #         self.pole_length = random.uniform(self.MIN_POLE_LENGTH, self.MAX_POLE_LENGTH)
        self.model.initialize()
        self.model.set_A_ae(self.A_ae)
        self.model.set_B_ae(self.B_ae)
        self.model.set_C_ae(self.C_ae)
        self.init_pitch = random.uniform(-m.pi/8, m.pi/8)
        self.model.set_init_pitch(self.init_pitch)

        self.pitch = self.model.get_pitch()
        self.pitch_dot = self.model.get_pitch_dot()
        self.plunge = self.model.get_plunge()
        self.plunge_dot = self.model.get_plunge_dot()
        self.delta = self.model.get_delta()
        self.delta_dot = self.model.get_delta_dot()

        self.CL = self.model.get_CL()
        self.prev_action = 0

        obs_pitch = np.clip(self.pitch, -m.pi/8, m.pi/8)
        obs_pitch = self.convert_range(obs_pitch, -m.pi/8, m.pi/8, -1, 1)

        obs_pitch_dot = np.clip(self.pitch_dot, -m.pi, m.pi)
        obs_pitch_dot = self.convert_range(obs_pitch_dot, -m.pi, m.pi, -1, 1)

        obs_plunge = np.clip(self.plunge, -10, 10)
        obs_plunge = self.convert_range(obs_plunge, -10, 10, -1, 1)

        obs_plunge_dot = np.clip(self.plunge_dot, -5, 5)
        obs_plunge_dot = self.convert_range(obs_plunge_dot, -5, 5, -1, 1)

        obs_delta = np.clip(self.delta, -m.pi/8, m.pi/8)
        obs_delta = self.convert_range(obs_delta, -m.pi/8, m.pi/8, -1, 1)

        obs_delta_dot = np.clip(self.pitch_dot, -m.pi, m.pi)
        obs_delta_dot = self.convert_range(obs_delta_dot, -m.pi, m.pi, -1, 1)

        obs_CL = self.convert_range(obs_delta_dot, -10, 10, -1, 1)

        obs_mass = np.array([self.convert_range(self.mass, self.MIN_MASS, self.MAX_MASS, -1, 1)])
        obs_x_cg = np.array([self.convert_range(self.x_cg, self.MIN_X_CG, self.MAX_X_CG, -1, 1)])
        obs_x_ea = np.array([self.convert_range(self.x_ea, self.MIN_X_EA, self.MAX_X_EA, -1, 1)])
        obs_k_h = np.array([self.convert_range(self.k_h, self.MIN_K_H, self.MAX_K_H -1, 1)])
        obs_k_alpha = np.array([self.convert_range(self.k_alpha, self.MIN_K_ALPHA, self.MAX_K_ALPHA, -1, 1)])

        if self.call_back == "constant_design":
            observation = np.concatenate([obs_pitch, obs_pitch_dot, obs_plunge, obs_plunge_dot, obs_delta, obs_delta_dot, obs_CL])
        else:
            observation = np.concatenate([obs_pitch, obs_pitch_dot, obs_plunge, obs_plunge_dot, obs_delta, obs_delta_dot, obs_CL, obs_mass, obs_x_cg, obs_x_ea, obs_k_h, obs_k_alpha])

        if (np.any(np.isnan(self.pitch)) or np.any(np.isinf(self.pitch)) or
            np.any(np.isnan(self.pitch_dot)) or np.any(np.isinf(self.pitch_dot)) or
            np.any(np.isnan(self.plunge)) or np.any(np.isinf(self.plunge)) or
            np.any(np.isnan(self.plunge_dot)) or np.any(np.isinf(self.plunge_dot)) or
            np.any(np.isnan(self.delta)) or np.any(np.isinf(self.delta)) or
            np.any(np.isnan(self.delta_dot)) or np.any(np.isinf(self.delta_dot))):
            print("nan or inf detected in reset")
            if self.call_back == "constant_design":
                observation = np.ones(7)
            else:
                observation = np.ones(12)
            observation = observation.astype(np.float32)
            reward = -1.0
            reward = float(reward)

        return observation

    def set_pole_length(self, pole_length):
        self.pole_length = pole_length
        self.pole_mass = self.pole_density * self.pole_length

        self.opt_change_len = True

    def get_pole_length(self):
        return self.pole_length

    def set_env_id(self, env_id):
        self.env_id = env_id

    def get_env_id(self):
        return self.env_id

    def render(self, mode='human'):
        pass

    def close(self):
        pass

    def deg_to_rad(self, deg):
        return deg * m.pi / 180.0
