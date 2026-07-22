cmake_minimum_required(VERSION 3.16)
project(thesis_python_bindings LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/python")

set(PYBIND11_FINDPYTHON ON)
find_package(Python COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

function(add_thesis_binding target source_directory)
  file(GLOB binding_sources CONFIGURE_DEPENDS
    "${source_directory}/*.c"
    "${source_directory}/*.cpp"
  )
  list(FILTER binding_sources EXCLUDE REGEX "/rt_cppclass_main\\.cpp$")
  list(FILTER binding_sources EXCLUDE REGEX "/main\\.cpp$")
  list(FILTER binding_sources EXCLUDE REGEX "/_coder_.*\\.cpp$")

  pybind11_add_module(${target} MODULE ${binding_sources})
  target_include_directories(${target} PRIVATE "${source_directory}")
  target_compile_definitions(${target} PRIVATE MAT_FILE=0)
endfunction()

add_thesis_binding(cartpole_Model_wrapper "${CMAKE_CURRENT_SOURCE_DIR}/cart_pole")
add_thesis_binding(custom_robot_wrapper "${CMAKE_CURRENT_SOURCE_DIR}/custom_robot")
add_thesis_binding(Model_wrapper "${CMAKE_CURRENT_SOURCE_DIR}/quadcopter")
add_thesis_binding(robot_chain_dynamics_wrapper "${CMAKE_CURRENT_SOURCE_DIR}/robot_chain")
add_thesis_binding(scara_robot_2dof_FD_wrapper "${CMAKE_CURRENT_SOURCE_DIR}/scara_2dof_robot")

set(robot_arm_sources "${CMAKE_CURRENT_SOURCE_DIR}/../generated/standalone/forward_dynamics_robot_arm")
add_thesis_binding(forward_dynamics_4arm_wrapper "${robot_arm_sources}/env_4_arms")
add_thesis_binding(forward_dynamics_6arm_wrapper "${robot_arm_sources}/env_6_arms")
add_thesis_binding(forward_dynamics_wrapper "${robot_arm_sources}/env_10_arms")
