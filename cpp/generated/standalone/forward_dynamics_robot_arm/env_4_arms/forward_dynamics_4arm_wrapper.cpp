#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "forward_dynamics_robot_4arm.h"

namespace py = pybind11;

void forward_dynamics_4arm_wrapper(double rho, double radius,
                              py::array_t<double> arm_length,
                              py::array_t<double> joint_axes,
                              py::array_t<double> joint_angles,
                              py::array_t<double> config,
                              py::array_t<double> vel,
                              py::array_t<double> tq,
                              py::array_t<double>& acc_data) {


    // Prepare C++ arrays from the input NumPy arrays
    double arm_length_arr[4], joint_axes_arr[12], joint_angles_arr[4],
           config_arr[4], vel_arr[4], tq_arr[4];
    std::copy(arm_length.data(), arm_length.data() + 4, arm_length_arr);
    std::copy(joint_axes.data(), joint_axes.data() + 12, joint_axes_arr);
    std::copy(joint_angles.data(), joint_angles.data() + 4, joint_angles_arr);
    std::copy(config.data(), config.data() + 4, config_arr);
    std::copy(vel.data(), vel.data() + 4, vel_arr);
    std::copy(tq.data(), tq.data() + 4, tq_arr);

    // Prepare output array for accelerations
    double acc_data_arr[4];
    int acc_size[1] = {4}; // Assuming the size of the acceleration array is known and fixed

    // Call the original C++ function
    forward_dynamics_robot_4arm(rho, radius, arm_length_arr, joint_axes_arr, joint_angles_arr,
                               config_arr, vel_arr, tq_arr, acc_data_arr, acc_size);

    // Copy back the acceleration data to the provided NumPy array reference
    std::copy(acc_data_arr, acc_data_arr + acc_size[0], acc_data.mutable_data());
}

PYBIND11_MODULE(forward_dynamics_4arm_wrapper, m) {
    m.def("forward_dynamics_robot", &forward_dynamics_4arm_wrapper,
          "Wrapper function for calling the forward dynamics of a robot arm",
          py::arg("rho"), py::arg("radius"), py::arg("arm_length"),
          py::arg("joint_axes"), py::arg("joint_angles"), py::arg("config"),
          py::arg("vel"), py::arg("tq"), py::arg("acc_data"));
}
