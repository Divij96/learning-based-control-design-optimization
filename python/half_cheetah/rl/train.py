from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[3]

import time
from typing import Any, Dict
import torch
import torch.nn as nn
import torch.nn.functional as F
import numpy as np
import gym
import pandas as pd
import os
import shutil
import xml.etree.ElementTree as ET
from stable_baselines3.common.callbacks import BaseCallback
from stable_baselines3 import PPO
from half_cheetah_v4 import HalfCheetahEnv
from stable_baselines3.common.vec_env import SubprocVecEnv
from stable_baselines3.common.callbacks import BaseCallback
from gaussMix_design_opt import DesignDistribution_log as DesignDistribution
from hebo.design_space.design_space import DesignSpace
from hebo.optimizers.hebo import HEBO
from scipy.io import loadmat, savemat
from stable_baselines3.common.policies import ActorCriticPolicy
import random
import torch.nn as nn
import torch
import math
from sklearn.mixture import GaussianMixture
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


def main():
    #training parameters
    use_sde = False
    hidden_sizes_train = 256
    REWARD = np.array([1.0, 0.0])
    stiffness_limits = np.array([0.1, 5.0])
    stiffness = [306.338, 636.608, 217.815, 391.246, 224.492, 501.802]
    learning_rate_train = 0.0001
    n_epochs_train = 10
    LOAD_OLD_MODEL = False
    n_update_dist = 25
    n_number_dist = 48
    n_steps_train = 512
    n_envs_train =  50
    entropy_coeff_train = 0.0
    total_timesteps_train = n_steps_train * n_envs_train * 500

    batch_size_train = 128
    global_iteration = 0
    TRAIN = True
    CALL_BACK_FUNC = f"random_design"
    lr_std_schaff = 0.01
    lr_mean_schaff = 0.01

    original_xml_path = f"{REPO_ROOT}/assets/mujoco/half_cheetah/half_cheetah.xml"
    destination_folder = f"{REPO_ROOT}/assets/mujoco/half_cheetah/"
    # Copy the original file with new names
    for i in range(n_envs_train):
        new_file_name = f"half_cheetah_{i}.xml"
        new_file_path = os.path.join(destination_folder, new_file_name)
        shutil.copy2(original_xml_path, new_file_path)
        # print(f"Copied to: {new_file_path}")

    while True:
        #initialise the model PPO
        learning_rate_train = learning_rate_train

        onpolicy_kwargs = dict(activation_fn=torch.nn.Tanh,
                                net_arch=dict(vf=[hidden_sizes_train, hidden_sizes_train], pi=[hidden_sizes_train, hidden_sizes_train]))

        global_iteration += 1

        # Define unique initialization variables for each environment
        env_configs = [{'env_id': i ,'forward_reward_weight': 1.0, 'ctrl_cost_weight': 0.1, 'reset_noise_scale' : 0.1} for i in range(n_envs_train)]
        # Ensure we have configurations for each environment instance
        assert len(env_configs) == n_envs_train

        # Create function for each environment instance with its unique configuration
        env_fns = [lambda config=config: HalfCheetahEnv(**config) for config in env_configs]

        # Create the vectorized environment using SubprocVecEnv directly
        vec_env = SubprocVecEnv(env_fns, start_method='fork')
        model_name = f"HalfCheetah_{CALL_BACK_FUNC}_ent_{entropy_coeff_train}_lr_{learning_rate_train}_hid_size_{hidden_sizes_train}_FORreward_{REWARD[0]}_CTRLcost_{REWARD[1]}"
        log_dir = f"{REPO_ROOT}/python/half_cheetah/half_cheetah_tensorboard/TB_{model_name}"

        if LOAD_OLD_MODEL is True:
            new_model = []
            old_model = PPO.load(f"{REPO_ROOT}/python/half_cheetah/rl/trained_model/random_design/Half_cheetah_dynamics_constant_random_design_start_upd_25lr_mean0.01_std_0.01_sdeFalse_Tanh_Tsteps_25600000_lr_0.0001_hidden_sizes_256_FORreward_1.0_CTRLcost_1.0_var_design", env = vec_env)
            # Create a new model with the desired configuration
            new_model = PPO("MlpPolicy", env=vec_env, n_steps=n_steps_train,
                            batch_size=batch_size_train, n_epochs=n_epochs_train,
                            use_sde=use_sde, ent_coef=entropy_coeff_train,
                            learning_rate=learning_rate_train, policy_kwargs=onpolicy_kwargs,
                            device='cpu', verbose=1, tensorboard_log=log_dir)

            # Load the weights from the old model
            new_model.set_parameters(old_model.get_parameters())
        else:
            new_model = PPO("MlpPolicy", env = vec_env, n_steps = n_steps_train, batch_size = batch_size_train,
                n_epochs=n_epochs_train, use_sde = use_sde , ent_coef = entropy_coeff_train, learning_rate = learning_rate_train,
                policy_kwargs=onpolicy_kwargs, device ='cpu',verbose=1, tensorboard_log=log_dir)
            print("New model created")

        # Train the new model
        print("Model training...")
        # Now you can continue training with the new model
        if CALL_BACK_FUNC == "random_design":
            param_changer = random_design(model_name = model_name, model = new_model, n_steps_train = n_steps_train, n_envs_train = n_envs_train, verbose=1)
        elif CALL_BACK_FUNC == "Hebo_Gauss_callback":
            param_changer = Hebo_Gauss_callback(model_name = model_name, model = new_model, n_steps_train = n_steps_train, n_envs_train = n_envs_train, verbose=1)
        else:
            print("No callback function specified")
            break

        new_model.learn(total_timesteps = total_timesteps_train ,progress_bar=True, callback=param_changer)
        print("Model trained, saving...")
        new_model.save(f"{REPO_ROOT}/python/half_cheetah/rl/trained_model/random_design/{model_name}")
        print("Model saved")
        LOAD_OLD_MODEL = True
        vec_env.close()
        break


