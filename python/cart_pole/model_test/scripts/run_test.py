import os
from pathlib import Path
import time
from collections import OrderedDict
import pickle
import sys
import gym
from gym import wrappers
import numpy as np
from gym.envs.registration import register
from scipy.io import loadmat, savemat

from src.quadcopter_env import QuadcopterEnv

REPO_ROOT = Path(__file__).resolve().parents[4]

def main():
    register(
        id='Quadcopter-v0',
        entry_point='src.quadcopter_env:QuadcopterEnv',
    )

    env = gym.make('Quadcopter-v0')
    ob = env.reset()

    obs, acs, rewards, position, velocity, omega, R = [], [], [], [], [], [], []

    # Load .mat file
    input_path = Path(
        os.environ.get(
            "MASTER_THESIS_INPUT_CMD",
            REPO_ROOT / "data" / "input_cmd.mat",
        )
    )
    data = loadmat(input_path)

    # Assume the key you're interested in is 'input_cmd'.
    # Adjust this to be the actual key for the data you want to use.
    data_key = 'w'

    # Check if the key exists in the .mat file and is 2D
    if data_key in data and len(data[data_key].shape) == 2:
        data_list = data[data_key].tolist()
    else:
        print(f"{data_key} not found in .mat file or it is not 2D")
        return

    for i in range(len(data_list)):

        acs = np.array(data_list[i])
        ob, rew, done, _ = env.step(acs)
        position.append(ob[0:3])
        velocity.append(ob[3:6])
        omega.append(ob[6:9])
        R.append(ob[9:18])  # Reshape into 3x3 matrix before appending
        rewards.append(rew)
    # R = np.array(R)  # Convert list of matrices into a 3D array
    # R = np.transpose(R, (1, 2 , 0))

    print("step: ", i, "  " ,data_list[i])

    # Save the data
    output_data = {
        "rewards_python": np.array(rewards),
        "position_python": np.array(position),
        "velocity_python": np.array(velocity),
        "omega_python": np.array(omega),
        "R_python": np.array(R),

    }

    print("saving to output.mat...")
    output_dir = REPO_ROOT / "outputs" / "model_tests"
    output_dir.mkdir(parents=True, exist_ok=True)
    savemat(output_dir / "quadcopter_output.mat", output_data)


if __name__ == "__main__":
    main()
