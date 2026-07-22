from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[3]

import time
from stable_baselines3.common.callbacks import BaseCallback
from stable_baselines3 import PPO
from stable_baselines3.common.env_util import make_vec_env

from env_cartpole import CartPoleEnv
from stable_baselines3.common.vec_env import SubprocVecEnv
from stable_baselines3.common.callbacks import BaseCallback
import torch
import numpy as np
from gaussMix_design_opt import DesignDistribution_log as DesignDistribution
import time
from hebo.design_space.design_space import DesignSpace
from hebo.optimizers.hebo import HEBO
from scipy.io import loadmat, savemat
import argparse
import pandas as pd
from typing import Any, Dict
import math as m
# for hebo training avoid using batch greater than 1
def main():
    #training parameters
    save_path = f"{REPO_ROOT}/python/cart_pole/rl/trained_model/schaff_chop/"
    parser = argparse.ArgumentParser()
    parser.add_argument('--pole_length', type=float, default=2.0, help='Length of the pole')
    args = parser.parse_args()

    pole_length = 0.5
    freq = 1
    hidden_sizes_train = 256
    REWARD = np.array([1.0, 0.2, 0.05])
    learning_rate_train = 0.00005
    n_epochs_train = 10
    LOAD_OLD_MODEL = False
    n_steps_train = 512 * 10
    n_envs_train = 20  # 508 Maximum number of environments to train, 104 used for radom design
    entropy_coeff_train = 0.0
    total_timesteps_train = n_steps_train * n_envs_train * 100
    batch_size_train = 512
    global_iteration = 0
    num_distributions = 4   # Number of distributions to use for design optimization
    CALL_BACK_FUNC = f"constant_design"
    while True:
        #initialise the model PPO
        learning_rate_train = learning_rate_train
        onpolicy_kwargs = dict(activation_fn=torch.nn.Tanh,
                                net_arch=dict(vf=[hidden_sizes_train, hidden_sizes_train], pi=[hidden_sizes_train, hidden_sizes_train])
                                )

        global_iteration += 1

        # Define unique initialization variables for each environment
        env_configs = [{'REWARD': REWARD, 'env_id': i , 'pole_length': pole_length,'freq': freq,'call_back': CALL_BACK_FUNC} for i in range(n_envs_train)]

        # Ensure we have configurations for each environment instance
        assert len(env_configs) == n_envs_train

        # Create function for each environment instance with its unique configuration
        env_fns = [lambda config=config: CartPoleEnv(**config) for config in env_configs]

        # Create the vectorized environment using SubprocVecEnv directly
        vec_env = SubprocVecEnv(env_fns, start_method='fork')

        model_name = f"CartPole_{CALL_BACK_FUNC}_Tanh_Tsteps_{total_timesteps_train}_lr_{learning_rate_train}_hidden_sizes_{hidden_sizes_train}_reward_{REWARD[0]}{REWARD[1]}{REWARD[2]}_pole_length_{pole_length}_freq_{freq}_schaff_lr0.1"
        log_dir = f"{REPO_ROOT}/python/cart_pole/cartpole_tensorboard/TB_{model_name}"

        if LOAD_OLD_MODEL is True:
            new_model = []
            old_model = PPO.load(f"{REPO_ROOT}/python/cart_pole/rl/trained_model/random_dist/new/CartPole_random_design_Tanh_Tsteps_51200000_lr_5e-05_hidden_sizes_256_reward_1.00.20.1_freq_1", env = vec_env)
            # Create a new model with the desired configuration
            new_model = PPO("MlpPolicy", env=vec_env, n_steps=n_steps_train,
                            batch_size=batch_size_train, n_epochs=n_epochs_train,
                            ent_coef=entropy_coeff_train,
                            learning_rate=learning_rate_train, policy_kwargs=onpolicy_kwargs,
                            device='cpu', verbose=1, tensorboard_log=log_dir)

            # Load the weights from the old model
            new_model.set_parameters(old_model.get_parameters())

        else:
            new_model = PPO("MlpPolicy", env = vec_env, n_steps = n_steps_train, batch_size = batch_size_train,
                n_epochs=n_epochs_train, ent_coef = entropy_coeff_train, learning_rate = learning_rate_train,
                policy_kwargs=onpolicy_kwargs, device ='cpu',verbose=1, tensorboard_log=log_dir)
            print("New model created")

        # Train the new model
        print("Model training...")
        # Now you can continue training with the new model
        if CALL_BACK_FUNC == "Hebo_callback":
            param_changer = Hebo_callback(model_name = model_name, n_steps_train = n_steps_train, n_envs_train = n_envs_train, save_path=save_path ,verbose=1)

        elif CALL_BACK_FUNC == "Schaff_callback":
            param_changer = Schaff_callback(model_name = model_name,n_steps_train = n_steps_train, n_envs_train = n_envs_train,num_distributions=num_distributions, save_path=save_path ,verbose=1)

        elif CALL_BACK_FUNC == "random_design":
            param_changer = random_design(model_name = model_name,n_steps_train = n_steps_train, n_envs_train = n_envs_train ,verbose=1)

        elif CALL_BACK_FUNC == "constant_design":
            param_changer = constant_design(model_name = model_name,n_steps_train = n_steps_train, n_envs_train = n_envs_train, save_path=save_path ,verbose=1)

        new_model.learn(total_timesteps = total_timesteps_train ,progress_bar=True, callback=param_changer)

        print("Model trained, saving...")
        new_model.save(f"{save_path}/{model_name}")

        print("Model saved")

        vec_env.close()

        if CALL_BACK_FUNC == "constant_design":
            pole_length = pole_length + 0.5
            if pole_length > 10:
                break
        else:
            break

