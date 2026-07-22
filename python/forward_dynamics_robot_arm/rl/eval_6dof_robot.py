#!/usr/bin/env python
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[3]

import rospy
from visualization_msgs.msg import Marker
from geometry_msgs.msg import Point, Quaternion
import tf.transformations as tf_trans
import numpy as np
import math
from robot_6dof_arm_dynamics import Robot_6dof_Arm_Dynamics
from stable_baselines3 import PPO
from visualization_msgs.msg import Marker, MarkerArray
from scipy.spatial.transform import Rotation as R
from std_msgs.msg import ColorRGBA
import time
from geometry_msgs.msg import Point, Vector3, Quaternion
def quaternion_from_euler(roll, pitch, yaw):
    """Convert Euler angles to quaternion."""
    return tf_trans.quaternion_from_euler(roll, pitch, yaw)

from geometry_msgs.msg import Quaternion
import numpy as np
import math
# Assuming quaternion_from_euler is from tf.transformations or a similar utility is available
from tf.transformations import quaternion_from_euler, quaternion_about_axis

def quaternion_from_axis_angle(axis, angle):
    """Convert axis-angle to quaternion. This is a placeholder for demonstration."""
    # Normalize the axis to ensure it's a unit vector
    axis = axis / np.linalg.norm(axis)
    qx = axis[0] * np.sin(angle / 2)
    qy = axis[1] * np.sin(angle / 2)
    qz = axis[2] * np.sin(angle / 2)
    qw = np.cos(angle / 2)
    return qx, qy, qz, qw

# def create_arm_marker(arm_id, start_point, end_point, diameter, color=np.array([0, 1, 0]), frame_id="map"):
#     """Corrected function to calculate quaternion orientation for the cylinder."""
#     marker = Marker()
#     marker.header.frame_id = frame_id
#     marker.type = Marker.CYLINDER
#     marker.action = Marker.ADD
#     marker.ns = "robot_arms"
#     marker.id = arm_id
#     marker.scale.x = diameter
#     marker.scale.y = diameter
#     marker.scale.z = np.linalg.norm([end_point.x - start_point.x, end_point.y - start_point.y, end_point.z - start_point.z])

#     marker.pose.position.x = (start_point.x + end_point.x) / 2.0
#     marker.pose.position.y = (start_point.y + end_point.y) / 2.0
#     marker.pose.position.z = (start_point.z + end_point.z) / 2.0

#     # Calculate the direction vector and axis of rotation
#     # Ensure direction is calculated as a float array
#     direction = np.array([end_point.x - start_point.x, end_point.y - start_point.y, end_point.z - start_point.z], dtype=float)
#     direction_norm = np.linalg.norm(direction)
#     if direction_norm == 0:
#         direction = np.array([0, 0, 1])
#     else:
#         direction /= direction_norm

#     axis = np.cross([0, 0, 1], direction)
#     if np.linalg.norm(axis) == 0:  # If direction is parallel to z-axis
#         axis = [0, 1, 0]  # Choose an arbitrary perpendicular axis
#     angle = np.arccos(np.dot([0, 0, 1], direction))

#     # Convert axis-angle to quaternion
#     qx, qy, qz, qw = quaternion_from_axis_angle(axis, angle)

#     marker.pose.orientation.x = qx
#     marker.pose.orientation.y = qy
#     marker.pose.orientation.z = qz
#     marker.pose.orientation.w = qw

#     marker.color.r = color[0]
#     marker.color.g = color[1]
#     marker.color.b = color[2]
#     marker.color.a = 1.0

#     return marker

