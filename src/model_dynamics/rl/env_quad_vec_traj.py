from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[3]

import numpy as np
import gymnasium as gym
from gymnasium import utils
from gymnasium.spaces import Box
import math as m
import random
import sys
import time
sys.path.append(f'{REPO_ROOT}/devel/lib')

import Model_wrapper as mw

class QuadcopterEnv(utils.EzPickle, gym.Env):
    metadata = {
        "render_modes": [
            "human",
        ],
        "render_fps": 20,
    }

    def __init__(self, arm_length = np.array([0.17,0.17,0.17,0.17]), REWARD = np.array([0.0, 0.5, 0.0]), env_id = 1, arm_length_limits = np.array([0.01, 2.0]) ,n_steps_train = 512 * 2, callback=f"eval_design"):
        super(QuadcopterEnv, self).__init__()

        utils.EzPickle.__init__(self)
        self.action_space = Box(low=-1, high=1, shape=(4,))

        self.Max_propeller_speed = 4000
        self.Min_propeller_speed = 0
        self.n_steps_train = n_steps_train
        self.traj_length = n_steps_train
        self.arm_length_limits = arm_length_limits
        self.callback = callback

        self.freq = 10
        self.env_id = env_id
        self.observation_space = Box(low=-1, high=1, shape=(36,))
        self.steps = 0
        self.init_num = 0
        self.next_n_obs = 5
        self.model = mw.multirotor0()
        self.TARGET_POS = np.array([0.0, 0.0, 0.0])  # for example
        self.QUAT_DES = np.array([1.0, 0.0, 0.0, 0.0])  # for example
        self.R_DES = np.array([1.0, 0.0 , 0.0 , 0.0 , 1.0 , 0.0 , 0.0 , 0.0 , 1.0])
        self.INIT_POS = np.array([0.0, 0.0, 0.0])  # for example
        self.INIT_VEL = np.array([0.0, 0.0, 0.0])  # for example
        self.INIT_OMEGA = np.array([0, 0.0, 0.0])  # for example
        self.INIT_ATT = np.array([0.0, 0.0, 0.0], dtype=np.float64)

        self.max_init_vel = 0
        self.max_init_omega = 0
        self.MAX_POS = 10.0
        self.MAX_OMEGA = 5.0
        self.MAX_VEL = 15.0
        self.major_radius = 2.0
        self.minor_radius = 0.5

        #reward function
        self.PROPELLER_SPEED = REWARD[0]
        self.VELOCITY_REWARD = REWARD[1]
        self.ANGULAR_VELOCITY_PENALTY = -REWARD[2]

        #Design parameters
        #Design parameters
        self.arm_length = np.array([0.4051
                                    ,0.6522
                                    ,0.9356,
                                    0.5377])
        # self.arm_length = np.array([0.5
        #                             ,0.5
        #                             ,0.5,
        #                             0.5])
                            # Best design: x1    0.287804
                            # x2    0.498948
                            # x3    0.595183
                            # x4    0.540826


        self.propeller_height = np.array([-0.028, -0.028, -0.028, -0.028])
        self.propeller_diameter = np.array([0.2032, 0.2032, 0.2032, 0.2032])
        self.rotation_direction = np.array([1, -1, 1, -1])
        self.max_rpm = np.array([self.Max_propeller_speed, self.Max_propeller_speed, self.Max_propeller_speed, self.Max_propeller_speed])
        self.min_rpm = np.array([0.0, 0.0, 0.0, 0.0])
        self.arm_radius = np.array([0.0013, 0.0013, 0.0013, 0.0013])
        self.motor_arm_angle = np.array([45, 135, 225, 315])
        self.mass_center = 0.1
        self.COM_mass_center = np.array([0, 0, 0])
        self.set_Surface_params = np.array([0.12, 0.12, 0.06])
        self.obs_next_n_desired_vel_grad = []
        self.obs_next_n_desired_pos = []
        self.traj_radius = 2
        self.zone_change = self.traj_radius
        self.zone = 0
        self.closest_point = np.array([0, 0, 0])

        self.monaco_traj = np.array([   (341, 14, 0),
                                        (583, 169, 0),
                                        (774, 260, 0),
                                        (804, 155, 0),
                                        (1066, 127, 0),
                                        (1011, 276, 0),
                                        (1098, 200, 0),
                                        (1157, 235, 0),
                                        (888, 354, 0),
                                        (521, 248, 0),
                                        (255, 234, 0),
                                        (189, 325, 0),
                                        (137, 407, 0),
                                        (121, 349, 0),
                                        (23, 420, 0)])
        #shift the trajectory to the origin
        self.monaco_traj = self.monaco_traj - np.array([341, 14, 0])
        self.monaco_traj = self.monaco_traj / 10
        self.closest_point = self.monaco_traj[0]
        np.set_printoptions(precision=2)

    def step(self, action):
        done = False
        if action is np.inf or action is -np.inf:
            print("action is inf")
        w  = self.convert_range(action, -1, 1, self.Min_propeller_speed, self.Max_propeller_speed)

        #set design parameters and the rpm
        self.model.set_arm_length(self.arm_length)
        self.model.set_propeller_height(self.propeller_height)
        self.model.set_propeller_diameter(self.propeller_diameter)
        self.model.set_rotation_direction(self.rotation_direction)
        self.model.set_max_rpm(self.max_rpm)
        self.model.set_min_rpm(self.min_rpm)
        self.model.set_arm_radius(self.arm_radius)
        self.model.set_motor_arm_angle(self.motor_arm_angle)
        self.model.set_mass_center(self.mass_center)
        self.model.set_COM_mass_center(self.COM_mass_center)
        self.model.set_Surface_params(self.set_Surface_params)

        self.model.set_wind_vector(np.array([0.0 * np.sin(0.2 * self.steps/100),
                                            0.0 * np.cos(0.3 * self.steps/100),
                                            0.0 * np.sin(0.1 * self.steps/100)]))

        self.model.set_force_disturb_vector(np.array([0.0, 0.0, 0.0]))
        self.model.set_moment_disturb_vector(np.array([0.0, 0.0, 0.0]))
        self.model.set_w_0(w)

        #step the model at self.freq times
        for i in range(self.freq):
            self.model.step2() #sets the propeller speeds
            self.model.step0()

        #get position
        pos_world = self.model.get_pos_world()
        #get rotation matrix
        R = self.model.get_RotationMatrix_world()
        #get velocity
        vel_world = self.model.get_velocity_world()
        obs_rotation_matrix = np.clip(R, -1, 1)
        obs_rotation_matrix = obs_rotation_matrix.flatten()
        #get angular velocity
        omega_world = self.model.get_omega_world()
        #get propeller speed
        propeller_speed = self.model.get_motor_rpm()

        if (np.any(np.isnan(pos_world)) or np.any(np.isinf(pos_world)) or
            np.any(np.isnan(vel_world)) or np.any(np.isinf(vel_world)) or
            np.any(np.isnan(omega_world)) or np.any(np.isinf(omega_world)) or
            np.any(np.isnan(R)) or np.any(np.isinf(R))):
            print("nan or inf detected")

            observation = np.ones(36)

            observation = observation.astype(np.float32)
            reward = -1.0
            reward = float(reward)
            early_Stop = False
            done  = True
            return observation, reward, done, early_Stop, {"pos_world": pos_world, "target_pos": self.TARGET_POS, "init_pos": self.INIT_POS, "rot_matrix_world":R.flatten(), "vel_world": vel_world, "omega_world": omega_world, "action": action, "reward": reward, "propeller_speed": propeller_speed, "action_motor_rpm": w, "arm_length": self.arm_length, "action_penalty": 0.0, "omega_world_penalty": 0.0, "steps": self.steps, "desired_path": pos_world }

        #find the distance between point and line
        if self.zone + 1 < len(self.monaco_traj):
            distance_zone_t, self.closest_point = self.distance_point_to_segment(pos_world, self.monaco_traj[self.zone], self.monaco_traj[self.zone + 1])
        else:
            distance_zone_t, self.closest_point = self.distance_point_to_segment(pos_world, self.monaco_traj[self.zone], self.monaco_traj[0])

        obs_vel_mag = np.linalg.norm(vel_world)
        obs_distance_zone_t = self.convert_range(distance_zone_t, 0, self.traj_radius, 0, 1)
        obs_velocity_vector = vel_world / obs_vel_mag
        if self.zone + 1 < len(self.monaco_traj):
            obs_velocity_des_grad = self.monaco_traj[self.zone] - self.monaco_traj[self.zone + 1]
            obs_pos_vec = pos_world - self.monaco_traj[self.zone + 1]
        else:
            obs_velocity_des_grad = self.monaco_traj[self.zone] - self.monaco_traj[0]
            obs_pos_vec = pos_world - self.monaco_traj[0]

        obs_pos_vec_mag = np.linalg.norm(obs_pos_vec)
        obs_velocity_des_grad = -obs_velocity_des_grad / np.linalg.norm(obs_velocity_des_grad)
        obs_velocity_des_grad = np.clip(obs_velocity_des_grad, -1, 1)

        if self.zone + 2 < len(self.monaco_traj):
            obs_velocity_next_des_grad = self.monaco_traj[self.zone + 1] - self.monaco_traj[self.zone + 2]
        else:
            obs_velocity_next_des_grad = self.monaco_traj[0] - self.monaco_traj[1]

        obs_velocity_next_des_grad = -obs_velocity_next_des_grad / (np.linalg.norm(obs_velocity_next_des_grad) + 0.001)
        obs_velocity_next_des_grad = np.clip(obs_velocity_next_des_grad, -1, 1)

        obs_velocity_dot_product = np.dot(obs_velocity_vector, obs_velocity_des_grad)
        obs_velocity_dot_product = self.convert_range(obs_velocity_dot_product, -1, 1, 0, 1)
        obs_velocity_dot_product = np.clip(obs_velocity_dot_product, 0, 1)

        obs_vel_mag = self.convert_range(obs_vel_mag, 0, self.MAX_VEL, 0, 1)

        omega_world = np.clip(omega_world, -self.MAX_OMEGA, self.MAX_OMEGA)
        # obs_omega_norm = self.convert_range(omega_world, -self.MAX_OMEGA, self.MAX_OMEGA, -1, 1)
        obs_omega_norm = omega_world/np.linalg.norm(omega_world)

        #clip arm length
        obs_arm_length = np.clip(self.arm_length, self.arm_length_limits[0], self.arm_length_limits[1])
        obs_arm_length = self.convert_range(obs_arm_length, self.arm_length_limits[0], self.arm_length_limits[1], -1, 1)


        propeller_speed = np.clip(propeller_speed, self.Min_propeller_speed, self.Max_propeller_speed)
        obs_propeller_speed_norm = self.convert_range(propeller_speed, self.Min_propeller_speed, self.Max_propeller_speed, -1, 1)

        #reward function
        reward_vel_dot_des_grad = obs_vel_mag * obs_velocity_dot_product

        reward_ang_vel = np.linalg.norm(omega_world)
        reward_ang_vel_norm = self.convert_range(reward_ang_vel, -self.MAX_OMEGA, self.MAX_OMEGA, 0, 1)
        reward_ang_vel_norm = np.clip(reward_ang_vel_norm, 0, 1)

        reward = reward_vel_dot_des_grad - 0.2*reward_ang_vel_norm

        if distance_zone_t > self.traj_radius:
            done = True
            reward = -1.0

        if obs_pos_vec_mag < self.zone_change:
            self.zone += 1
            if self.zone == len(self.monaco_traj):
                self.zone = 0
        obs_pos_vec_mag = self.convert_range(obs_pos_vec_mag, 0, np.linalg.norm(obs_velocity_des_grad), 0, 1)

        observation = np.concatenate([obs_velocity_vector,
                                    obs_velocity_des_grad,
                                    obs_velocity_next_des_grad,
                                    np.array([obs_velocity_dot_product]),
                                    np.array([obs_vel_mag]),
                                    obs_pos_vec,
                                    np.array([obs_pos_vec_mag]),
                                    np.array([obs_distance_zone_t]),
                                    obs_omega_norm,
                                    obs_rotation_matrix,
                                    obs_propeller_speed_norm,
                                    obs_arm_length])
        self.steps += 1
        observation = observation.astype(np.float32)
        reward = float(reward)
        early_Stop = False
        return observation, reward, done, early_Stop, {"pos_world": pos_world, "init_pos": self.INIT_POS, "rot_matrix_world":R.flatten(), "vel_world": vel_world, "omega_world": omega_world, "action": action, "reward": reward, "propeller_speed": propeller_speed, "action_motor_rpm": w, "arm_length": self.arm_length, "steps": self.steps, "desired_path": pos_world, "orignal_traj":self.monaco_traj[self.zone] }

    def reset(self, seed=None):


        if self.callback == "random_design" or self.callback == "eval_design":
            self.arm_length = np.array([random.uniform(self.arm_length_limits[0],self.arm_length_limits[1]),
                                        random.uniform(self.arm_length_limits[0],self.arm_length_limits[1]),
                                        random.uniform(self.arm_length_limits[0],self.arm_length_limits[1]),
                                        random.uniform(self.arm_length_limits[0],self.arm_length_limits[1])])

        self.set_Surface_params = np.array([(self.arm_length[0]+self.arm_length[2])/2,
                                            (self.arm_length[1]+self.arm_length[3])/2,
                                            0.06])

        if self.zone + 1 < len(self.monaco_traj):
            obs_velocity_des_grad = self.monaco_traj[self.zone] - self.monaco_traj[self.zone + 1]
        else:
            obs_velocity_des_grad = self.monaco_traj[self.zone] - self.monaco_traj[0]
        obs_velocity_des_grad = -obs_velocity_des_grad / np.linalg.norm(obs_velocity_des_grad)
        self.INIT_VEL = self.MAX_VEL * obs_velocity_des_grad
        self.INIT_POS =  self.closest_point
        self.INIT_OMEGA = np.array([0, 0.0, 0.0])  # for example
        self.INIT_ATT = np.array([0.0, 0.0, 0.0], dtype=np.float64)

        self.model.set_init_Att(self.INIT_ATT)
        self.model.set_w_0(np.array([3000.0, 3000.0, 3000.0, 3000.0]))
        self.model.set_arm_length(self.arm_length)
        self.model.set_propeller_height(self.propeller_height)
        self.model.set_propeller_diameter(self.propeller_diameter)
        self.model.set_rotation_direction(self.rotation_direction)
        self.model.set_max_rpm(self.max_rpm)
        self.model.set_min_rpm(self.min_rpm)
        self.model.set_arm_radius(self.arm_radius)
        self.model.set_motor_arm_angle(self.motor_arm_angle)
        self.model.set_init_pos(self.INIT_POS)
        self.model.set_init_vel(self.INIT_VEL)
        self.model.set_init_omega(self.INIT_OMEGA)
        self.model.set_Surface_params(self.set_Surface_params)

        self.model.initialize()
        self.model.step2() #sets the propeller speeds
        self.model.step0()

        #get position
        pos_world = self.model.get_pos_world()
        #find the distance between point and line
        if self.zone + 1 < len(self.monaco_traj):
            distance_zone_t, self.closest_point = self.distance_point_to_segment(pos_world, self.monaco_traj[self.zone], self.monaco_traj[self.zone + 1])
        else:
            distance_zone_t, self.closest_point = self.distance_point_to_segment(pos_world, self.monaco_traj[self.zone], self.monaco_traj[0])
        obs_distance_zone_t = self.convert_range(distance_zone_t, 0, self.traj_radius, 0, 1)

        #get rotation matrix
        R = self.model.get_RotationMatrix_world()
        # print(R)
        obs_rotation_matrix = np.clip(R, -1, 1)
        obs_rotation_matrix = obs_rotation_matrix.flatten()

        #get velocity
        vel_world = self.model.get_velocity_world()
        obs_vel_mag = np.linalg.norm(vel_world)
        obs_velocity_vector = vel_world / obs_vel_mag
        if self.zone + 1 < len(self.monaco_traj):
            obs_velocity_des_grad = self.monaco_traj[self.zone] - self.monaco_traj[self.zone + 1]
            obs_pos_vec = pos_world - self.monaco_traj[self.zone + 1]
        else:
            obs_velocity_des_grad = self.monaco_traj[self.zone] - self.monaco_traj[0]
            obs_pos_vec = pos_world - self.monaco_traj[0]

        obs_pos_vec_mag = np.linalg.norm(obs_pos_vec)
        obs_pos_vec_mag = self.convert_range(obs_pos_vec_mag, 0, np.linalg.norm(obs_velocity_des_grad), 0, 1)
        if self.zone + 2 < len(self.monaco_traj):
            obs_velocity_next_des_grad = self.monaco_traj[self.zone + 1] - self.monaco_traj[self.zone + 2]
        else:
            obs_velocity_next_des_grad = self.monaco_traj[0] - self.monaco_traj[1]

        obs_velocity_dot_product = np.dot(obs_velocity_vector, obs_velocity_des_grad)
        obs_velocity_dot_product = self.convert_range(obs_velocity_dot_product, -1, 1, 0, 1)
        obs_velocity_dot_product = np.clip(obs_velocity_dot_product, 0, 1)

        obs_vel_mag = self.convert_range(obs_vel_mag, 0, self.MAX_VEL, 0, 1)

        #get angular velocity
        omega_world = self.model.get_omega_world()
        omega_world = np.clip(omega_world, -self.MAX_OMEGA, self.MAX_OMEGA)
        # obs_omega_norm = self.convert_range(omega_world, -self.MAX_OMEGA, self.MAX_OMEGA, -1, 1)
        obs_omega_norm = omega_world/np.linalg.norm(omega_world)
        #clip arm length
        obs_arm_length = np.clip(self.arm_length, self.arm_length_limits[0], self.arm_length_limits[1])
        obs_arm_length = self.convert_range(obs_arm_length, self.arm_length_limits[0], self.arm_length_limits[1], -1, 1)

        #get propeller speed
        propeller_speed = self.model.get_motor_rpm()
        propeller_speed = np.clip(propeller_speed, self.Min_propeller_speed, self.Max_propeller_speed)
        obs_propeller_speed_norm = self.convert_range(propeller_speed, self.Min_propeller_speed, self.Max_propeller_speed, -1, 1)

        observation = np.concatenate([obs_velocity_vector,
                                    obs_velocity_des_grad,
                                    obs_velocity_next_des_grad,
                                    np.array([obs_velocity_dot_product]),
                                    np.array([obs_vel_mag]),
                                    obs_pos_vec,
                                    np.array([obs_pos_vec_mag]),
                                    np.array([obs_distance_zone_t]),
                                    obs_omega_norm,
                                    obs_rotation_matrix,
                                    obs_propeller_speed_norm,
                                    obs_arm_length])

        observation = observation.astype(np.float32)
        info = {}

        if (np.any(np.isnan(pos_world)) or np.any(np.isinf(pos_world)) or
            np.any(np.isnan(vel_world)) or np.any(np.isinf(vel_world)) or
            np.any(np.isnan(omega_world)) or np.any(np.isinf(omega_world)) or
            np.any(np.isnan(R)) or np.any(np.isinf(R))):
            print("nan or inf detected in reset")
            observation = np.ones(36)
            observation = observation.astype(np.float32)
            reward = -1.0
            reward = float(reward)

        return observation, info

    def render(self, mode='human'):
        pass

    def close(self):
        pass

    def set_init_pos(self, init_pos):
        self.INIT_POS = init_pos

    def get_init_pos(self):
        return self.INIT_POS

    def get_arm_length(self):
        return self.arm_length

    def set_arm_length(self, new_arm_length):
        self.arm_length = new_arm_length

    def set_int_Att(self, init_Att):
        self.INIT_ATT = init_Att

    def get_init_Att(self):
        return self.INIT_ATT

    def set_steps(self, steps):
        self.zone = steps
        self.INIT_POS = self.monaco_traj[steps]

    def is_within_radius(self,desired_point, current_point, radius):
        distance = np.linalg.norm(desired_point - current_point)
        return distance <= radius

    def set_env_id(self, env_id):
        self.env_id = env_id

    def get_env_id(self):
        return self.env_id

    def rotation_matrix_to_quaternion(self, rotation_matrix: np.array) -> tuple:
        a, b, c = rotation_matrix[0]
        d, e, f = rotation_matrix[1]
        g, h, i = rotation_matrix[2]
        q0 = np.sqrt(max(0, 1 + a + e + i)) / 2
        q1 = np.sqrt(max(0, 1 + a - e - i)) / 2
        q2 = np.sqrt(max(0, 1 - a + e - i)) / 2
        q3 = np.sqrt(max(0, 1 - a - e + i)) / 2
        q1 *= np.sign(f - h)
        q2 *= np.sign(g - c)
        q3 *= np.sign(b - d)
        magnitude = np.sqrt(q0**2 + q1**2 + q2**2 + q3**2)
        return q0 / magnitude, q1 / magnitude, q2 / magnitude, q3 / magnitude

    def cartesian_to_spherical_with_orientation(self, point, origin, R):
        # 1. Translate the point to make origin as (0, 0, 0)
        translated_point = point - origin

        # 2. Convert the translated point to spherical coordinates
        x, y, z = translated_point
        r = np.sqrt(x**2 + y**2 + z**2)

        # 3. Convert the spherical coordinates' angles with orientation in mind
        rotated_point = np.dot(R.reshape(3,3), translated_point)
        x_rot, y_rot, z_rot = rotated_point
        theta = np.arccos(z_rot / r) if r != 0 else 0
        phi = np.arctan2(y_rot, x_rot)

        return r, theta, phi

    def convert_range(self,x, min_x, max_x, min_y, max_y):
        return (x - min_x) / (max_x - min_x) * (max_y - min_y) + min_y

    def is_traj_in_bounds(self, points, bound):

        points = np.array(points)
        is_in_bounds = not (np.any(points>bound) or np.any(points<-bound))

        return is_in_bounds

    def set_motor_arm_angle(self, angles):
        self.motor_arm_angle = np.array([angles[0], 90 + angles[1], 180 + angles[2], 270 + angles[3]])

    def get_motor_arm_angle(self):
        return self.motor_arm_angle

    def gradient_direction(self,x, y):
        theta = np.arctan2(y, x)
        tangent_theta = theta + np.pi / 2

        dx = np.cos(tangent_theta)
        dy = np.sin(tangent_theta)

        return [dx, dy, 0]

    def is_inside_torus(self,x, y, z, R, r):
        d = np.sqrt(x**2 + y**2)
        return (d - R)**2 + z**2 < r**2

    def random_point_on_circle(self, r):
        theta = random.uniform(0, 2*np.pi)
        x = r * np.cos(theta)
        y = r * np.sin(theta)
        point = np.array([x, y, 0])
        return point


    def distance_point_to_segment(self, point, seg_start, seg_end):
        """
        Calculate the minimum distance between a point and a line segment in 3D.

        :param point: The point (a tuple or list of three numbers).
        :param seg_start: The starting point of the line segment (a tuple or list of three numbers).
        :param seg_end: The end point of the line segment (a tuple or list of three numbers).
        :return: The shortest distance from the point to the line segment.
        """
        # Convert to numpy arrays for vector operations
        p = np.array(point)
        a = np.array(seg_start)
        b = np.array(seg_end)

        # Vector from a to b
        ab = b - a
        # Vector from a to p
        ap = p - a

        # Projection of ap onto ab, from a
        t = np.dot(ap, ab) / np.dot(ab, ab)

        # Clamp t from [0,1]
        t = np.clip(t, 0, 1)

        # Find the closest point on the line segment
        closest_point = a + t * ab

        # Distance from p to the closest point on the line segment
        distance = np.linalg.norm(p - closest_point)

        return distance, closest_point

class QuadcopterTrajectory:
    def __init__(self, init_values):
        # Randomize the coefficients a, b, c (same for x, y, z)
        self.a, self.b, self.c = [init_values[0], init_values[1], init_values[2]]
        # For a closed loop, d = 0 and e = 2a + b (for x, y, z)
        self.d = 0
        self.e = 2*self.a + self.b
        # Similarly, for y and z
        self.f, self.g, self.h = [init_values[3], init_values[4], init_values[5]]
        self.i = 0
        self.j = 2*self.f + self.g
        # And for z
        self.k, self.l, self.m = [init_values[6], init_values[7], init_values[8]]
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