class constant_design(BaseCallback):
    def __init__(self, model_name = f"matfile" ,n_steps_train=512 * 10, n_envs_train=8, save_path=None ,verbose=0):

        super(constant_design, self).__init__(verbose)
        self.n_envs_train = n_envs_train
        self.n_steps_train = n_steps_train
        self.model_name = model_name
        self.save_path = save_path
        self.episode_rewards = {}
        self.rewards_iteration = {}
        self.reward_accumulator = [[] for _ in range(self.n_envs_train)]
        self.best_reward = 0
        self.episode_length = {}
        self.mat_pole_length = []
        self.mat_reward = []
        self.mat_episode_length = []
        self.average_reward = []
        self.average_episode_length = []
        self.init_pos = np.linspace(-m.pi+0.001, m.pi-0.001, self.n_envs_train).tolist()
        self.model_name = model_name

    def _on_rollout_start(self) -> bool:
        #reset the environments
        for i in range(self.n_envs_train):
            self.training_env.env_method('reset', indices=[i])
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
                    current_arm_length = self.training_env.env_method('get_pole_length', indices=[i])[0]
                    dist_env_id = self.training_env.env_method('get_env_id', indices=[i])[0]
                    self.average_episode_length.append(self.episode_length[i])
                    self.average_reward.append(self.episode_rewards[i])

                    # Reset episode reward accumulator
                    self.episode_rewards[i] = 0
                    self.episode_length[i] = 0
        return True

    def _on_rollout_end(self) -> bool:
        print(f"Mean reward: {np.mean(self.average_reward)}, Mean episode length: {np.mean(self.average_episode_length)}, length: {np.shape(self.average_reward)}, length: {np.shape(self.average_episode_length)}")
        self.logger.record("mean reward", np.mean(self.average_reward))
        self.logger.record("mean episode length", np.mean(self.average_episode_length))

        self.average_episode_length = []
        self.average_reward = []
        self.model.save(f"{REPO_ROOT}/python/cart_pole/rl/trained_model/constant_mass/{self.model_name}")
        return True