def create_arm_marker(arm_id, start_point, end_point, diameter, color=np.array([0, 1, 0]), frame_id="map"):
    # Create a marker object
    marker = Marker()
    marker.header.frame_id = frame_id
    marker.header.stamp = rospy.Time.now()
    marker.ns = "arm_marker"
    marker.id = arm_id
    marker.type = Marker.CYLINDER
    marker.action = Marker.ADD

    # Calculate the midpoint for the position of the cylinder
    marker.pose.position.x = (start_point[0] + end_point[0]) / 2
    marker.pose.position.y = (start_point[1] + end_point[1]) / 2
    marker.pose.position.z = (start_point[2] + end_point[2]) / 2

    # Calculate the vector from start to end and its length
    vec = np.array(end_point) - np.array(start_point)
    length = np.linalg.norm(vec)

    # Normalize the vector
    vec_normalized = vec / length

    # Calculate the angle and axis for the rotation
    z_axis = np.array([0, 0, 1])
    axis = np.cross(z_axis, vec_normalized)
    axis_length = np.linalg.norm(axis)
    if axis_length != 0:
        axis = axis / axis_length  # Ensure the axis is normalized
        angle = np.arccos(np.dot(z_axis, vec_normalized))
    else:
        # This handles the case where the vector is already aligned with the Z-axis
        angle = 0 if vec_normalized[2] > 0 else np.pi

    # Creating a quaternion from the axis and angle
    quat = quaternion_about_axis(angle, axis if axis_length != 0 else z_axis)

    # Set the orientation of the marker
    marker.pose.orientation.x = quat[0]
    marker.pose.orientation.y = quat[1]
    marker.pose.orientation.z = quat[2]
    marker.pose.orientation.w = quat[3]

    # Set the scale of the marker
    marker.scale.x = diameter  # Diameter in X
    marker.scale.y = diameter  # Diameter in Y
    marker.scale.z = length    # Length of the cylinder

    # Set the color of the marker
    marker.color.r = color[0]
    marker.color.g = color[1]
    marker.color.b = color[2]
    marker.color.a = 1.0  # Alpha value

    return marker


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
    marker.pose.position.z = target_pos[2]

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
    num_links = 6
    diameters = np.ones(num_links) * 0.05
    eval_env = Robot_6dof_Arm_Dynamics(env_id = 1, num_links=num_links, call_back=f"eval")
    pub = rospy.Publisher('visualization_marker_array', MarkerArray, queue_size=num_links)

    t = 0  # Time variable for the wave function

    #load the model
    # EVAL_MODEL_PATH = f"{REPO_ROOT}/python/scara_2dof_robot/rl/trained_model/random_design/PlanarRobot_length_constant_design_start_upd_25lr_mean0.01_std_0.01_sdeFalse_Tanh_Tsteps_107520000_lr_0.0001_hidden_sizes_256_POSreward_1.0_VELreward_0.0_omega_pen_0.4_var_design"

    EVAL_MODEL_PATH = f"{REPO_ROOT}/python/forward_dynamics_robot_arm/rl/trained_model/random_design/ScaraRobot_dynamics_6arm_random_design_start_upd_25lr_mean0.01_std_0.01_sdeFalse_Tanh_Tsteps_25600000_lr_0.0001_hidden_sizes_256_POSreward_1.0_VELreward_0.0_omega_pen_0.0_var_design"
    eval_model = PPO.load(EVAL_MODEL_PATH, env=eval_env)
    obs, info = eval_env.reset()
    done = False
    while not rospy.is_shutdown():

        actions, _states = eval_model.predict(obs)

        # wave input for num_links

        # if done:
        #     obs, info = eval_env.reset()

        obs, reward, done, early_Stop, info = eval_env.step(actions)

        joint_angles = info['joint_pos']
        arm_lengths = info['arm_length']

        marker_array = MarkerArray()

        # Initialize the cumulative transformation matrix
        cumulative_transformation = np.eye(4)  # 4x4 identity matrix
        diameter = 0.05

        # Initialize variables
        link_points = info['link_pos_data']

        start_point = np.array([0.0, 0.0, 0.0])
        end_point = np.array([0.0, 0.0, 0.0])

        for i in range(6):
            if i == 0:
                start_point = np.array([0.0, 0.0, 0.0])
            else:
                start_point[0] = link_points[i - 1]
                start_point[1] = link_points[i + 5]
                start_point[2] = link_points[i + 11]

            end_point[0] = link_points[i]
            end_point[1] = link_points[i + 6]
            end_point[2] = link_points[i + 12]

            # Create and append the marker for the current link
            marker = create_arm_marker(i, start_point, end_point, diameter)
            marker_array.markers.append(marker)


        pub.publish(marker_array)

        t += 0.001



if __name__ == '__main__':
    main()
