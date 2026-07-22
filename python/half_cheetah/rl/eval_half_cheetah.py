from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[3]

from stable_baselines3 import PPO
from half_cheetah_v4 import HalfCheetahEnv
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
        EVAL_MODEL_PATH = f"{REPO_ROOT}/python/half_cheetah/rl/trained_model/random_design/Half_cheetah_dynamics_constant_design_random_design_start_upd_25lr_mean0.01_std_0.01_sdeFalse_Tanh_Tsteps_12800000_lr_0.0001_hidden_sizes_256_FORreward_1.0_CTRLcost_2.0_var_design"
        mujoco_file_folder = f"{REPO_ROOT}/assets/mujoco/half_cheetah/"
        # stiffness = [348.849528, 392.320462, 118.132672, 484.039642, 411.843929, 368.657455]
        # stiffness = [382.77, 208.47, 142.39, 422.33, 494.99, 156.47]
        # stiffness = [240.0, 180.0, 120.0, 180.0, 120.0, 60.0]
        # stiffness = [495.975, 572.092, 136.334, 483.064, 358.19,  616.395]
        # stiffness = [548.922, 312.522, 170.263, 514.539, 496.388, 145.926]
        # stiffness = [344.262476, 281.186121, 362.159516, 423.990564, 484.720639, 517.179648]
        stiffness = [355.057876667471, 299.820855117453, 378.324215785938, 465.081778806844, 457.768236524388, 451.796873601263]
        stiffness = [343.718869681552, 291.143336253668, 368.004749414057, 414.211185133853, 449.430751513667, 513.065015346920]
        # stiffness = [240.0, 180.0, 120.0, 180.0, 120.0, 60.0]
        # stiffness = [300.0, 300.0, 300.0, 300.0, 300.0, 300.0]

        stiffness = [306.338, 636.608, 217.815, 391.246, 224.492, 501.802]
        stiffness = [10.0, 10.0, 10.0, 10.0, 10.0, 10.0]

        # stiffness = 5*np.array([50.0, 50.0, 50.0, 50.0, 50.0, 50.0])
        for iter in range(batch_size):
            modify_xml_stiffness(f"{mujoco_file_folder}half_cheetah_{0}.xml", stiffness)
            eval_env = create_env()
            model = PPO.load(EVAL_MODEL_PATH, env=eval_env)

            rewards = 0
            episode_length = 0
            obs = model.env.reset()

            for _ in range(episode_length_loop):
                actions, _states = model.predict(obs)
                obs, rewards_env, dones, infos = model.env.step(actions)
                rewards += rewards_env
                episode_length += 1
                time.sleep(0.05)
                if dones:
                    break

def create_env(pole_length=0.5, init_pole_pos=0.0):
    return HalfCheetahEnv()


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
