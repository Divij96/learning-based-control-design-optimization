from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[3]

import numpy as np
import sys
sys.path.append(f'{REPO_ROOT}/devel/lib')
import robot_chain_dynamics_wrapper

# Example data (make sure these are appropriate for your specific function)
q = np.array([1.0, 2.0, 3.0], dtype=np.double) # Example joint positions
dq = np.array([0.1, 0.2, 0.3], dtype=np.double) # Example joint velocities
rho = 7850 # Example density
num_links = 3 # Number of links
radius = 0.05 # Example radius
arm_length = np.array([1.0, 1.2, 1.5], dtype=np.double) # Example arm lengths
torque = np.array([10, 20, 30], dtype=np.double) # Example torques

# Pre-allocate arrays for outputs (make sure sizes are correct)
joint_acc = np.zeros_like(q, dtype=np.double)
pos_tcp = np.zeros(3, dtype=np.double) # Assuming pos_tcp is a 3-element array

print(q,dq,rho,num_links,radius,arm_length,torque,joint_acc,pos_tcp)
# Call the wrapped function
robot_chain_dynamics_wrapper.robot_chain_dynamics(q, dq, rho, num_links, radius, arm_length, torque, joint_acc, pos_tcp)

# joint_acc and pos_tcp are now filled with the results
print("Joint Accelerations:", joint_acc)
print("Position TCP:", pos_tcp)
