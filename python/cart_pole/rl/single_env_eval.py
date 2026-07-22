from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[3]

from stable_baselines3 import PPO
from env_cartpole import CartPoleEnv
import numpy as np
from scipy.io import savemat
import time
import os
import matplotlib.pyplot as plt
import matplotlib.animation as animation

def main():
    # Training parameters
    REWARD = np.array([1.0, 0.0, 0.0])
    global_iteration = 0
    EVAL = True
    model_name = f"CartPoleEnv_Tanh_Tsteps_122880000_lr0.0001_hidden_sizes_256_lay2_rewardUpRight_1_obsLen_min1002_polemass_GaussMix_9"
    EVAL_MODEL_PATH = f"{REPO_ROOT}/python/cart_pole/rl/trained_model/random_dist/CartPole_random_design_Tanh_Tsteps_51200000_lr_0.0001_hidden_sizes_256_reward_1.00.20.1_pole_length_1.0_freq_1"
    eval_env = create_env(REWARD)
    eval_model = PPO.load(EVAL_MODEL_PATH, env=eval_env)
    while True:
        global_iteration += 1

        if EVAL:
            evaluate(eval_model, model_name, global_iteration)

        break

def create_env(reward_config):
    return CartPoleEnv(REWARD=reward_config)

def evaluate(model, model_name, global_iteration):
    LOOP_COUNT = 1000
    cart_position = []
    pole_position = []
    rewards = []
    effort = []
    avg_effort = []
    force = []
    policy_action = []
    pole_angle = []
    average_effort_mat, steps, ep_reward_mat, pole_length, pole_position_mat, cart_position_mat = [], [], [], [], [], []
    ep_reward = 0
    step_count = 0
    effort_temp = 0
    start_time = time.time()
    obs = model.env.reset()
    k=0
    print("starting evaluation")

    for num in range(LOOP_COUNT):
        if num % 2500 == 0:
            end_time = time.time()
            print(f"iteration: {num}, iteration per sec: {10000/(end_time-start_time)}")
            start_time = time.time()

        actions, _states = model.predict(obs)
        obs, reward, done, info = model.env.step(actions)

        policy_action.append(np.array(actions))
        cart_position.append(np.array(info[0]['cart_pos']))
        pole_position.append(np.array(info[0]['pole_pos']))
        avg_effort.append(np.array(info[0]['effort']))
        rewards.append(np.array(reward))
        pole_length.append(np.array(info[0]['pole_length']))
        effort_temp = effort_temp + abs(np.array(info[0]['force']))*0.02
        effort.append(np.array(effort_temp))
        force.append(np.array(info[0]['force']))
        pole_angle.append(np.array(info[0]['pole_angle']))
        ep_reward += reward
        step_count += 1
        print(f"pole angle: {info[0]['pole_angle'][0]:<10.2f}, reward: {reward[0]:<10.2f}, pole length: {info[0]['pole_length']}, init pos: {info[0]['init_pos']}")

        if done:
            average_effort_mat.append(np.mean(avg_effort))
            steps.append(np.array(step_count))
            ep_reward_mat.append(np.array(ep_reward))
            avg_effort = []
            ep_reward = 0
            step_count = 0
            effort_temp = 0
            # model.env.env_method('set_pole_length', eval_pole_length[k])
            print("steps: ", steps[k])
            k+=1
            break

    # Visualization call
    # Convert lists to numpy arrays for visualization

    np_pole_angles = np.array(pole_angle)
    np_cart_positions = np.array(cart_position)
    np_pole_positions = np.array(pole_position)
    visualize_cart_pole(np_cart_positions, np_pole_positions, np_pole_angles)

    # Save data in a MATLAB file
    output_data = {
        "cart_position": np.array(cart_position),
        "pole_position": np.array(pole_position),
        "pole_length": np.array(pole_length),
        "average_effort": np.array(average_effort_mat),
        "steps": np.array(steps),
        "ep_reward": np.array(ep_reward_mat),
        "rewards": np.array(rewards),
        "effort": np.array(effort),
        "force": np.array(force),
        "policy_action": np.array(policy_action),
        "pole_angle": np.array(pole_angle)
    }
    print("saving to output.mat...")

    file_path = f"{REPO_ROOT}/outputs/cart_pole/EVAL_{model_name}.mat"

    savemat(file_path, output_data)
    print("saved to output.mat")

def visualize_cart_pole(cart_positions, pole_positions, pole_angles):
    fig, ax = plt.subplots()
    cart, = ax.plot([cart_positions[0], cart_positions[0]], [0, 0], color='b', marker='s', linewidth=5, markersize=20)
    pole, = ax.plot([cart_positions[0], pole_positions[0, 0]], [0, pole_positions[0, 1]], color='r', linewidth=2)
    angle_text = ax.text(0.05, 0.95, '', transform=ax.transAxes, verticalalignment='top')
    ax.set_xlim([-10, 10])
    ax.set_ylim([-10, 10])
    ax.set_aspect('equal')
    ax.set_facecolor('white')

    def update(frame):
        cart.set_xdata([cart_positions[frame], cart_positions[frame]])
        pole.set_xdata([cart_positions[frame], pole_positions[frame, 0]])
        pole.set_ydata([0, pole_positions[frame, 1]])

        # Check if pole_angles[frame] is an array and extract the first element
        angle_value = pole_angles[frame][0] if isinstance(pole_angles[frame], np.ndarray) else pole_angles[frame]
        angle_text.set_text(f'Pole Angle: {angle_value:.2f} rad')

        return cart, pole, angle_text


    ani = animation.FuncAnimation(fig, update, frames=len(cart_positions), interval=50, blit=True)
    plt.show()


if __name__ == '__main__':
    main()