class random_design(BaseCallback):
    def __init__(self,model_name = f"matfile" ,n_steps_train=512 * 10, n_envs_train=8, verbose=0):

        super(random_design, self).__init__(verbose)
        self.n_envs_train = n_envs_train
        self.n_steps_train = n_steps_train
        self.episode_rewards = {}
        self.rewards_iteration = {}
        self.design_iteration = [1 for _ in range(self.n_envs_train)]
        self.design_rewards = [0 for _ in range(self.n_envs_train)]
        self.episode_length = {}
        self.mat_pole_length = []
        self.mat_reward = []
        self.mat_episode_length = []
        self.average_reward = []
        self.average_episode_length = []
        self.model_name = model_name

    def _on_rollout_start(self) -> bool:
        #reset the environments
        for i in range(self.n_envs_train):
            self.training_env.env_method('reset', indices=[i])
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
                    current_arm_length = self.training_env.env_method('get_pole_length', indices=[i])[0]
                    dist_env_id = self.training_env.env_method('get_env_id', indices=[i])[0]
                    self.average_episode_length.append(self.episode_length[i])
                    self.average_reward.append(self.episode_rewards[i])
                    # print("env id", dist_env_id ,"arm length: ",current_arm_length, "ep len:", self.episode_length[i], "rew", self.episode_rewards[i])
                    # Reset episode reward accumulator
                    self.episode_rewards[i] = 0
                    self.episode_length[i] = 0
        return True

    def _on_rollout_end(self) -> bool:
        print(f"Mean reward: {np.mean(self.average_reward)}, Mean episode length: {np.mean(self.average_episode_length)}, length: {np.shape(self.average_reward)}, length: {np.shape(self.average_episode_length)}")
        self.logger.record("mean reward", np.mean(self.average_reward))
        self.logger.record("mean episode length", np.mean(self.average_episode_length))

        self.average_episode_length = []
        self.average_reward = []
        self.model.save(f"{REPO_ROOT}/python/cart_pole/rl/trained_model/random_dist/{self.model_name}")
        return True

