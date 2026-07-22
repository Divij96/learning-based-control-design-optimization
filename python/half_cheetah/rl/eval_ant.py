from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[3]

from stable_baselines3 import PPO
from ant_v4 import AntEnv
from stable_baselines3.common.vec_env import SubprocVecEnv
import numpy as np
from scipy.io import savemat
import time
import math as m
import xml.etree.ElementTree as ET

def main():

    episode_length_loop = 1000
    batch_size = 10

    # Training parameters
    while True:

        # EVAL_MODEL_PATH = f"{REPO_ROOT}/python/half_cheetah/rl/trained_model/random_design/Half_cheetah_dynamics_const_random_design_start_upd_25lr_mean0.01_std_0.01_sdeFalse_Tanh_Tsteps_12800000_lr_0.0001_hidden_sizes_256_FORreward_1.0_CTRLcost_1.0_var_design"
        # EVAL_MODEL_PATH = f"{REPO_ROOT}/python/half_cheetah/rl/trained_model/random_design/Half_cheetah_dynamics_constant_design_random_design_start_upd_25lr_mean0.01_std_0.01_sdeFalse_Tanh_Tsteps_12800000_lr_0.0001_hidden_sizes_256_FORreward_1.0_CTRLcost_1.0_var_design"


        # stiffness = 5*np.array([50.0, 50.0, 50.0, 50.0, 50.0, 50.0])
        for iter in range(batch_size):

            eval_env = create_env()

            rewards = 0
            episode_length = 0

            for _ in range(episode_length_loop):
                actions = np.array([0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0])
                obs, rewards_env, dones, early_stop ,infos = eval_env.step(actions)
                rewards += rewards_env
                episode_length += 1
                # time.sleep(0.05)
                # if dones:
                #     break

def create_env():
    return AntEnv()


def modify_xml_stiffness(file_path, stiffness_values):
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
