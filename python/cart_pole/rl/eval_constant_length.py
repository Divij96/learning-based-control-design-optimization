from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[3]

from stable_baselines3 import PPO
from env_cartpole import CartPoleEnv
from stable_baselines3.common.vec_env import SubprocVecEnv
import numpy as np
from scipy.io import savemat
import time
import math as m

def main():
    pole_length = 0.5
    episode_length_loop = 5120
    batch_size = 10
    mat_episode_length = []
    mat_rewards = []
    mat_pole_length = []


    # Training parameters
    while True:

        REWARD = np.array([1.0, 0.2, 0.2])

        n_envs = 1
        model_name = f"CartPole_constant_design_Tanh_Tsteps_10240000_lr_5e-05_hidden_sizes_256_reward_1.00.2{REWARD[2]}_pole_length_{pole_length}_freq_1_schaff_lr0.1"
        EVAL_MODEL_PATH = f"{REPO_ROOT}/python/cart_pole/rl/trained_model/constant_mass/{model_name}"
        matlab_model_name = f"CartPole_constant_design_Tanh_Tsteps_5120000_lr_0.0001_hidden_sizes_256_reward_1.00.2{REWARD[2]}_freq_1"
        matlab_model_path = f"{REPO_ROOT}/python/cart_pole/rl/trained_model/constant_mass/new_matlab_results/{matlab_model_name}.mat"
        # Load the model once outside of the loop
        init_pos = np.linspace(-m.pi+0.001, m.pi-0.001, batch_size).tolist()
        print(init_pos)

        for iter in range(batch_size):
            eval_env = create_env(REWARD, pole_length=pole_length, init_pole_pos=init_pos[iter])
            model = PPO.load(EVAL_MODEL_PATH, env=eval_env)
            start_time = time.time()
            rewards = 0
            episode_length = 0
            obs = model.env.reset()
            print(f"Initial pole position: {init_pos[iter]}")
            for _ in range(episode_length_loop):
                actions, _states = model.predict(obs)
                obs, rewards_env, dones, infos = model.env.step(actions)
                rewards += rewards_env
                episode_length += 1
                if dones:
                    break
            print(f"Episode length: {episode_length}, Rewards: {rewards}, Pole length: {pole_length}, init_pos: {infos[0]['init_pos']}, iterations per sec:, {episode_length/(time.time()-start_time)}")
            mat_episode_length.append(episode_length)
            mat_rewards.append(rewards)
            mat_pole_length.append(pole_length)
        pole_length += 0.5
        # Save data in a MATLAB file
        output_data = {
            "episode_length": np.array(mat_episode_length),
            "rewards": np.array(mat_rewards),
            "pole_length": np.array(mat_pole_length)
            }

        savemat(matlab_model_path, output_data)


def create_env(reward_config,pole_length=0.5, init_pole_pos=0.0):
    return CartPoleEnv(REWARD=reward_config, pole_length=pole_length, init_pos=init_pole_pos)


if __name__ == '__main__':
    main()
