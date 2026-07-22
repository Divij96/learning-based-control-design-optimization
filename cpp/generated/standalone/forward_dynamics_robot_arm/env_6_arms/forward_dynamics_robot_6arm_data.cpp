//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: forward_dynamics_robot_6arm_data.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 14-Feb-2024 19:42:36
//

// Include Files
#include "forward_dynamics_robot_6arm_data.h"
#include "rt_nonfinite.h"

// Variable Definitions
unsigned int state[625];

const signed char iv[16]{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

const char cv[10]{'d', 'u', 'm', 'm', 'y', 'b', 'o', 'd', 'y', '1'};

const char cv1[9]{'p', 'r', 'i', 's', 'm', 'a', 't', 'i', 'c'};

const signed char iv1[9]{1, 0, 0, 0, 1, 0, 0, 0, 1};

const char cv2[12]{'e', 'n', 'd', '_', 'e', 'f', 'f', 'e', 'c', 't', 'o', 'r'};

boolean_T isInitialized_forward_dynamics_robot_6arm{false};

//
// File trailer for forward_dynamics_robot_6arm_data.cpp
//
// [EOF]
//
