from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[3]

# import sys
# import time
# import numpy as np
# sys.path.append(f'{REPO_ROOT}/devel/lib')
# import forward_dynamics_4arm_wrapper
# import forward_dynamics_6arm_wrapper

# # Example input data
# num_links = 6
# rho = 2000.0
# radius = 0.025
# arm_length = np.array([2] * num_links)
# # joint_axes = np.array([[0, 0, 1]] * num_links).flatten()
# joint_angles = np.array([0] * num_links)
# config = np.array([0.0] * num_links)
# vel = np.array([1.0] * num_links)
# tq = np.array([50.0] * num_links)
# acc_data = np.zeros(num_links)
# link_pos_data = np.zeros(18)
# # Timing and loop configuration
# num_iterations = 1  # Total number of function calls
# print_interval = 1   # Print the execution time every 'print_interval' iterations
# total_time = 0        # Total accumulated time



# for i in range(1, num_iterations + 1):
#     start_time = time.time()  # Start timing

#     if num_links == 4:
#         # Call the wrapper function
#         joint_axes = np.array([ 0, 0, 0, 0,
#                                 0, 0, 0, 0,
#                                 1, 1, 1, 1])
#         forward_dynamics_4arm_wrapper.forward_dynamics_robot(rho, radius, arm_length, joint_axes, joint_angles,
#                                                         config, vel, tq, acc_data)
#     else:
#         # Call the wrapper function

#         joint_axes = np.array([ 0, 1, 0, 0, 0, 0,
#                                 0, 0, 0, 0, 0, 0,
#                                 1, 0, 1, 1, 1, 1])
#         forward_dynamics_6arm_wrapper.forward_dynamics_robot(rho, radius, arm_length, joint_axes, joint_angles,
#                                                         config, vel, tq, acc_data, link_pos_data)

#     end_time = time.time()  # End timing
#     elapsed_time = end_time - start_time
#     total_time += elapsed_time

#     # Print the average execution time at specified intervals
#     if i % print_interval == 0:
#         print(f"Iteration {i}: Average execution time: {i / total_time:.6f} per second")

# # Optionally, print final average execution time
# print(f"Final average execution time over {num_iterations} iterations: {total_time / num_iterations:.6f} seconds")

# print(acc_data)


import numpy as np
import sys
import math as m
sys.path.append(f'{REPO_ROOT}/devel/lib')

import forward_dynamics_6arm_wrapper

# Example input data
num_links = 6
rho = 2000.0  # Material density
radius = 0.025  # Radius of the arm
arm_length = np.array([2.0] * num_links, dtype=np.double)  # Arm lengths
joint_axes = np.array([
                        0, 0, 0, 0, 0, 0,
                        1, 1, 1, 1, 1, 1,
                        0, 0, 0, 0, 0, 0,
                    ], dtype=np.double)  # Joint axes, reshaped appropriately if necessary
# joint_angles = np.array([0.0] * num_links, dtype=np.double)  # Joint angles
joint_angles = np.array([0.0, 0.0, 0.0, 0.0, 0.0, 0.0], dtype=np.double) # Joint angles
config = np.array([0.0] * num_links, dtype=np.double)  # Configuration
vel = np.array([0.0] * num_links, dtype=np.double)  # Velocities
tq = np.array([0.0] * num_links, dtype=np.double)  # Torques

# Output arrays must be pre-allocated
acc_data = np.zeros(num_links, dtype=np.double)  # Acceleration data
link_pos_data = np.zeros(18, dtype=np.double)  # Link position data

# Call the wrapper function
while True:
    forward_dynamics_6arm_wrapper.forward_dynamics_robot(rho, radius, arm_length, joint_axes,
                                                        joint_angles, config,vel, tq, acc_data, link_pos_data)

    vel = vel + acc_data*0.001
    joint_angles = joint_angles + vel*0.001
    print("Joint Angles:", joint_angles)
