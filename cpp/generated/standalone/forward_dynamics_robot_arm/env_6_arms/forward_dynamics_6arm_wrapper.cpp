#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <algorithm> // For std::copy
#include "forward_dynamics_robot_6arm.h" // Make sure this path is correct

namespace py = pybind11;

void forward_dynamics_6arm_wrapper(double rho, double radius,
                                   py::array_t<double> arm_length,
                                   py::array_t<double> joint_axes,
                                   py::array_t<double> joint_angles,
                                   py::array_t<double> config,
                                   py::array_t<double> vel,
                                   py::array_t<double> tq,
                                   py::array_t<double>& acc_data,
                                   py::array_t<double>& link_pos_data) {

    // Prepare C++ arrays from the input NumPy arrays
    double arm_length_arr[6], joint_axes_arr[18], joint_angles_arr[6],
           config_arr[6], vel_arr[6], tq_arr[6];
    std::copy(arm_length.data(), arm_length.data() + 6, arm_length_arr);
    std::copy(joint_axes.data(), joint_axes.data() + 18, joint_axes_arr);
    std::copy(joint_angles.data(), joint_angles.data() + 6, joint_angles_arr);
    std::copy(config.data(), config.data() + 6, config_arr);
    std::copy(vel.data(), vel.data() + 6, vel_arr);
    std::copy(tq.data(), tq.data() + 6, tq_arr);

    // Define the joint_angles_size based on your specific needs
    int joint_angles_size[2] = {/* Determine the correct size here */};

    // Prepare output arrays
    double acc_data_arr[6];
    double linkPositionsArray[18];
    int acc_size[1] = {4};

    // Call the original C++ function
    forward_dynamics_robot_6arm(rho, radius, arm_length_arr, joint_axes_arr, joint_angles_arr,
                                config_arr, vel_arr, tq_arr, acc_data_arr, acc_size, linkPositionsArray);

    // Resize and copy back the acceleration and link position data to the provided NumPy array references
    acc_data.resize({6}); // Resize if necessary
    link_pos_data.resize({18}); // Resize if necessary
    std::copy(acc_data_arr, acc_data_arr + 6, acc_data.mutable_data());
    std::copy(linkPositionsArray, linkPositionsArray + 18, link_pos_data.mutable_data());
}

PYBIND11_MODULE(forward_dynamics_6arm_wrapper, m) {
    m.def("forward_dynamics_robot", &forward_dynamics_6arm_wrapper,
          "Wrapper function for calling the forward dynamics of a robot arm",
          py::arg("rho"), py::arg("radius"), py::arg("arm_length"),
          py::arg("joint_axes"), py::arg("joint_angles"), py::arg("config"),
          py::arg("vel"), py::arg("tq"), py::arg("acc_data"), py::arg("link_pos_data"));
}