class random_design(BaseCallback):
    def __init__(self, model_name = f"matfile", model = None, n_steps_train=512 * 10, n_envs_train=8, verbose=0):

        super(random_design, self).__init__(verbose)
        self.model = model
        self.n_envs_train = n_envs_train
        self.n_steps_train = n_steps_train
        self.episode_rewards = {}
        self.rewards_iteration = {}
        self.design_iteration = [1 for _ in range(self.n_envs_train)]
        self.design_rewards = [0 for _ in range(self.n_envs_train)]
        self.episode_length = {}
        self.mat_stiffness = []
        self.mat_reward = []
        self.mat_iteration = []
        self.average_reward = []
        self.average_episode_length = []
        self.model_name = model_name
        self.design_iteration = [0 for _ in range(self.n_envs_train)]
        self.my_custom_condition = True  # Initialize your condition
        self.model.evaluate_current_policy = False
        self.mujoco_file_folder = f"{REPO_ROOT}/assets/mujoco/half_cheetah/"

        self.new_sizes_array = np.array([
                        [0.046, 0.145],  # bthigh
                        [0.046, 0.15],  # bshin
                        [0.046, 0.094],  # bfoot
                        [0.046, 0.133],  # fthigh
                        [0.046, 0.106],  # fshin
                        [0.046, 0.07]   # ffoot
                        ])
        # self.stiffness = [348.849528, 392.320462, 118.132672, 484.039642, 411.843929, 368.657455]
        # self.stiffness = [382.77, 208.47, 142.39, 422.33, 494.99, 156.47]
        # self.stiffness = [657.055, 598.032, 176.102, 602.802, 576.769, 420.613]
        # self.stiffness = [548.922, 312.522, 170.263, 514.539, 496.388, 145.926]
        # self.stiffness = [240.0, 180.0, 120.0, 180.0, 120.0, 60.0]
        self.stiffness = [355.057876667471, 299.820855117453, 378.324215785938, 465.081778806844, 457.768236524388, 451.796873601263]
        # self.stiffness = [306.338, 636.608, 217.815, 391.246, 224.492, 501.802]

    def _on_rollout_start(self) -> bool:

        #reset the environments
        for i in range(self.n_envs_train):

            self.stiffness = np.array([random.uniform(10, 1000) for _ in range(6)])
            self.modify_xml_stiffness(f"{self.mujoco_file_folder}half_cheetah_{i}.xml", self.stiffness)
            self.training_env.env_method('__init__', i ,indices=[i])
            self.training_env.env_method("set_stiffness", self.stiffness, indices=[i])
            self.training_env.env_method('reset', indices=[i])

            # print(self.training_env.env_method('get_stiffness', indices=[i]))
        # time.sleep(20)

        return True


    def _on_step(self) -> bool:

        if 'rewards' in self.locals:
            rewards = self.locals['rewards']
            for i, reward in enumerate(rewards):
                self.episode_rewards[i] = self.episode_rewards.get(i, 0) + reward
                self.episode_length[i] = self.episode_length.get(i, 0) + 1

        if 'dones' in self.locals:
            dones = self.locals['dones']
            for i, done in enumerate(dones):
                if done or self.episode_length[i] >= self.n_steps_train:
                    # current_stiffness = self.training_env.env_method('get_stiffness', indices=[i])[0]
                    # target_pos_tcp = self.training_env.env_method('get_target_pos_tcp', indices=[i])[0]
                    # dist_env_id = self.training_env.env_method('get_env_id', indices=[i])[0]
                    self.average_episode_length.append(self.episode_length[i])
                    self.average_reward.append(self.episode_rewards[i])
                    self.design_iteration[i] += 1
                    # Reset episode reward accumulator
                    self.episode_rewards[i] = 0
                    self.episode_length[i] = 0
        return True

    def _on_rollout_end(self) -> bool:
        self.model.save(f"{REPO_ROOT}/python/half_cheetah/rl/trained_model/random_design/{self.model_name}")
        self.logger.record("mean episode length", np.sum(self.average_episode_length) / np.sum(self.design_iteration))
        self.logger.record("mean reward", np.sum(self.average_reward) / np.sum(self.design_iteration))
        self.average_episode_length = []
        self.average_reward = []
        self.design_iteration = [0 for _ in range(self.n_envs_train)]
        # for i in range(self.n_envs_train):
        #     new_length = self.training_env.env_method('get_body_geom_sizes', indices=[i])
        #     print(new_length)
        return True

    def modify_xml_file(self, file_path, sizes_array):
        """
        Modify specified elements in a single XML file, setting their 'size' attributes based on a 2D NumPy array.

        Args:
        - file_path: Path to the XML file to modify.
        - sizes_array: 2D NumPy array containing the new size values.
        """
        # Load the XML file
        tree = ET.parse(file_path)
        root = tree.getroot()

        # Names of the elements to modify
        element_names = ['bthigh', 'bshin', 'bfoot', 'fthigh', 'fshin', 'ffoot']

        # Ensure sizes_array matches the expected dimensions
        if sizes_array.shape != (len(element_names), 2):
            raise ValueError("sizes_array must have the shape (6, 2) for six elements and two dimensions each.")

        # Apply the specified sizes to the corresponding elements
        for i, name in enumerate(element_names):
            size_str = f"{sizes_array[i][0]:.3f} {sizes_array[i][1]:.3f}"
            for geom in root.findall(f".//body[@name='{name}']/stiffness"):
                geom.set('size', size_str)
        # Save the modified XML file
        tree.write(file_path)

    def modify_xml_stiffness(self, file_path, stiffness_values):
        """
        Modify specified elements in a single XML file, setting their 'stiffness' attributes based on a sequence of values.

        Args:
        - file_path: Path to the XML file to modify.
        - stiffness_values: Sequence containing the new stiffness values.
        """
        # Load the XML file
        tree = ET.parse(file_path)
        root = tree.getroot()

        # Names of the elements to modify
        element_names = ['bthigh', 'bshin', 'bfoot', 'fthigh', 'fshin', 'ffoot']

        # Ensure stiffness_values has the correct length
        if len(stiffness_values) != len(element_names):
            raise ValueError("stiffness_values must have the same number of elements as there are to modify.")

        # Apply the specified stiffness values to the corresponding elements
        for i, name in enumerate(element_names):
            # Find the specific element by its name and modify its 'stiffness' attribute
            for joint in root.findall(f".//body[@name='{name}']/joint"):
                joint.set('stiffness', str(stiffness_values[i]))
        # Save the modified XML file
        tree.write(file_path)