class Schaff_callback(BaseCallback):
    def __init__(self,model_name = f"matfile" ,n_steps_train=512 * 10, n_envs_train=8, num_distributions = 8,save_path = None ,verbose=0):

        super(Schaff_callback, self).__init__(verbose)
        self.num_distributions = num_distributions
        self.num_envs = n_envs_train
        self.Schaffs_batch_size = 10
        self.episode_rewards = {}
        self.rewards_iteration = {}
        self.episode_length = {}
        self.design_rewards_avg = [0 for _ in range(self.num_envs)]
        self.design_iteration = [1 for _ in range(self.num_envs)]
        self.design_rewards_avg = [0 for _ in range(self.num_envs//self.Schaffs_batch_size)]
        self.episode_length_avg = [0 for _ in range(self.num_envs//self.Schaffs_batch_size)]
        self.avg_design_iteration = [0 for _ in range(self.num_envs//self.Schaffs_batch_size)]
        self.episode_rewards = {}
        self.episode_length = {}
        self.model_name = model_name
        self.mat_file_name = model_name
        self.save_path = save_path

        # Initialize the distributions

        self.distributions = []
        self.min_pole_length = [0.5]
        self.max_pole_length = [10]
        self.n_steps_train = n_steps_train
        self.steps_update_distribution = n_steps_train * n_envs_train * 0
        self.steps_chop_distribution = n_steps_train * n_envs_train * 10
        np.set_printoptions(precision=2)

        #initializ matlab data
        self.mat_dist_mean = [[] for _ in range(self.num_distributions)]
        self.mat_dist_std = [[] for _ in range(self.num_distributions)]
        self.mat_pole_length = [[] for _ in range(self.num_distributions)]
        self.mat_reward = [[] for _ in range(self.num_distributions)]
        self.mat_episode_length = [[] for _ in range(self.num_distributions)]
        self.mat_iter = 0
        self.accumulated_rewards_chopping_metric = [[] for _ in range(self.num_distributions)]

        self.start_chopping = False
        self.start_sampling_distributions = False
        self.iteration_matlab = 0
        self.init_pos = []

        # Initialize
        mean = np.linspace(self.min_pole_length[0], self.max_pole_length[0], self.num_distributions + 2)[1:-1]

        for _ in range(self.num_distributions):
            # self.initial_mean = np.array([min_val + (max_val - min_val) * np.random.rand()
            #                         for min_val, max_val in zip(self.min_pole_length, self.max_pole_length)])
            self.initial_mean = np.array([mean[_]])
            self.initial_std = np.ones(1, dtype=np.float32) * 3  # Initialize std deviation as you prefer
            # self.initial_std = self.uniform_distribution_variance(mean[0], mean[1])
            self.design_dist = DesignDistribution(self.initial_mean, self.initial_std, min_parameters = self.min_pole_length, max_parameters = self.max_pole_length)
            print(self.initial_mean, self.initial_std ,self.design_dist.get_mean(), self.design_dist.get_std())
            self.distributions.append(self.design_dist)

    def uniform_distribution_variance(self, a, b):
        """
        Calculate the variance and standard deviation of a uniform distribution
        with bounds a and b.
        """
        variance = ((b - a) ** 2) / 12
        std_dev = (variance ** 0.5)

        return std_dev

    def on_training_start(self, locals_: Dict[str, Any], globals_: Dict[str, Any]) -> bool:
        print("Training started")
        #set the environment id for each environment
        for i in range(self.num_envs):
            self.training_env.env_method('set_env_id', i//(self.num_envs//self.num_distributions), indices=[i])

        # print(f"Env IDs: {[self.training_env.env_method('get_env_id', indices=[i])[0] for i in range(self.num_envs)]}")

        self.init_pole_pos = np.linspace(-m.pi+0.001, m.pi-0.001, self.Schaffs_batch_size).tolist()

        return True


    def _on_rollout_start(self) -> bool:

        #reset the environments
        for i in range(self.num_envs):
            self.training_env.env_method('reset', indices=[i])

        #set the sampled pole length for each batch
        for i in range(self.num_envs//self.Schaffs_batch_size):
            self.training_env.env_method('set_pole_length', self.distributions[i//(self.num_envs//(self.Schaffs_batch_size*self.num_distributions))].sample_design().detach().item(), indices=[i*self.Schaffs_batch_size + j for j in range(self.Schaffs_batch_size)])


        for i in range(self.num_envs//self.Schaffs_batch_size):
            for j in range(self.Schaffs_batch_size):
                self.training_env.env_method('set_init_pole_pos', self.init_pole_pos[j], indices=[i*self.Schaffs_batch_size + j])
                self.training_env.env_method('reset', indices=[i*self.Schaffs_batch_size + j])
                dist_env_id = self.training_env.env_method('get_env_id', indices=[i*self.Schaffs_batch_size + j])[0]
                init_pos = self.training_env.env_method('get_init_pole_pos', indices=[i*self.Schaffs_batch_size + j])[0]
                new_pole_length = self.training_env.env_method('get_pole_length', indices=[i*self.Schaffs_batch_size + j])[0]
                # print(f"env id: {dist_env_id}, init pos: {init_pos}, pole length: {new_pole_length}, mean: {self.distributions[i//(self.num_envs//(self.Schaffs_batch_size*self.num_distributions))].get_mean()[0]}, std: {self.distributions[i//(self.num_envs//(self.Schaffs_batch_size*self.num_distributions))].get_std()[0]}")
        return True

    def _on_rollout_end(self) -> bool:


        #calulate the mean reward for each unique design (pole length)

        self.design_rewards_avg = [0 for _ in range(self.num_envs//self.Schaffs_batch_size)]
        self.episode_length_avg = [0 for _ in range(self.num_envs//self.Schaffs_batch_size)]
        for i in range(self.num_envs//self.Schaffs_batch_size):
            #average batch reward
            sum_reward = 0
            total_episode_length = 0
            total_design_iteration = 0
            for j in range(self.Schaffs_batch_size):
                sum_reward += self.episode_rewards[i*self.Schaffs_batch_size + j]/self.design_iteration[i*self.Schaffs_batch_size + j]
                total_episode_length += self.episode_length[i*self.Schaffs_batch_size + j]/self.design_iteration[i*self.Schaffs_batch_size + j]
                total_design_iteration += self.design_iteration[i*self.Schaffs_batch_size + j]
            self.design_rewards_avg[i] = sum_reward/self.Schaffs_batch_size
            self.episode_length_avg[i] = total_episode_length/self.Schaffs_batch_size
            self.avg_design_iteration[i] = total_design_iteration/self.Schaffs_batch_size

        #update the design distribution based on the mean reward

        for i in range(self.num_envs//self.Schaffs_batch_size):
            current_pole_length = self.training_env.env_method('get_pole_length', indices=[i*self.Schaffs_batch_size])[0]
            self.distributions[i//(self.num_envs//(self.Schaffs_batch_size*self.num_distributions))].update_distribution([torch.tensor(self.design_rewards_avg[i], dtype=torch.float32)], [current_pole_length])
            self.mat_dist_mean[i//(self.num_envs//(self.Schaffs_batch_size*self.num_distributions))].append(self.distributions[i//(self.num_envs//(self.Schaffs_batch_size*self.num_distributions))].get_mean()[0])
            self.mat_dist_std[i//(self.num_envs//(self.Schaffs_batch_size*self.num_distributions))].append(self.distributions[i//(self.num_envs//(self.Schaffs_batch_size*self.num_distributions))].get_std())
            self.mat_pole_length[i//(self.num_envs//(self.Schaffs_batch_size*self.num_distributions))].append(current_pole_length)
            self.mat_reward[i//(self.num_envs//(self.Schaffs_batch_size*self.num_distributions))].append(self.design_rewards_avg[i])
            self.mat_episode_length[i//(self.num_envs//(self.Schaffs_batch_size*self.num_distributions))].append(self.episode_length_avg[i])
            self.accumulated_rewards_chopping_metric[i//(self.num_envs//(self.Schaffs_batch_size*self.num_distributions))].append(self.design_rewards_avg[i])
            print(f"env: {i*self.Schaffs_batch_size:<1.2f}, pole length: {current_pole_length}, mean reward: {self.design_rewards_avg[i]:<1.2f}, mean episode length: {self.episode_length_avg[i]:<1.2f}, design iteration: {self.avg_design_iteration[i]}, dist mean: {self.distributions[i//(self.num_envs//(self.Schaffs_batch_size*self.num_distributions))].get_mean(), self.distributions[i//(self.num_envs//(self.Schaffs_batch_size*self.num_distributions))].get_std()}")

        output_data = {
            "dist_mean": np.array(self.mat_dist_mean),
            "dist_std": np.array(self.mat_dist_std),
            "pole_length": np.array(self.mat_pole_length),
            "reward": np.array(self.mat_reward),
            "iteration": np.array(self.mat_episode_length)
        }

        print("saving matlab data...")
        file_path = f"{self.save_path}/{self.mat_file_name}_{self.iteration_matlab}_num_dist_{self.num_distributions}.mat"
        savemat(file_path, output_data)
        print("saving current model...")
        self.model.save(f"{self.save_path}/{self.model_name}_num_dist_{self.num_distributions}")

        print("model amd matlab data saved")

        #chop low performing distributions
        if self.num_timesteps % self.steps_chop_distribution == 0:

            if len(self.distributions) > 1:
                print("...Starting to chop distributions...")
                print("Updating design distribution...")
                # Step 1: Calculate mean rewards for each distribution
                print(f"Mean rewards: {self.accumulated_rewards_chopping_metric}")
                mean_rewards = [np.mean(self.accumulated_rewards_chopping_metric[i]) for i in range(len(self.accumulated_rewards_chopping_metric))]

                # Step 2: Sort the distributions by mean rewards and take the top half
                sorted_indices = np.argsort(mean_rewards)[::-1]  # Sort in descending order
                top_indices = sorted_indices[:len(sorted_indices) // 2]  # Take the top half
                print(f"Top indices: {top_indices}, mean rewards: {mean_rewards}, sorted indices: {sorted_indices}")


                print(f"Kept {len(top_indices)} top-performing distributions.")
                print(f"New distribution means: {[self.distributions[i].get_mean() for i in range(len(self.distributions))]}")
                print(f"New distribution stds: {[self.distributions[i].get_std() for i in range(len(self.distributions))]}")
                print(f"New ditribution env IDs: {[self.training_env.env_method('get_env_id', indices=[i])[0] for i in range(self.num_envs)]}")
                print(f"New distribution mean rewards: {[np.mean(self.accumulated_rewards_chopping_metric[i]) for i in range(len(self.accumulated_rewards_chopping_metric))]}")


                # Step 3: Keep only the top-performing distributions
                self.num_distributions = len(top_indices)
                self.accumulated_rewards_chopping_metric = [[] for _ in range(self.num_distributions)]
                self.distributions = [self.distributions[i] for i in top_indices]

                # Logging
                self.mat_dist_mean = [self.mat_dist_mean[i] for i in top_indices]
                self.mat_dist_std = [self.mat_dist_std[i] for i in top_indices]
                self.mat_pole_length = [self.mat_pole_length[i] for i in top_indices]
                self.mat_reward = [self.mat_reward[i] for i in top_indices]
                self.mat_episode_length = [self.mat_episode_length[i] for i in top_indices]

                # Step 4: Set the new distributions for each environment id
                # Number of distributions left
                for i in range(self.num_envs):
                    self.training_env.env_method('set_env_id', i//(self.num_envs//self.num_distributions), indices=[i])

                self.start_chopping = False

        # Reset episode reward accumulator
        self.design_iteration = [1 for _ in range(self.num_envs)]
        self.episode_rewards = {}
        self.episode_length = {}

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

class Hebo_callback(BaseCallback):

    def __init__(self,model_name = f"matfile" ,n_steps_train=512 * 10, n_envs_train=8, save_path=None, verbose=0):

        super(Hebo_callback, self).__init__(verbose)

        self.batch_iterations = n_steps_train * n_envs_train
        self.steps_update_distribution = self.batch_iterations * 0 # Set to batch_iterations * 1 for clarity
        self.n_envs_train = n_envs_train
        self.model_name = model_name

        self.save_path = save_path
        self.distributions = []
        self.mat_pole_length = []
        self.mat_reward = []
        self.mat_episode_length = []
        self.state = 'propose_design'
        self.design_process = False  # Initialize to False
        self.mat_file_name = model_name
        self.save_recorded_data = n_steps_train * n_envs_train * 1
        self.reduce_batch_size = n_steps_train * n_envs_train * 10
        self.batch_size_opt = 20
        self.init_pos = []
        # Initialize
        self.episode_rewards = {}
        self.episode_length = {}
        self.design_iteration = [1 for _ in range(self.n_envs_train)]
        self.design_rewards_avg = [0 for _ in range(self.n_envs_train//self.batch_size_opt)]
        self.episode_length_avg = [0 for _ in range(self.n_envs_train//self.batch_size_opt)]
        self.best_design = []
        self.best_design_reward = []

        np.set_printoptions(precision=3)

        space = DesignSpace().parse([
            {'name': 'x1', 'type': 'num', 'lb': 0.5, 'ub': 10}
        ])
        self.opt = HEBO(space)
        print("Initialiastion callback: ")

    def deg_to_rad(self, deg):
        return deg * m.pi / 180.0

    def on_training_start(self, locals_: Dict[str, Any], globals_: Dict[str, Any]) -> bool:
        print("Training started")

        #generate equally spaced initial points between -m.pi/2, m.pi/2 based on the batch size
        self.init_pos = np.linspace(-m.pi+0.001, m.pi-0.001, self.batch_size_opt).tolist()
        # self.init_pos = self.deg_to_rad(np.array([90.0, 88.0, 86.0, 84.0, 82.0, -90.0, -88.0, -86.0, -84.0, -82.0]))
        #set the environment id for each environment
        for i in range(self.n_envs_train):
            self.training_env.env_method('set_env_id', i, indices=[i])
        return True


    def _on_rollout_start(self) -> bool:

        print("...Updating the new lengths...")
        start_time = time.time()
        self.rec = self.opt.suggest(n_suggestions=self.n_envs_train // self.batch_size_opt)

        for i in range(self.n_envs_train//self.batch_size_opt):
            for j in range(self.batch_size_opt):
                new_pole_length = self.rec.values[i][0]
                self.training_env.env_method('set_pole_length', new_pole_length, indices=[i*self.batch_size_opt + j])
                self.training_env.env_method('set_init_pole_pos', self.init_pos[j], indices=[i*self.batch_size_opt + j])

                self.training_env.env_method('reset', indices=[i*self.batch_size_opt + j])

                dist_env_id = self.training_env.env_method('get_env_id', indices=[i*self.batch_size_opt + j])[0]
                init_pos = self.training_env.env_method('get_init_pole_pos', indices=[i*self.batch_size_opt + j])[0]
                print(f"env: {i*self.batch_size_opt + j:<1.2f}, real id:{dist_env_id}, pole length: {new_pole_length}, init pos: {init_pos}")

        print(f"Design proposal took {time.time() - start_time:.2f} seconds")

        return True

    def _on_rollout_end(self) -> bool:


        if self.num_timesteps >= self.steps_update_distribution-self.n_envs_train:

            print("...Starting design distribution update...")
            start_time = time.time()

            scores = []

            self.design_rewards_avg = [0 for _ in range(self.n_envs_train//self.batch_size_opt)]
            self.episode_length_avg = [0 for _ in range(self.n_envs_train//self.batch_size_opt)]
            for i in range(self.n_envs_train):
                print(f"Env ID: {self.training_env.env_method('get_env_id', indices=[i])[0]}, episode reward: {self.episode_rewards[i]},  Mean episode length: {self.episode_length[i]}, arm length: {self.training_env.env_method('get_pole_length', indices=[i])[0]}, design iter: {self.design_iteration[i]}, init pos: {self.training_env.env_method('get_init_pole_pos', indices=[i])[0]}")

            for i in range(self.n_envs_train//self.batch_size_opt):
                #average batch reward
                sum_reward = 0
                total_episode_length = 0
                for j in range(self.batch_size_opt):
                    sum_reward += self.episode_rewards[i*self.batch_size_opt + j]/self.design_iteration[i*self.batch_size_opt + j]
                    total_episode_length += self.episode_length[i*self.batch_size_opt + j]/self.design_iteration[i*self.batch_size_opt + j]
                self.design_rewards_avg[i] = sum_reward/self.batch_size_opt
                self.episode_length_avg[i] = total_episode_length/self.batch_size_opt
                score_array = np.array(self.design_rewards_avg[i]).reshape(-1, 1)  # Convert to NumPy array
                scores.append(-score_array) # HEBO minimizes, so we need to negate the scores

                # Logging
                current_pole_length = self.training_env.env_method('get_pole_length', indices=[i*self.batch_size_opt])[0]
                dist_env_id = self.training_env.env_method('get_env_id', indices=[i*self.batch_size_opt])[0]
                print(f"Env ID: {dist_env_id}, mean reward: {self.design_rewards_avg[i]}, Mean episode length: {self.episode_length_avg[i]}, arm length: {current_pole_length}")
                self.logger.record("mean reward", self.design_rewards_avg[i])
                self.logger.record("mean episode length", self.episode_length_avg[i])

                # Matlab logging
                self.mat_pole_length.append(current_pole_length)
                self.mat_reward.append(self.design_rewards_avg[i])
                self.mat_episode_length.append(self.episode_length_avg[i])


            # Update the design distribution
            scores = np.array(scores)  # Make sure the outer list is also a NumPy array
            self.opt.observe(self.rec, scores)
            self.state = 'propose_design'

            # After all iterations, print the best input and output
            best_idx = self.opt.y.argmin()
            best_design = self.opt.X.iloc[best_idx]
            best_design_reward = self.opt.y[best_idx]

            print(f"Best design: {best_design}, best reward: {best_design_reward}")
            self.best_design.append(best_design)
            self.best_design_reward.append(best_design_reward)

            print(f"Design distribution update took {time.time() - start_time:.2f} seconds")
        else:
            # Logging
            for i in range(self.n_envs_train):

                current_pole_length = self.training_env.env_method('get_pole_length', indices=[i])[0]
                dist_env_id = self.training_env.env_method('get_env_id', indices=[i])[0]
                print(f"Env ID: {dist_env_id}, episode reward: {self.episode_rewards[i]}, mean reward: {self.episode_rewards[i]/self.design_iteration[i]}, design iter: {self.design_iteration[i]}, Mean episode length: {self.episode_length[i]}, arm length: {current_pole_length}")
                self.logger.record("mean reward", self.episode_rewards[i]/self.design_iteration[i])
                self.logger.record("mean episode length", self.episode_length[i])

                # Matlab logging
                self.mat_pole_length.append(current_pole_length)
                self.mat_reward.append(self.episode_rewards[i]/self.design_iteration[i])
                self.mat_episode_length.append(self.episode_length[i]/self.design_iteration[i])

        # Reset episode reward accumulator
        self.design_iteration = [1 for _ in range(self.n_envs_train)]
        self.episode_rewards = {}
        self.episode_length = {}


        if self.num_timesteps % self.save_recorded_data == 0:
            output_data = {
                "pole_length": np.array(self.mat_pole_length),
                "reward": np.array(self.mat_reward),
                "iteration": np.array(self.mat_episode_length)
            }
            print("saving matlab data...")
            file_path = f"{self.save_path}/{self.mat_file_name}_batchsizeHebo_{self.batch_size_opt}.mat"
            savemat(file_path, output_data)
            print("Model saved")

        #increasing the batch size with each iteration
        # if self.num_timesteps % self.reduce_batch_size == 0:
        #     print("Increasing batch size...")
        #     self.batch_size_opt = 2 * self.batch_size_opt
        #     if self.batch_size_opt > self.n_envs_train:
        #         self.batch_size_opt = self.n_envs_train

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

if __name__ == '__main__':
    main()
