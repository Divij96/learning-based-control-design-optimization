#!/usr/bin/env python
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[3]

import rospy
from visualization_msgs.msg import Marker
from geometry_msgs.msg import Point, Quaternion
import tf.transformations as tf_trans
import numpy as np
import math
from planar_robot_env import PlanarRobotEnv
from stable_baselines3.common.vec_env import SubprocVecEnv
from stable_baselines3 import PPO
import time

def quaternion_from_euler(roll, pitch, yaw):
    """Convert Euler angles to quaternion."""
    return tf_trans.quaternion_from_euler(roll, pitch, yaw)

def create_arm_marker(arm_id, start_point, end_point, diameter, frame_id="map"):
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
    marker.color.r = 0.0
    marker.color.g = 0.0
    marker.color.b = 1.0
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
    rospy.init_node('robot_arm_visualizer')
    pub = rospy.Publisher('visualization_marker', Marker, queue_size=10)
    rate = rospy.Rate(1000)  # 20 Hz for smooth animation
    arm_lengths = [1.0, 1.0, 1.0]  # Lengths of the arms
    diameters = [0.1, 0.1, 0.1]  # Diameter of the arms
    eval_env = PlanarRobotEnv(arm_length = arm_lengths)

    t = 0  # Time variable for the wave function

    #load the model
    EVAL_MODEL_PATH = f"{REPO_ROOT}/src/custom_robot/rl/trained_model/random_design/PlanarRobot_length_constant_design_start_upd_25lr_mean0.01_std_0.01_sdeFalse_Tanh_Tsteps_107520000_lr_1e-05_hidden_sizes_256_POSreward_1.0_VELreward_0.0_omega_pen_0.0_var_design"
    eval_model = PPO.load(EVAL_MODEL_PATH, env=eval_env)


    obs, info = eval_env.reset()

    while not rospy.is_shutdown():
        # joint_torque = np.array([
        #     math.sin(t),
        #     math.sin(t + math.pi / 2),
        #     math.sin(t + math.pi)
        # ])


        actions, _states = eval_model.predict(obs)

        obs, reward, done, early_Stop, info = eval_env.step(actions)

        joint_angles = info['joint_pos']
        arm_lengths = info['arm_length']

        start_point = Point(0, 0, 0)
        if t > (512 * 5)/1000 or done:
            t = 0
            eval_env.reset()


        accumulated_angle = 0  # Initialize accumulated angle

        for i, (length, diameter) in enumerate(zip(arm_lengths, diameters)):
            accumulated_angle += joint_angles[i]  # Accumulate joint angles

            end_point = Point(
                start_point.x + length * math.cos(accumulated_angle),
                start_point.y + length * math.sin(accumulated_angle),
                0
            )
            marker = create_arm_marker(i, start_point, end_point, diameter)
            pub.publish(marker)
            start_point = end_point

        target_pos = info['target_pos']
        target_marker = create_target_marker(target_pos, 0.2)
        target_tcp_pos = info['pos_tcp']
        target_tcp_marker = create_target_marker(target_tcp_pos, 0.2, marker_name=f"target_pos_tcp")
        pub.publish(target_tcp_marker)
        pub.publish(target_marker)


        if t > 200:
            break
        t += 0.001
        rate.sleep()


if __name__ == '__main__':
    main()