class Hebo_Gauss_callback(BaseCallback):

    def __init__(self,model_name = f"matfile", model = None ,n_steps_train=512 * 10, n_envs_train=8, stiffness_limits = np.array([1.0, 5.0]), verbose=0):

        super(Hebo_Gauss_callback, self).__init__(verbose)

        self.batch_iterations = n_steps_train * n_envs_train
        self.steps_update_distribution = self.batch_iterations * 0 # Set to batch_iterations * 1 for clarity
        self.n_envs_train = n_envs_train
        self.model_name = model_name
        self.min_bound = stiffness_limits[0]
        self.max_bound = stiffness_limits[1]
        self.model = model
        self.distributions = []
        self.mat_stiffness = []
        self.mat_best_design_gauss = []
        self.mat_reward = []
        self.mat_iteration = []
        self.design_process = False  # Initialize to False
        self.mat_file_name = model_name
        self.save_recorded_data = n_steps_train * n_envs_train * 1
        self.reduce_batch_size = n_steps_train * n_envs_train * 1
        self.workspace_radius = 2.0
        self.max_joint_pos = np.array([math.pi, math.pi], dtype=np.double)
        self.min_joint_pos = np.array([-math.pi, -math.pi], dtype=np.double)

        # Initialize

        self.state = 'hebo_init' #random or gaussian or init_gaussian or hebo or init_hebo

        self.sampling_hebo_time_period = 40
        self.sampling_gauss_time_period = 10
        self.sampling_random_time_period = 0
        self.sampling_hebo_ctr = 0
        self.sampling_gauss_ctr = 0
        self.sampling_random_ctr = 0
        self.hebo_design_history = []
        self.hebo_reward_history = []
        self.percentile_top_designs = 40 # 0 to 100
        self.batch_size_hebo = 1
        self.batch_size_gauss = 1
        self.batch_size_random = 1
        self.optimal_components = 1
        self.optimal_gmm = None
        self.hebo_init_ctr = 0
        self.gauss_init_ctr = 0

        self.episode_rewards = {}
        self.episode_length = {}
        self.design_iteration = [1 for _ in range(self.n_envs_train)]
        self.design_rewards_avg = [0 for _ in range(self.n_envs_train//self.batch_size_hebo)]
        self.episode_length_avg = [0 for _ in range(self.n_envs_train//self.batch_size_hebo)]
        self.best_design = []
        self.best_design_reward = []
        self.target_pos_param = []
        self.init_joint_pos = []
        self.logger_reward = []
        self.logger_reward_prev = -1000
        self.logger_episode_length = []
        #define hebo design space based on the number of components
        self.design_space_lb = np.array([10.0, 10.0, 10.0, 10.0, 10.0, 10.0])
        self.design_space_ub = np.array([1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0])
        self.design_space_history = []
        self.best_design_gauss = np.array([1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0])
        self.best_design_reward_gauss = -1000
        # Range of possible components
        self.n_components_range = range(1, 10)
        self.sample_half_gauss = False
        self.stiffness = [100.0, 100.0, 100.0, 100.0, 100.0, 100.0]
        self.mujoco_file_folder = f"{REPO_ROOT}/assets/mujoco/half_cheetah/"
        self.column_names = ['x1', 'x2', 'x3', 'x4', 'x5', 'x6']
        self.rec_gauss_his = pd.DataFrame(columns=self.column_names)
        self.scores_gauss_his = []



        np.set_printoptions(precision=3)

    def on_training_start(self, locals_: Dict[str, Any], globals_: Dict[str, Any]) -> bool:
        print("Training started")

    def _on_rollout_start(self) -> bool:

        if self.state == "hebo_init":
            print("initialising HEBO")

            space_config = []
            self.opt = None

            for i in range(1, len(self.design_space_lb) + 1):
                space_config.append({
                    'name': f'x{i}',  # This will create 'x1', 'x2', etc.
                    'type': 'num',
                    'lb': self.design_space_lb[i-1],  # Assuming self.min_stiffness is defined
                    'ub': self.design_space_ub[i-1]   # Assuming self.max_stiffness is defined
                })
            space = DesignSpace().parse(space_config)
            self.opt = HEBO(space)
            self.hebo_init_ctr += 1
            self.state = "hebo"

        if self.state == "gauss_init":
            print("initialising gaussian mixture models")
            sorted_indices = []
            top_indices = []
            self.top_designs = []
            self.top_rewards = []
            top_designs_scaled = []
            #decrease the time period for sampling from hebo
            self.sampling_hebo_time_period -= 5
            if self.sampling_hebo_time_period <= 5:
                self.sampling_hebo_time_period = 5

            #define the gaussian mixture models based on the history of hebo
            #order top performing designs based on reward in descending order
            self.hebo_design_history = np.array(self.hebo_design_history)
            self.hebo_reward_history = np.concatenate(self.hebo_reward_history, axis=0)
            sorted_indices = np.argsort(self.hebo_reward_history)[::-1]

            #take the top percentile of the designs
            top_indices = sorted_indices[:int((self.percentile_top_designs/100) * len(sorted_indices))]

            #keep designs greater than the average reward
            avg_reward = np.mean(self.hebo_reward_history)
            # top_indices = [i for i in range(len(self.hebo_reward_history)) if self.hebo_reward_history[i] > avg_reward]

            print(f"avg reward: {avg_reward}, top indices: {len(top_indices)}")
            print(f"top desgins: {self.hebo_design_history[top_indices]}, top rewards: {self.hebo_reward_history[top_indices]}")
            self.top_designs = self.hebo_design_history[top_indices]
            self.top_rewards = self.hebo_reward_history[top_indices]
            #find the lower and upper bound of the top designs for each dimension

            self.design_space_lb = np.min(self.top_designs, axis=0)
            self.design_space_ub = np.max(self.top_designs, axis=0)

            self.design_space_history.append([self.design_space_lb, self.design_space_ub])
            print(f"Design space lower bound: {self.design_space_lb}")
            print(f"Design space upper bound: {self.design_space_ub}")
            print(f"Design space history: {self.design_space_history}")
            #scale self.top_designs to the design space bounded by lb and ub
            top_designs_scaled = (self.top_designs - self.design_space_lb)/(self.design_space_ub - self.design_space_lb)
            #normalise top rewards
            top_rewards_norm = (self.top_rewards - np.min(self.top_rewards))/(np.max(self.top_rewards) - np.min(self.top_rewards))

            bic_scores = []
            aic_scores = []

            # Fit GMMs with different number of components
            for n_components in self.n_components_range:

                gmm = GaussianMixture(n_components=n_components, random_state=42,
                              covariance_type='full', init_params='kmeans',
                              max_iter=100, n_init=20)
                #fit until convergence
                gmm.fit(top_designs_scaled, top_rewards_norm)
                print(f"gmm {n_components} converged: {gmm.converged_}, with iterations: {gmm.n_iter_}")

                # gmm.fit(top_designs_scaled)
                bic_scores.append(gmm.bic(top_designs_scaled))
                aic_scores.append(gmm.aic(top_designs_scaled))

                # Choosing the optimal number of components
                self.optimal_components = np.argmin(bic_scores) + 1  # +1 because range starts from 1
                print(f"Optimal number of components according to BIC: {self.optimal_components}")

            # Fit GMM with the optimal number of components
            self.optimal_gmm = GaussianMixture(n_components=self.optimal_components, random_state=42,
                                        covariance_type='full', init_params='kmeans',
                                        max_iter=100, n_init=20)

            #fit gaussian mixture models
            self.optimal_gmm.fit(top_designs_scaled, top_rewards_norm)

            print(f"GMM means: {self.optimal_gmm.means_}")
            print(f"GMM covariances: {self.optimal_gmm.covariances_}")
            print(f"GMM means orignal scale: {self.optimal_gmm.means_ * (self.design_space_ub - self.design_space_lb) + self.design_space_lb}")

            self.hebo_design_history = []
            self.hebo_reward_history = []

            # design_plot = self.optimal_gmm.sample(400)
            # clusters = self.optimal_gmm.predict(design_plot[0])

            # design_plot_ds = design_plot[0] * (self.design_space_ub - self.design_space_lb) + self.design_space_lb
            # # Plotting the clusters in 3D
            # fig = plt.figure(figsize=(10, 8))
            # ax = fig.add_subplot(111, projection='3d')
            # scatter = ax.scatter(design_plot_ds[:, 0], design_plot_ds[:, 1], design_plot_ds[:, 2], c=clusters, cmap='viridis', marker='o')
            # legend1 = ax.legend(*scatter.legend_elements(), loc="upper right", title="Clusters")
            # ax.add_artist(legend1)
            # ax.set_title("Gaussian Mixture Model Clustering on Complex 3D Data")
            # ax.set_xlabel("X axis")
            # ax.set_ylabel("Y axis")
            # ax.set_zlabel("Z axis")
            # ax.set_xlim(0.1, 2.0)
            # ax.set_ylim(0.1, 2.0)
            # ax.set_zlim(0.1, 2.0)
            # plt.show()

            self.gauss_init_ctr += 1

            self.state = "gauss"

        if self.state == "hebo":

            #turn off train when sampling from hebo
            self.model.evaluate_current_policy = True
            print("...Updating the new lengths...")
            start_time = time.time()

            if not self.sample_half_gauss:
                #sample from hebos
                self.rec = self.opt.suggest(n_suggestions=(self.n_envs_train // self.batch_size_hebo))
            else:
                #sample half from hebos
                self.rec = self.opt.suggest(n_suggestions=(self.n_envs_train // (self.batch_size_hebo*2)))
                # #sample half from gaussian mixture models
                # gauss_output_scaled = self.optimal_gmm.sample(self.n_envs_train // (self.batch_size_hebo*2))

                # #scale the sampled designs to the design space bounded by lb and ub
                # gauss_output = gauss_output_scaled[0] * (self.design_space_ub - self.design_space_lb) + self.design_space_lb
                # gauss_output = np.clip(gauss_output, self.design_space_lb, self.design_space_ub)

                # # Convert gauss_output[0] to a DataFrame with the same column names
                # gauss_output_df = pd.DataFrame(gauss_output, columns=self.column_names)

                prev_top_designs = pd.DataFrame(self.top_designs[:int(self.n_envs_train // (self.batch_size_hebo*2))], columns=self.column_names)

                # Now concatenate the DataFrames
                self.rec = pd.concat([self.rec, prev_top_designs], ignore_index=True)
                print("first hebo", self.rec)
                self.sample_half_gauss = False

            for i in range(self.n_envs_train//self.batch_size_hebo):
                for j in range(self.batch_size_hebo):
                    self.stiffness = self.rec.values[i]
                    self.modify_xml_stiffness(f"{self.mujoco_file_folder}half_cheetah_{i}.xml", self.stiffness)
                    self.training_env.env_method('__init__', i ,indices=[i*self.batch_size_hebo + j])
                    self.training_env.env_method('reset', indices=[i*self.batch_size_hebo + j])
                    self.training_env.env_method('set_stiffness', self.stiffness, indices=[i*self.batch_size_hebo + j])

                    #reset the environment
                    self.training_env.env_method('reset', indices=[i*self.batch_size_hebo + j])
                    dist_env_id = self.training_env.env_method('get_env_id', indices=[i*self.batch_size_hebo + j])[0]
                    current_stiffness = self.training_env.env_method('get_stiffness', indices=[i*self.batch_size_hebo + j])[0]
                    # print(f"env: {i*self.batch_size_hebo + j:<1.2f}, real id:{dist_env_id}, stiffness: {self.stiffness}")

            print(f"Design proposal took {time.time() - start_time:.2f} seconds")
            self.sampling_hebo_ctr += 1

        if self.state == "gauss":

            #turn on train when sampling from gaussian mixture models
            self.model.evaluate_current_policy = False

            #sample from gaussian mixture models
            self.gauss_output = self.optimal_gmm.sample(self.n_envs_train//self.batch_size_gauss)
            self.gauss_designs = self.gauss_output[0]

            #scale the sampled designs to the design space bounded by lb and ub
            self.gauss_designs = self.gauss_designs * (self.design_space_ub - self.design_space_lb) + self.design_space_lb
            self.gauss_designs = np.clip(self.gauss_designs, self.design_space_lb, self.design_space_ub)
            #sample from gaussian mixture models and set the designs in the environments
            for i in range(self.n_envs_train//self.batch_size_gauss):
                for j in range(self.batch_size_gauss):
                    self.modify_xml_stiffness(f"{self.mujoco_file_folder}half_cheetah_{i}.xml", self.gauss_designs[i])
                    self.training_env.env_method('__init__', i ,indices=[i*self.batch_size_gauss + j])
                    self.training_env.env_method('reset', indices=[i*self.batch_size_gauss + j])
                    self.training_env.env_method('set_stiffness', self.gauss_designs[i], indices=[i*self.batch_size_gauss + j])

            self.sampling_gauss_ctr += 1
            self.sample_half_gauss = True

        return True

    def _on_rollout_end(self) -> bool:


        if self.state == "hebo":
            print("...Starting design distribution update...")

            start_time = time.time()

            scores = []

            self.design_rewards_avg = [0 for _ in range(self.n_envs_train//self.batch_size_hebo)]
            self.episode_length_avg = [0 for _ in range(self.n_envs_train//self.batch_size_hebo)]

            for i in range(self.n_envs_train//self.batch_size_hebo):
                #average batch reward
                sum_reward = 0
                total_episode_length = 0
                for j in range(self.batch_size_hebo):
                    sum_reward += self.episode_rewards[i*self.batch_size_hebo + j]/self.design_iteration[i*self.batch_size_hebo + j]
                    total_episode_length += self.episode_length[i*self.batch_size_hebo + j]/self.design_iteration[i*self.batch_size_hebo + j]

                self.design_rewards_avg[i] = sum_reward/self.batch_size_hebo
                self.episode_length_avg[i] = total_episode_length/self.batch_size_hebo
                score_array = np.array(self.design_rewards_avg[i]).reshape(-1, 1)  # Convert to NumPy array
                scores.append(-score_array) # HEBO minimizes, so we need to negate the scores

                # Logging
                current_stiffness = self.training_env.env_method('get_stiffness', indices=[i*self.batch_size_hebo])[0]
                dist_env_id = self.training_env.env_method('get_env_id', indices=[i*self.batch_size_hebo])[0]
                # print(f"Env ID: {dist_env_id}, mean reward: {self.design_rewards_avg[i]}, Mean episode length: {self.episode_length_avg[i]}, arm length: {current_stiffness}")
                self.logger.record("mean reward", self.design_rewards_avg[i])
                self.logger.record("mean episode length", self.episode_length_avg[i])

                # Matlab logging
                self.mat_stiffness.append(current_stiffness)
                self.mat_reward.append(self.design_rewards_avg[i])
                self.mat_iteration.append(self.episode_length_avg[i])

                self.logger_reward.append(self.design_rewards_avg[i])
                self.logger_episode_length.append(self.episode_length_avg[i])

            # Logging
            self.logger.record("mean reward", np.mean(self.logger_reward))
            self.logger.record("mean episode length", np.mean(self.logger_episode_length))
            self.logger_reward = []
            self.logger_episode_length = []

            scores = np.array(scores)  # Make sure the outer list is also a NumPy array
            #save history of design and reward proposed by hebo
            self.hebo_design_history.extend(self.rec.values.tolist())
            self.hebo_reward_history.extend(np.concatenate(-scores).tolist())

            # Update the design distribution
            scores = scores.reshape(-1, 1)
            self.opt.observe(self.rec, scores)

            # #check if self.rec_gauss_his is empty
            # if len(self.scores_gauss_his) > 0:
            #     self.scores_gauss_his = np.array(self.scores_gauss_his).reshape(-1, 1)
            #     self.opt.observe(self.rec_gauss_his, self.scores_gauss_his)
            #     self.rec_gauss_his = pd.DataFrame(columns=self.column_names)
            #     self.scores_gauss_his = []

            # After all iterations, print the best input and output
            best_idx = self.opt.y.argmin()
            best_design = self.opt.X.iloc[best_idx]
            best_design_reward = self.opt.y[best_idx]

            print(f"Best design: {best_design}, best reward: {best_design_reward}")
            self.best_design.append(best_design)
            self.best_design_reward.append(best_design_reward)

            print(f"Design distribution update took {time.time() - start_time:.2f} seconds")


            # Reset episode reward accumulator
            self.design_rewards_avg = [0 for _ in range(self.n_envs_train)]
            self.design_iteration = [1 for _ in range(self.n_envs_train)]
            self.episode_rewards = {}
            self.episode_length = {}

        if self.state == "gauss":
            #calculate the reward for the sampled designs
            self.design_rewards_avg = [0 for _ in range(self.n_envs_train//self.batch_size_gauss)]
            self.episode_length_avg = [0 for _ in range(self.n_envs_train//self.batch_size_gauss)]

            for i in range(self.n_envs_train//self.batch_size_gauss):
                #average batch reward
                sum_reward = 0
                total_episode_length = 0
                for j in range(self.batch_size_gauss):
                    sum_reward += self.episode_rewards[i*self.batch_size_gauss + j]/self.design_iteration[i*self.batch_size_gauss + j]
                    total_episode_length += self.episode_length[i*self.batch_size_gauss + j]/self.design_iteration[i*self.batch_size_gauss + j]

                self.design_rewards_avg[i] = sum_reward/self.batch_size_gauss
                self.episode_length_avg[i] = total_episode_length/self.batch_size_gauss
                self.logger_reward.append(self.design_rewards_avg[i])
                self.logger_episode_length.append(self.episode_length_avg[i])
                current_stiffness = self.training_env.env_method('get_stiffness', indices=[i*self.batch_size_gauss])[0]
                dist_env_id = self.training_env.env_method('get_env_id', indices=[i*self.batch_size_gauss])[0]
                # print(f"Env ID: {dist_env_id}, mean reward: {self.design_rewards_avg[i]}, Mean episode length: {self.episode_length_avg[i]}, arm length: {current_stiffness}")

                # # append current_stiffness in DataFrame with the same column names
                # current_stiffness_reshaped = current_stiffness.reshape(1, -1)  # Reshapes to (1, 6)
                # # Append current_stiffness as a new row in DataFrame with the correct column names
                # self.rec_gauss_his = pd.concat([self.rec_gauss_his, pd.DataFrame(current_stiffness_reshaped, columns=self.column_names)], ignore_index=True)
                # self.scores_gauss_his.append(-self.design_rewards_avg[i])

                #find the best design
                if self.design_rewards_avg[i] > self.best_design_reward_gauss:
                    self.best_design_reward_gauss = self.design_rewards_avg[i]
                    self.best_design_gauss = current_stiffness
                    self.mat_best_design_gauss.append(current_stiffness)
                    self.model.save(f"{REPO_ROOT}/python/half_cheetah/rl/trained_model/bestDesign_{self.model_name}")


            # Logging
            self.logger.record("mean reward", np.mean(self.logger_reward))
            self.logger.record("mean episode length", np.mean(self.logger_episode_length))
            self.logger_reward = []
            self.logger_episode_length = []

            #save the best model
            # if np.mean(self.design_rewards_avg) >= self.logger_reward_prev:
                # self.logger_reward_prev = np.mean(self.design_rewards_avg)
            self.model.save(f"{REPO_ROOT}/python/half_cheetah/rl/trained_model/{self.model_name}")
                # print(f"Model saved, reward: {self.logger_reward_prev}, iteration: {self.gauss_init_ctr}, best design: {self.best_design_gauss}")

            # Reset episode reward accumulator
            self.design_rewards_avg = [0 for _ in range(self.n_envs_train)]
            self.design_iteration = [1 for _ in range(self.n_envs_train)]
            self.episode_rewards = {}
            self.episode_length = {}

        output_data = {
            "stiffness": np.array(self.mat_stiffness),
            "reward": np.array(self.mat_reward),
            "iteration": np.array(self.mat_iteration),
            "best_design": np.array(self.mat_best_design_gauss)
        }
        print("saving matlab data...")
        file_path = f"{REPO_ROOT}/half_cheetah/{self.mat_file_name}.mat"
        savemat(file_path, output_data)

        if self.sampling_hebo_ctr >= self.sampling_hebo_time_period:
            self.state = "gauss_init"
            self.sampling_hebo_ctr = 0

        elif self.sampling_gauss_ctr >= self.sampling_gauss_time_period:
            self.state = "hebo_init"
            self.sampling_gauss_ctr = 0

        return True

    def _on_step(self) -> bool:

        if 'rewards' in self.locals:
            rewards = self.locals['rewards']
            for i, reward in enumerate(rewards):
                self.episode_rewards[i] = self.episode_rewards.get(i, 0) + reward
                self.episode_length[i] = self.episode_length.get(i, 0) + 1

        if 'dones' in self.locals:
            dones = self.locals['dones']
            for i, done in enumerate(dones):
                if done:
                    self.design_iteration[i] += 1
        return True

    def modify_xml_stiffness(self, file_path, stiffness_values):
        """
        Modify specified elements in a single XML file, setting their 'stiffness' attributes based on a sequence of values.

        Args:
        - file_path: Path to the XML file to modify.
        - stiffness_values: Sequence containing the new stiffness values.
        """
        # Load the XML file
        tree = ET.parse(file_path)
        root = tree.getroot()

        # Names of the elements to modify
        element_names = ['bthigh', 'bshin', 'bfoot', 'fthigh', 'fshin', 'ffoot']

        # Ensure stiffness_values has the correct length
        if len(stiffness_values) != len(element_names):
            raise ValueError("stiffness_values must have the same number of elements as there are to modify.")

        # Apply the specified stiffness values to the corresponding elements
        for i, name in enumerate(element_names):
            # Find the specific element by its name and modify its 'stiffness' attribute
            for joint in root.findall(f".//body[@name='{name}']/joint"):
                joint.set('stiffness', str(stiffness_values[i]))
        # Save the modified XML file
        tree.write(file_path)


if __name__ == '__main__':
    main()