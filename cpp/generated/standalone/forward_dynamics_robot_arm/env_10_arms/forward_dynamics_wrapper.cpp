#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "forward_dynamics_robot_arm.h"

namespace py = pybind11;

void forward_dynamics_wrapper(double rho, double radius,
                              py::array_t<double> arm_length,
                              py::array_t<double> joint_axes,
                              py::array_t<double> joint_angles,
                              py::array_t<double> config,
                              py::array_t<double> vel,
                              py::array_t<double> tq,
                              py::array_t<double>& acc_data) {


    // Prepare C++ arrays from the input NumPy arrays
    double arm_length_arr[10], joint_axes_arr[30], joint_angles_arr[10],
           config_arr[10], vel_arr[10], tq_arr[10];
    std::copy(arm_length.data(), arm_length.data() + 10, arm_length_arr);
    std::copy(joint_axes.data(), joint_axes.data() + 30, joint_axes_arr);
    std::copy(joint_angles.data(), joint_angles.data() + 10, joint_angles_arr);
    std::copy(config.data(), config.data() + 10, config_arr);
    std::copy(vel.data(), vel.data() + 10, vel_arr);
    std::copy(tq.data(), tq.data() + 10, tq_arr);

    // Prepare output array for accelerations
    double acc_data_arr[10];
    int acc_size[1] = {10}; // Assuming the size of the acceleration array is known and fixed

    // Call the original C++ function
    forward_dynamics_robot_arm(rho, radius, arm_length_arr, joint_axes_arr, joint_angles_arr,
                               config_arr, vel_arr, tq_arr, acc_data_arr, acc_size);

    // Copy back the acceleration data to the provided NumPy array reference
    std::copy(acc_data_arr, acc_data_arr + acc_size[0], acc_data.mutable_data());
}

PYBIND11_MODULE(forward_dynamics_wrapper, m) {
    m.def("forward_dynamics_robot", &forward_dynamics_wrapper,
          "Wrapper function for calling the forward dynamics of a robot arm",
          py::arg("rho"), py::arg("radius"), py::arg("arm_length"),
          py::arg("joint_axes"), py::arg("joint_angles"), py::arg("config"),
          py::arg("vel"), py::arg("tq"), py::arg("acc_data"));
}
