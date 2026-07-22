#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "scara_robot_2dof_FD.h"
#include "scara_robot_2dof_FD_terminate.h"

namespace py = pybind11;

// Wrap the scara_robot_2dof_FD function for pybind11, assuming it has the same signature
void wrap_scara_robot_2dof_FD(py::array_t<double> q, py::array_t<double> dq, double rho,
                          double radius, py::array_t<double> arm_length,
                          py::array_t<double> torque, py::array_t<double>& joint_acc,
                          py::array_t<double>& pos_tcp) {

    // Verify that each input array has the correct size one by one

    // q should be a 1D array of size 2
    if (q.ndim() != 1)
        throw std::runtime_error("q should be a 1D array");
    if (q.shape(0) != 2)
        throw std::runtime_error("q should have size 2");

    // dq should be a 1D array of size 2
    if (dq.ndim() != 1)
        throw std::runtime_error("dq should be a 1D array");
    if (dq.shape(0) != 2)
        throw std::runtime_error("dq should have size 2");

    // arm_length should be a 1D array of size 2
    if (arm_length.ndim() != 1)
        throw std::runtime_error("arm_length should be a 1D array");
    if (arm_length.shape(0) != 2)
        throw std::runtime_error("arm_length should have size 2");

    // torque should be a 1D array of size 2
    if (torque.ndim() != 1)
        throw std::runtime_error("torque should be a 1D array");
    if (torque.shape(0) != 2)
        throw std::runtime_error("torque should have size 2");

    // Get raw pointers to the data in the numpy arrays
    const double* q_ptr = q.data();
    const double* dq_ptr = dq.data();
    const double* arm_length_ptr = arm_length.data();
    const double* torque_ptr = torque.data();
    double* joint_acc_ptr = joint_acc.mutable_data();
    double* pos_tcp_ptr = pos_tcp.mutable_data();

    // Call the original C++ function
    scara_robot_2dof_FD(q_ptr, dq_ptr, rho, radius, arm_length_ptr, torque_ptr, joint_acc_ptr, pos_tcp_ptr);

    // The output arrays joint_acc and pos_tcp are modified in place
}

PYBIND11_MODULE(scara_robot_2dof_FD_wrapper, m) {
    m.def("scara_robot_2dof_FD", &wrap_scara_robot_2dof_FD, "A function to calculate system matrices and joint accelerations and positions");
}
