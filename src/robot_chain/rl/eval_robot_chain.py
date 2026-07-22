#!/usr/bin/env python
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[3]

import rospy
from visualization_msgs.msg import Marker
from geometry_msgs.msg import Point, Quaternion
import tf.transformations as tf_trans
import numpy as np
import math
from robot_chain_dynamics import Robot_Chain_Env
from stable_baselines3 import PPO
from visualization_msgs.msg import Marker, MarkerArray

import time

def quaternion_from_euler(roll, pitch, yaw):
    """Convert Euler angles to quaternion."""
    return tf_trans.quaternion_from_euler(roll, pitch, yaw)

def create_arm_marker(arm_id, start_point, end_point, diameter, color=np.array([0, 1, 0]),frame_id="map"):
    """Create a Marker message to represent the robot arm."""
    marker = Marker()
    marker.header.frame_id = frame_id
    marker.type = marker.CYLINDER
    marker.action = marker.ADD
    marker.ns = "robot_arms"
    marker.id = arm_id
    marker.scale.x = diameter
    marker.scale.y = diameter
    marker.scale.z = np.linalg.norm([end_point.x - start_point.x, end_point.y - start_point.y])

    # Set the position of the cylinder
    marker.pose.position.x = (start_point.x + end_point.x) / 2.0
    marker.pose.position.y = (start_point.y + end_point.y) / 2.0
    marker.pose.position.z = 0

    # Calculate orientation of the arm
    angle = math.atan2(end_point.y - start_point.y, end_point.x - start_point.x)
    quat = quaternion_from_euler(0, math.pi/2, angle)

    marker.pose.orientation = Quaternion(*quat)

    # Set the color of the arm
    marker.color.r = color[0]
    marker.color.g = color[1]
    marker.color.b = color[2]
    marker.color.a = 1.0

    return marker

# visualise target pos with a sphere

def create_target_marker(target_pos, diameter, frame_id="map", marker_name=f"target_pos"):
    """Create a Marker message to represent the robot arm."""
    marker = Marker()
    marker.header.frame_id = frame_id
    marker.type = marker.SPHERE
    marker.action = marker.ADD
    marker.ns = marker_name
    marker.id = 1
    marker.scale.x = diameter
    marker.scale.y = diameter
    marker.scale.z = diameter

    # Set the position of the cylinder
    marker.pose.position.x = target_pos[0]
    marker.pose.position.y = target_pos[1]
    marker.pose.position.z = 0

    # Set the color of the arm
    marker.color.r = 1.0
    marker.color.g = 0.0
    marker.color.b = 0.0
    marker.color.a = 1.0

    return marker

def main():
    print("Starting robot arm visualizer...")
    rospy.init_node('robot_arm_visualizer')
    rate = rospy.Rate(20)  # 20 Hz for smooth animation
    arm_lengths = [1.0, 1.0]  # Lengths of the arms
    num_links = 4
    diameters = np.ones(num_links) * 0.05
    eval_env = Robot_Chain_Env(env_id = 1, num_links=num_links, call_back=f"eval")
    pub = rospy.Publisher('visualization_marker_array', MarkerArray, queue_size=num_links)

    t = 0  # Time variable for the wave function

    #load the model
    # EVAL_MODEL_PATH = f"{REPO_ROOT}/src/scara_2dof_robot/rl/trained_model/random_design/PlanarRobot_length_constant_design_start_upd_25lr_mean0.01_std_0.01_sdeFalse_Tanh_Tsteps_107520000_lr_0.0001_hidden_sizes_256_POSreward_1.0_VELreward_0.0_omega_pen_0.4_var_design"

    EVAL_MODEL_PATH = f"{REPO_ROOT}/src/robot_chain/rl/trained_model/random_design/ScaraRobot_dynamics_random_design_start_upd_25lr_mean0.01_std_0.01_sdeFalse_Tanh_Tsteps_20480000_lr_0.0001_hidden_sizes_256_POSreward_1.0_VELreward_0.0_omega_pen_0.0_var_design"
    eval_model = PPO.load(EVAL_MODEL_PATH, env=eval_env)
    obs, info = eval_env.reset()
    done = False
    while not rospy.is_shutdown():

        actions, _states = eval_model.predict(obs)

        # wave input for num_links

        if done:
            obs, info = eval_env.reset()

        obs, reward, done, early_Stop, info = eval_env.step(actions)

        joint_angles = info['joint_pos']
        arm_lengths = info['arm_length']

        start_point = Point(0, 0, 0)
        if t > (512)/1000 or done:
            print("total steps: ", t*1000)
            t = 0
            print("resetting")
            eval_model = PPO.load(EVAL_MODEL_PATH, env=eval_env)
            eval_env.reset()


        marker_array = MarkerArray()

        accumulated_angle = 0  # Initialize accumulated angle
        if done:
            color = np.array([1, 0, 0])
        else:
            color = np.array([0, 1, 0])
        for i, (length, diameter) in enumerate(zip(arm_lengths, diameters)):
            accumulated_angle += joint_angles[i]  # Accumulate joint angles

            end_point = Point(
                start_point.x + length * math.cos(accumulated_angle),
                start_point.y + length * math.sin(accumulated_angle),
                0
            )
            marker = create_arm_marker(i, start_point, end_point, diameter)
            marker_array.markers.append(marker)
            start_point = end_point


        # Visualization of Collision Pattern 1
        collision_pattern_1 = info['collision_pattern_1']
        for i in range(len(collision_pattern_1) - 1):
            start_point = Point(*collision_pattern_1[i], 0)
            end_point = Point(*collision_pattern_1[i + 1], 0)
            collision_pattern_1_marker = create_arm_marker(num_links + i, start_point, end_point, diameter, color,frame_id="map")
            marker_array.markers.append(collision_pattern_1_marker)


        # Add target markers
        target_pos = info['target_pos']
        target_marker = create_target_marker(target_pos, 0.2)
        target_tcp_pos = info['pos_tcp']
        target_tcp_marker = create_target_marker(target_tcp_pos, 0.2, marker_name=f"target_pos_tcp")

        marker_array.markers.append(target_marker)
        marker_array.markers.append(target_tcp_marker)

        pub.publish(marker_array)

        t += 0.001
        time.sleep(0.1)
        # rate.sleep()


if __name__ == '__main__':
    main()
