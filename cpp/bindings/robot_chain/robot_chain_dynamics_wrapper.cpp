#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "robot_chain_dynamics.h"
#include "robot_chain_dynamics_terminate.h"
#include "robot_chain_dynamics_initialize.h"
#include "coder_array.h"

namespace py = pybind11;

void robot_chain_dynamics_wrapper(py::array_t<double> q, py::array_t<double> dq, double rho,
                               double num_links, double radius, py::array_t<double> arm_length,
                               py::array_t<double> torque, py::array_t<double>& joint_acc,
                               py::array_t<double>& pos_tcp) {

    // Convert numpy arrays to coder::array
    coder::array<double, 1U> q_array, dq_array, arm_length_array, torque_array;
    coder::array<double, 1U> joint_acc_array;

    // Initialize coder::array with numpy array data and size
    q_array.set((double*)q.data(), q.size());
    dq_array.set((double*)dq.data(), dq.size());
    arm_length_array.set((double*)arm_length.data(), arm_length.size());
    torque_array.set((double*)torque.data(), torque.size());
    joint_acc_array.set(joint_acc.mutable_data(), joint_acc.size());

    // Prepare pos_tcp array
    double pos_tcp_array[3];

    // Call the original C++ function
    robot_chain_dynamics(q_array, dq_array, rho, num_links, radius,
                         arm_length_array, torque_array, joint_acc_array,
                         pos_tcp_array);

    // Copy back the data to numpy arrays for outputs
    std::copy(pos_tcp_array, pos_tcp_array + 3, pos_tcp.mutable_data());
}

PYBIND11_MODULE(robot_chain_dynamics_wrapper, m) {
    m.def("robot_chain_dynamics", &robot_chain_dynamics_wrapper, "A function to calculate system matrices and joint accelerations and positions");
}
