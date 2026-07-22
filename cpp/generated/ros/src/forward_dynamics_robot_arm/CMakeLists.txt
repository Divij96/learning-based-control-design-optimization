cmake_minimum_required(VERSION 3.9)
project(forward_dynamics_robot_arm)
set(CMAKE_VERBOSE_MAKEFILE ON)
# Set CMAKE_BUILD_TYPE
set(CMAKE_BUILD_TYPE Release)
# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()
# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()
if(ALIAS_ROS1_CLASS_LOADER)
    add_definitions(-Dclass_loader=ros1_class_loader)
endif()
## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  CATKIN_DEPENDS
  roscpp
  std_msgs
  INCLUDE_DIRS include
)
###########
## Build ##
###########
## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  include
  ${PROJECT_SOURCE_DIR}
  ${Boost_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
  "include/forward_dynamics_robot_arm"
)
set (CMAKE_SKIP_BUILD_RPATH false)
set (CMAKE_BUILD_WITH_INSTALL_RPATH true)
set (CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set (CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
## Get list of .c files in project source directory
file(GLOB ${PROJECT_NAME}_C_SOURCES RELATIVE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/*.c)
## Get list of .cpp files in project source directory
file(GLOB ${PROJECT_NAME}_CPP_SOURCES RELATIVE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/*.cpp)
# Declare library
add_library(
    forward_dynamics_robot_arm
    STATIC
    src/CollisionSet.cpp
    src/RigidBody.cpp
    src/RigidBodyTree1.cpp
    src/RigidBodyTreeDynamics.cpp
    src/axang2tform.cpp
    src/collisionCylinder.cpp
    src/eigStandard.cpp
    src/eml_rand_mt19937ar_stateful.cpp
    src/find.cpp
    src/forward_dynamics_robot_arm.cpp
    src/forward_dynamics_robot_arm_data.cpp
    src/forward_dynamics_robot_arm_initialize.cpp
    src/forward_dynamics_robot_arm_rtwutil.cpp
    src/forward_dynamics_robot_arm_terminate.cpp
    src/insertionsort.cpp
    src/mtimes.cpp
    src/rand.cpp
    src/relop.cpp
    src/rigidBody1.cpp
    src/rigidBodyJoint.cpp
    src/rigidBodyTree.cpp
    src/rtGetInf.cpp
    src/rtGetNaN.cpp
    src/rt_nonfinite.cpp
    src/strcmp.cpp
    src/svd.cpp
    src/trvec2tform.cpp
    src/xdlaev2.cpp
    src/xdlahqr.cpp
    src/xdlanv2.cpp
    src/xdsterf.cpp
    src/xnrm2.cpp
    src/xrotg.cpp
    src/xzgehrd.cpp
    src/xzlarfg.cpp
    src/xzlascl.cpp
    src/ccd_ccd.c
    src/ccd_mpr.c
    src/ccd_polytope.c
    src/ccd_vec3.c
    src/collisioncodegen_CollisionGeometry.cpp
    src/collisioncodegen_api.cpp
    src/collisioncodegen_ccdExtensions.cpp
    src/collisioncodegen_checkCollision.cpp
)
target_include_directories(forward_dynamics_robot_arm PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#target_compile_options(forward_dynamics_robot_arm PUBLIC $<$<OR:$<COMPILE_LANGUAGE:CXX>,$<COMPILE_LANGUAGE:C>>: -Wall -Wextra -Wpedantic>)
endif()
target_compile_options(forward_dynamics_robot_arm PUBLIC
  $<$<OR:$<COMPILE_LANGUAGE:CXX>,$<COMPILE_LANGUAGE:C>>:
  -Dccd_EXPORTS
  -DMODEL=forward_dynamics_robot_arm
  >
  )
## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
add_dependencies(
  forward_dynamics_robot_arm
  ${catkin_EXPORTED_TARGETS}
)
# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(forward_dynamics_robot_arm PRIVATE "FORWARD_DYNAMICS_ROBOT_ARM_BUILDING_LIBRARY")
install(
  DIRECTORY include/
  DESTINATION include
)
install(
  TARGETS forward_dynamics_robot_arm
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
foreach(file_i ${CUDA_BINS})
add_custom_command(
                   TARGET
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND}
                   ARGS -E copy ${PROJECT_SOURCE_DIR}/src/${file_i} ${CATKIN_DEVEL_PREFIX}/codegen/exe//${file_i}
				   )
add_custom_command(
                   TARGET
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND}
                   ARGS -E copy ${PROJECT_SOURCE_DIR}/src/${file_i} ${CATKIN_DEVEL_PREFIX}/_ert_rtw/${file_i}
				   )
endforeach(file_i)
# Generated on Fri Feb 02 13:35:31 2024
