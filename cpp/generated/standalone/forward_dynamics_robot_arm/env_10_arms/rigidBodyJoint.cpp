//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: rigidBodyJoint.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 02-Feb-2024 13:34:01
//

// Include Files
#include "rigidBodyJoint.h"
#include "axang2tform.h"
#include "forward_dynamics_robot_arm_data.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : double ax[3]
// Return Type  : void
//
namespace coder {
void rigidBodyJoint::get_JointAxis(double ax[3]) const
{
  static const char b_cv[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  int exitg1;
  int kstr;
  boolean_T b_bool;
  boolean_T guard1;
  b_bool = false;
  if (Type.size(1) == 8) {
    kstr = 0;
    do {
      exitg1 = 0;
      if (kstr < 8) {
        if (Type[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  guard1 = false;
  if (b_bool) {
    guard1 = true;
  } else {
    b_bool = false;
    if (Type.size(1) == 9) {
      kstr = 0;
      do {
        exitg1 = 0;
        if (kstr < 9) {
          if (Type[kstr] != cv1[kstr]) {
            exitg1 = 1;
          } else {
            kstr++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (b_bool) {
      guard1 = true;
    } else {
      ax[0] = rtNaN;
      ax[1] = rtNaN;
      ax[2] = rtNaN;
    }
  }
  if (guard1) {
    ax[0] = JointAxisInternal[0];
    ax[1] = JointAxisInternal[1];
    ax[2] = JointAxisInternal[2];
  }
}

//
// Arguments    : void
// Return Type  : rigidBodyJoint *
//
rigidBodyJoint *rigidBodyJoint::b_init()
{
  static const char jname[14]{'d', 'u', 'm', 'm', 'y', 'b', 'o',
                              'd', 'y', '1', '_', 'j', 'n', 't'};
  static const char b_cv1[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const signed char b_iv[6]{0, 0, 1, 0, 0, 0};
  static const signed char b_iv1[6]{0, 0, 0, 0, 0, 1};
  static const char b_cv[5]{'f', 'i', 'x', 'e', 'd'};
  rigidBodyJoint *obj;
  array<char, 2U> switch_expression;
  double poslim_data[12];
  int exitg1;
  int loop_ub;
  signed char msubspace_data[36];
  boolean_T b_bool;
  obj = this;
  obj->InTree = false;
  for (int i{0}; i < 16; i++) {
    obj->JointToParentTransform[i] = iv[i];
  }
  for (int i{0}; i < 16; i++) {
    obj->ChildToJointTransform[i] = iv[i];
  }
  obj->NameInternal.set_size(1, 14);
  for (int i{0}; i < 14; i++) {
    obj->NameInternal[i] = jname[i];
  }
  obj->Type.set_size(1, 5);
  for (int i{0}; i < 5; i++) {
    obj->Type[i] = b_cv[i];
  }
  switch_expression.set_size(1, obj->Type.size(1));
  loop_ub = obj->Type.size(1);
  for (int i{0}; i < loop_ub; i++) {
    switch_expression[i] = obj->Type[i];
  }
  b_bool = false;
  if (switch_expression.size(1) == 8) {
    loop_ub = 0;
    do {
      exitg1 = 0;
      if (loop_ub < 8) {
        if (switch_expression[loop_ub] != b_cv1[loop_ub]) {
          exitg1 = 1;
        } else {
          loop_ub++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (b_bool) {
    loop_ub = 0;
  } else {
    b_bool = false;
    if (switch_expression.size(1) == 9) {
      loop_ub = 0;
      do {
        exitg1 = 0;
        if (loop_ub < 9) {
          if (switch_expression[loop_ub] != cv1[loop_ub]) {
            exitg1 = 1;
          } else {
            loop_ub++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (b_bool) {
      loop_ub = 1;
    } else {
      loop_ub = -1;
    }
  }
  switch (loop_ub) {
  case 0:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv[i];
    }
    poslim_data[0] = -3.1415926535897931;
    poslim_data[1] = 3.1415926535897931;
    obj->VelocityNumber = 1.0;
    obj->PositionNumber = 1.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    obj->VelocityNumber = 1.0;
    obj->PositionNumber = 1.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 1.0;
    break;
  default:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    obj->VelocityNumber = 0.0;
    obj->PositionNumber = 0.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 0.0;
    break;
  }
  obj->MotionSubspace.set_size(6, 1);
  for (int i{0}; i < 6; i++) {
    obj->MotionSubspace[i] = msubspace_data[i];
  }
  obj->PositionLimitsInternal.set_size(1, 2);
  for (int i{0}; i < 2; i++) {
    obj->PositionLimitsInternal[i] = poslim_data[i];
  }
  obj->HomePositionInternal.set_size(1);
  obj->HomePositionInternal[0] = 0.0;
  return obj;
}

//
// Arguments    : void
// Return Type  : rigidBodyJoint *
//
rigidBodyJoint *rigidBodyJoint::c_init()
{
  static const char b[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const char b_cv[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const signed char b_iv[6]{0, 0, 1, 0, 0, 0};
  static const signed char b_iv1[6]{0, 0, 0, 0, 0, 1};
  rigidBodyJoint *obj;
  array<char, 2U> switch_expression;
  double poslim_data[12];
  int exitg1;
  int loop_ub;
  signed char msubspace_data[36];
  boolean_T b_bool;
  obj = this;
  obj->InTree = false;
  for (int i{0}; i < 16; i++) {
    obj->JointToParentTransform[i] = iv[i];
  }
  for (int i{0}; i < 16; i++) {
    obj->ChildToJointTransform[i] = iv[i];
  }
  obj->NameInternal.set_size(1, 4);
  obj->NameInternal[0] = 'j';
  obj->NameInternal[1] = 'n';
  obj->NameInternal[2] = 't';
  obj->NameInternal[3] = '1';
  obj->Type.set_size(1, 8);
  for (int i{0}; i < 8; i++) {
    obj->Type[i] = b[i];
  }
  switch_expression.set_size(1, obj->Type.size(1));
  loop_ub = obj->Type.size(1);
  for (int i{0}; i < loop_ub; i++) {
    switch_expression[i] = obj->Type[i];
  }
  b_bool = false;
  if (switch_expression.size(1) == 8) {
    loop_ub = 0;
    do {
      exitg1 = 0;
      if (loop_ub < 8) {
        if (switch_expression[loop_ub] != b_cv[loop_ub]) {
          exitg1 = 1;
        } else {
          loop_ub++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (b_bool) {
    loop_ub = 0;
  } else {
    b_bool = false;
    if (switch_expression.size(1) == 9) {
      loop_ub = 0;
      do {
        exitg1 = 0;
        if (loop_ub < 9) {
          if (switch_expression[loop_ub] != cv1[loop_ub]) {
            exitg1 = 1;
          } else {
            loop_ub++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (b_bool) {
      loop_ub = 1;
    } else {
      loop_ub = -1;
    }
  }
  switch (loop_ub) {
  case 0:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv[i];
    }
    poslim_data[0] = -3.1415926535897931;
    poslim_data[1] = 3.1415926535897931;
    obj->VelocityNumber = 1.0;
    obj->PositionNumber = 1.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    obj->VelocityNumber = 1.0;
    obj->PositionNumber = 1.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 1.0;
    break;
  default:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    obj->VelocityNumber = 0.0;
    obj->PositionNumber = 0.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 0.0;
    break;
  }
  obj->MotionSubspace.set_size(6, 1);
  for (int i{0}; i < 6; i++) {
    obj->MotionSubspace[i] = msubspace_data[i];
  }
  obj->PositionLimitsInternal.set_size(1, 2);
  for (int i{0}; i < 2; i++) {
    obj->PositionLimitsInternal[i] = poslim_data[i];
  }
  obj->HomePositionInternal.set_size(1);
  obj->HomePositionInternal[0] = 0.0;
  return obj;
}

//
// Arguments    : rigidBodyJoint &iobj_0
// Return Type  : rigidBodyJoint *
//
rigidBodyJoint *rigidBodyJoint::copy(rigidBodyJoint &iobj_0) const
{
  static const char b_cv[128]{
      '\x00', '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\a',   '\b',
      '\t',   '\n',   '\v',   '\f',   '\r',   '\x0e', '\x0f', '\x10', '\x11',
      '\x12', '\x13', '\x14', '\x15', '\x16', '\x17', '\x18', '\x19', '\x1a',
      '\x1b', '\x1c', '\x1d', '\x1e', '\x1f', ' ',    '!',    '\"',   '#',
      '$',    '%',    '&',    '\'',   '(',    ')',    '*',    '+',    ',',
      '-',    '.',    '/',    '0',    '1',    '2',    '3',    '4',    '5',
      '6',    '7',    '8',    '9',    ':',    ';',    '<',    '=',    '>',
      '?',    '@',    'a',    'b',    'c',    'd',    'e',    'f',    'g',
      'h',    'i',    'j',    'k',    'l',    'm',    'n',    'o',    'p',
      'q',    'r',    's',    't',    'u',    'v',    'w',    'x',    'y',
      'z',    '[',    '\\',   ']',    '^',    '_',    '`',    'a',    'b',
      'c',    'd',    'e',    'f',    'g',    'h',    'i',    'j',    'k',
      'l',    'm',    'n',    'o',    'p',    'q',    'r',    's',    't',
      'u',    'v',    'w',    'x',    'y',    'z',    '{',    '|',    '}',
      '~',    '\x7f'};
  static const char b_cv1[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const char vstr[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const signed char b_iv[6]{0, 0, 1, 0, 0, 0};
  static const signed char b_iv1[6]{0, 0, 0, 0, 0, 1};
  static const char b_vstr[5]{'f', 'i', 'x', 'e', 'd'};
  static const char cv2[5]{'f', 'i', 'x', 'e', 'd'};
  rigidBodyJoint *newjoint;
  array<double, 1U> obj;
  array<char, 2U> jname;
  array<char, 2U> jtype;
  double b_obj[16];
  double poslim_data[12];
  int exitg1;
  int jointtype_size_idx_1;
  int kstr;
  int lenstr;
  int minnanb;
  int nmatched;
  int partial_match_size_idx_1;
  signed char msubspace_data[36];
  char jointtype_data[9];
  char partial_match_data[9];
  boolean_T b_bool;
  boolean_T b_guard1;
  boolean_T guard1;
  boolean_T guard2;
  boolean_T guard3;
  boolean_T matched;
  jtype.set_size(1, Type.size(1));
  minnanb = Type.size(1);
  for (kstr = 0; kstr < minnanb; kstr++) {
    jtype[kstr] = Type[kstr];
  }
  jname.set_size(1, NameInternal.size(1));
  minnanb = NameInternal.size(1);
  for (kstr = 0; kstr < minnanb; kstr++) {
    jname[kstr] = NameInternal[kstr];
  }
  newjoint = &iobj_0;
  iobj_0.InTree = false;
  for (kstr = 0; kstr < 16; kstr++) {
    iobj_0.JointToParentTransform[kstr] = iv[kstr];
  }
  for (kstr = 0; kstr < 16; kstr++) {
    iobj_0.ChildToJointTransform[kstr] = iv[kstr];
  }
  iobj_0.NameInternal.set_size(1, jname.size(1));
  minnanb = jname.size(1);
  for (kstr = 0; kstr < minnanb; kstr++) {
    iobj_0.NameInternal[kstr] = jname[kstr];
  }
  partial_match_size_idx_1 = 8;
  for (kstr = 0; kstr < 8; kstr++) {
    partial_match_data[kstr] = ' ';
  }
  lenstr = jtype.size(1);
  nmatched = 0;
  matched = false;
  guard1 = false;
  guard2 = false;
  guard3 = false;
  if (jtype.size(1) <= 8) {
    b_bool = false;
    minnanb = jtype.size(1);
    b_guard1 = false;
    if (lenstr <= minnanb) {
      if (minnanb > lenstr) {
        minnanb = lenstr;
      }
      b_guard1 = true;
    } else if (jtype.size(1) == 8) {
      minnanb = 8;
      b_guard1 = true;
    }
    if (b_guard1) {
      kstr = 0;
      do {
        exitg1 = 0;
        if (kstr <= minnanb - 1) {
          if (b_cv[static_cast<unsigned char>(jtype[kstr]) & 127] !=
              b_cv[static_cast<int>(b_cv1[kstr])]) {
            exitg1 = 1;
          } else {
            kstr++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (b_bool) {
      if (jtype.size(1) == 8) {
        nmatched = 1;
        for (kstr = 0; kstr < 8; kstr++) {
          partial_match_data[kstr] = vstr[kstr];
        }
      } else {
        for (kstr = 0; kstr < 8; kstr++) {
          partial_match_data[kstr] = vstr[kstr];
        }
        matched = true;
        nmatched = 1;
        guard3 = true;
      }
    } else {
      guard3 = true;
    }
  } else {
    guard3 = true;
  }
  if (guard3) {
    if (jtype.size(1) <= 9) {
      b_bool = false;
      minnanb = jtype.size(1);
      b_guard1 = false;
      if (lenstr <= minnanb) {
        if (minnanb > lenstr) {
          minnanb = lenstr;
        }
        b_guard1 = true;
      } else if (jtype.size(1) == 9) {
        minnanb = 9;
        b_guard1 = true;
      }
      if (b_guard1) {
        kstr = 0;
        do {
          exitg1 = 0;
          if (kstr <= minnanb - 1) {
            if (b_cv[static_cast<unsigned char>(jtype[kstr]) & 127] !=
                b_cv[static_cast<int>(cv1[kstr])]) {
              exitg1 = 1;
            } else {
              kstr++;
            }
          } else {
            b_bool = true;
            exitg1 = 1;
          }
        } while (exitg1 == 0);
      }
      if (b_bool) {
        if (jtype.size(1) == 9) {
          nmatched = 1;
          partial_match_size_idx_1 = 9;
          for (kstr = 0; kstr < 9; kstr++) {
            partial_match_data[kstr] = cv1[kstr];
          }
        } else {
          if (!matched) {
            partial_match_size_idx_1 = 9;
            for (kstr = 0; kstr < 9; kstr++) {
              partial_match_data[kstr] = cv1[kstr];
            }
          }
          matched = true;
          nmatched++;
          guard2 = true;
        }
      } else {
        guard2 = true;
      }
    } else {
      guard2 = true;
    }
  }
  if (guard2) {
    if (jtype.size(1) <= 5) {
      b_bool = false;
      minnanb = jtype.size(1);
      b_guard1 = false;
      if (lenstr <= minnanb) {
        if (minnanb <= lenstr) {
          lenstr = minnanb;
        }
        b_guard1 = true;
      } else if (jtype.size(1) == 5) {
        lenstr = 5;
        b_guard1 = true;
      }
      if (b_guard1) {
        kstr = 0;
        do {
          exitg1 = 0;
          if (kstr <= lenstr - 1) {
            if (b_cv[static_cast<unsigned char>(jtype[kstr]) & 127] !=
                b_cv[static_cast<int>(cv2[kstr])]) {
              exitg1 = 1;
            } else {
              kstr++;
            }
          } else {
            b_bool = true;
            exitg1 = 1;
          }
        } while (exitg1 == 0);
      }
      if (b_bool) {
        if (jtype.size(1) == 5) {
          nmatched = 1;
          partial_match_size_idx_1 = 5;
          for (kstr = 0; kstr < 5; kstr++) {
            partial_match_data[kstr] = b_vstr[kstr];
          }
        } else {
          if (!matched) {
            partial_match_size_idx_1 = 5;
            for (kstr = 0; kstr < 5; kstr++) {
              partial_match_data[kstr] = b_vstr[kstr];
            }
          }
          nmatched++;
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }
  }
  if (guard1 && (nmatched == 0)) {
    partial_match_size_idx_1 = 8;
    for (kstr = 0; kstr < 8; kstr++) {
      partial_match_data[kstr] = ' ';
    }
  }
  if ((nmatched == 0) || (jtype.size(1) == 0)) {
    jointtype_size_idx_1 = 8;
    for (kstr = 0; kstr < 8; kstr++) {
      jointtype_data[kstr] = ' ';
    }
  } else if (nmatched <= 1) {
    jointtype_size_idx_1 = partial_match_size_idx_1;
    ::std::copy(&partial_match_data[0],
                &partial_match_data[partial_match_size_idx_1],
                &jointtype_data[0]);
  }
  iobj_0.Type.set_size(1, jointtype_size_idx_1);
  for (kstr = 0; kstr < jointtype_size_idx_1; kstr++) {
    iobj_0.Type[kstr] = jointtype_data[kstr];
  }
  jtype.set_size(1, iobj_0.Type.size(1));
  minnanb = iobj_0.Type.size(1);
  for (kstr = 0; kstr < minnanb; kstr++) {
    jtype[kstr] = iobj_0.Type[kstr];
  }
  b_bool = false;
  if (jtype.size(1) == 8) {
    kstr = 0;
    do {
      exitg1 = 0;
      if (kstr < 8) {
        if (jtype[kstr] != b_cv1[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (b_bool) {
    minnanb = 0;
  } else {
    b_bool = false;
    if (jtype.size(1) == 9) {
      kstr = 0;
      do {
        exitg1 = 0;
        if (kstr < 9) {
          if (jtype[kstr] != cv1[kstr]) {
            exitg1 = 1;
          } else {
            kstr++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (b_bool) {
      minnanb = 1;
    } else {
      minnanb = -1;
    }
  }
  switch (minnanb) {
  case 0:
    for (kstr = 0; kstr < 6; kstr++) {
      msubspace_data[kstr] = b_iv[kstr];
    }
    poslim_data[0] = -3.1415926535897931;
    poslim_data[1] = 3.1415926535897931;
    iobj_0.VelocityNumber = 1.0;
    iobj_0.PositionNumber = 1.0;
    iobj_0.JointAxisInternal[0] = 0.0;
    iobj_0.JointAxisInternal[1] = 0.0;
    iobj_0.JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (kstr = 0; kstr < 6; kstr++) {
      msubspace_data[kstr] = b_iv1[kstr];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    iobj_0.VelocityNumber = 1.0;
    iobj_0.PositionNumber = 1.0;
    iobj_0.JointAxisInternal[0] = 0.0;
    iobj_0.JointAxisInternal[1] = 0.0;
    iobj_0.JointAxisInternal[2] = 1.0;
    break;
  default:
    for (kstr = 0; kstr < 6; kstr++) {
      msubspace_data[kstr] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    iobj_0.VelocityNumber = 0.0;
    iobj_0.PositionNumber = 0.0;
    iobj_0.JointAxisInternal[0] = 0.0;
    iobj_0.JointAxisInternal[1] = 0.0;
    iobj_0.JointAxisInternal[2] = 0.0;
    break;
  }
  iobj_0.MotionSubspace.set_size(6, 1);
  for (kstr = 0; kstr < 6; kstr++) {
    iobj_0.MotionSubspace[kstr] = msubspace_data[kstr];
  }
  iobj_0.PositionLimitsInternal.set_size(1, 2);
  for (kstr = 0; kstr < 2; kstr++) {
    iobj_0.PositionLimitsInternal[kstr] = poslim_data[kstr];
  }
  iobj_0.HomePositionInternal.set_size(1);
  iobj_0.HomePositionInternal[0] = 0.0;
  minnanb = NameInternal.size(1);
  if (minnanb != 0) {
    jtype.set_size(1, NameInternal.size(1));
    minnanb = NameInternal.size(1);
    for (kstr = 0; kstr < minnanb; kstr++) {
      jtype[kstr] = NameInternal[kstr];
    }
    if (!iobj_0.InTree) {
      iobj_0.NameInternal.set_size(1, jtype.size(1));
      minnanb = jtype.size(1);
      for (kstr = 0; kstr < minnanb; kstr++) {
        iobj_0.NameInternal[kstr] = jtype[kstr];
      }
    }
  }
  minnanb = PositionLimitsInternal.size(0) << 1;
  iobj_0.PositionLimitsInternal.set_size(PositionLimitsInternal.size(0), 2);
  obj.set_size(minnanb);
  for (kstr = 0; kstr < minnanb; kstr++) {
    obj[kstr] = PositionLimitsInternal[kstr];
  }
  minnanb = obj.size(0);
  for (kstr = 0; kstr < minnanb; kstr++) {
    iobj_0.PositionLimitsInternal[kstr] = obj[kstr];
  }
  obj.set_size(HomePositionInternal.size(0));
  minnanb = HomePositionInternal.size(0);
  for (kstr = 0; kstr < minnanb; kstr++) {
    obj[kstr] = HomePositionInternal[kstr];
  }
  iobj_0.HomePositionInternal.set_size(obj.size(0));
  minnanb = obj.size(0);
  for (kstr = 0; kstr < minnanb; kstr++) {
    iobj_0.HomePositionInternal[kstr] = obj[kstr];
  }
  double obj_idx_0;
  double obj_idx_1;
  double obj_idx_2;
  obj_idx_0 = JointAxisInternal[0];
  obj_idx_1 = JointAxisInternal[1];
  obj_idx_2 = JointAxisInternal[2];
  iobj_0.JointAxisInternal[0] = obj_idx_0;
  iobj_0.JointAxisInternal[1] = obj_idx_1;
  iobj_0.JointAxisInternal[2] = obj_idx_2;
  minnanb = 6 * MotionSubspace.size(1);
  iobj_0.MotionSubspace.set_size(6, MotionSubspace.size(1));
  obj.set_size(minnanb);
  for (kstr = 0; kstr < minnanb; kstr++) {
    obj[kstr] = MotionSubspace[kstr];
  }
  minnanb = obj.size(0);
  for (kstr = 0; kstr < minnanb; kstr++) {
    iobj_0.MotionSubspace[kstr] = obj[kstr];
  }
  for (kstr = 0; kstr < 16; kstr++) {
    b_obj[kstr] = JointToParentTransform[kstr];
  }
  for (kstr = 0; kstr < 16; kstr++) {
    iobj_0.JointToParentTransform[kstr] = b_obj[kstr];
  }
  for (kstr = 0; kstr < 16; kstr++) {
    b_obj[kstr] = ChildToJointTransform[kstr];
  }
  for (kstr = 0; kstr < 16; kstr++) {
    iobj_0.ChildToJointTransform[kstr] = b_obj[kstr];
  }
  return newjoint;
}

//
// Arguments    : void
// Return Type  : rigidBodyJoint *
//
rigidBodyJoint *rigidBodyJoint::d_init()
{
  static const char b[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const char b_cv[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const signed char b_iv[6]{0, 0, 1, 0, 0, 0};
  static const signed char b_iv1[6]{0, 0, 0, 0, 0, 1};
  rigidBodyJoint *obj;
  array<char, 2U> switch_expression;
  double poslim_data[12];
  int exitg1;
  int loop_ub;
  signed char msubspace_data[36];
  boolean_T b_bool;
  obj = this;
  obj->InTree = false;
  for (int i{0}; i < 16; i++) {
    obj->JointToParentTransform[i] = iv[i];
  }
  for (int i{0}; i < 16; i++) {
    obj->ChildToJointTransform[i] = iv[i];
  }
  obj->NameInternal.set_size(1, 4);
  obj->NameInternal[0] = 'j';
  obj->NameInternal[1] = 'n';
  obj->NameInternal[2] = 't';
  obj->NameInternal[3] = '2';
  obj->Type.set_size(1, 8);
  for (int i{0}; i < 8; i++) {
    obj->Type[i] = b[i];
  }
  switch_expression.set_size(1, obj->Type.size(1));
  loop_ub = obj->Type.size(1);
  for (int i{0}; i < loop_ub; i++) {
    switch_expression[i] = obj->Type[i];
  }
  b_bool = false;
  if (switch_expression.size(1) == 8) {
    loop_ub = 0;
    do {
      exitg1 = 0;
      if (loop_ub < 8) {
        if (switch_expression[loop_ub] != b_cv[loop_ub]) {
          exitg1 = 1;
        } else {
          loop_ub++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (b_bool) {
    loop_ub = 0;
  } else {
    b_bool = false;
    if (switch_expression.size(1) == 9) {
      loop_ub = 0;
      do {
        exitg1 = 0;
        if (loop_ub < 9) {
          if (switch_expression[loop_ub] != cv1[loop_ub]) {
            exitg1 = 1;
          } else {
            loop_ub++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (b_bool) {
      loop_ub = 1;
    } else {
      loop_ub = -1;
    }
  }
  switch (loop_ub) {
  case 0:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv[i];
    }
    poslim_data[0] = -3.1415926535897931;
    poslim_data[1] = 3.1415926535897931;
    obj->VelocityNumber = 1.0;
    obj->PositionNumber = 1.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    obj->VelocityNumber = 1.0;
    obj->PositionNumber = 1.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 1.0;
    break;
  default:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    obj->VelocityNumber = 0.0;
    obj->PositionNumber = 0.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 0.0;
    break;
  }
  obj->MotionSubspace.set_size(6, 1);
  for (int i{0}; i < 6; i++) {
    obj->MotionSubspace[i] = msubspace_data[i];
  }
  obj->PositionLimitsInternal.set_size(1, 2);
  for (int i{0}; i < 2; i++) {
    obj->PositionLimitsInternal[i] = poslim_data[i];
  }
  obj->HomePositionInternal.set_size(1);
  obj->HomePositionInternal[0] = 0.0;
  return obj;
}

//
// Arguments    : void
// Return Type  : rigidBodyJoint *
//
rigidBodyJoint *rigidBodyJoint::e_init()
{
  static const char b[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const char b_cv[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const signed char b_iv[6]{0, 0, 1, 0, 0, 0};
  static const signed char b_iv1[6]{0, 0, 0, 0, 0, 1};
  rigidBodyJoint *obj;
  array<char, 2U> switch_expression;
  double poslim_data[12];
  int exitg1;
  int loop_ub;
  signed char msubspace_data[36];
  boolean_T b_bool;
  obj = this;
  obj->InTree = false;
  for (int i{0}; i < 16; i++) {
    obj->JointToParentTransform[i] = iv[i];
  }
  for (int i{0}; i < 16; i++) {
    obj->ChildToJointTransform[i] = iv[i];
  }
  obj->NameInternal.set_size(1, 4);
  obj->NameInternal[0] = 'j';
  obj->NameInternal[1] = 'n';
  obj->NameInternal[2] = 't';
  obj->NameInternal[3] = '3';
  obj->Type.set_size(1, 8);
  for (int i{0}; i < 8; i++) {
    obj->Type[i] = b[i];
  }
  switch_expression.set_size(1, obj->Type.size(1));
  loop_ub = obj->Type.size(1);
  for (int i{0}; i < loop_ub; i++) {
    switch_expression[i] = obj->Type[i];
  }
  b_bool = false;
  if (switch_expression.size(1) == 8) {
    loop_ub = 0;
    do {
      exitg1 = 0;
      if (loop_ub < 8) {
        if (switch_expression[loop_ub] != b_cv[loop_ub]) {
          exitg1 = 1;
        } else {
          loop_ub++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (b_bool) {
    loop_ub = 0;
  } else {
    b_bool = false;
    if (switch_expression.size(1) == 9) {
      loop_ub = 0;
      do {
        exitg1 = 0;
        if (loop_ub < 9) {
          if (switch_expression[loop_ub] != cv1[loop_ub]) {
            exitg1 = 1;
          } else {
            loop_ub++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (b_bool) {
      loop_ub = 1;
    } else {
      loop_ub = -1;
    }
  }
  switch (loop_ub) {
  case 0:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv[i];
    }
    poslim_data[0] = -3.1415926535897931;
    poslim_data[1] = 3.1415926535897931;
    obj->VelocityNumber = 1.0;
    obj->PositionNumber = 1.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    obj->VelocityNumber = 1.0;
    obj->PositionNumber = 1.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 1.0;
    break;
  default:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    obj->VelocityNumber = 0.0;
    obj->PositionNumber = 0.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 0.0;
    break;
  }
  obj->MotionSubspace.set_size(6, 1);
  for (int i{0}; i < 6; i++) {
    obj->MotionSubspace[i] = msubspace_data[i];
  }
  obj->PositionLimitsInternal.set_size(1, 2);
  for (int i{0}; i < 2; i++) {
    obj->PositionLimitsInternal[i] = poslim_data[i];
  }
  obj->HomePositionInternal.set_size(1);
  obj->HomePositionInternal[0] = 0.0;
  return obj;
}

//
// Arguments    : void
// Return Type  : rigidBodyJoint *
//
rigidBodyJoint *rigidBodyJoint::f_init()
{
  static const char b[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const char b_cv[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const signed char b_iv[6]{0, 0, 1, 0, 0, 0};
  static const signed char b_iv1[6]{0, 0, 0, 0, 0, 1};
  rigidBodyJoint *obj;
  array<char, 2U> switch_expression;
  double poslim_data[12];
  int exitg1;
  int loop_ub;
  signed char msubspace_data[36];
  boolean_T b_bool;
  obj = this;
  obj->InTree = false;
  for (int i{0}; i < 16; i++) {
    obj->JointToParentTransform[i] = iv[i];
  }
  for (int i{0}; i < 16; i++) {
    obj->ChildToJointTransform[i] = iv[i];
  }
  obj->NameInternal.set_size(1, 4);
  obj->NameInternal[0] = 'j';
  obj->NameInternal[1] = 'n';
  obj->NameInternal[2] = 't';
  obj->NameInternal[3] = '4';
  obj->Type.set_size(1, 8);
  for (int i{0}; i < 8; i++) {
    obj->Type[i] = b[i];
  }
  switch_expression.set_size(1, obj->Type.size(1));
  loop_ub = obj->Type.size(1);
  for (int i{0}; i < loop_ub; i++) {
    switch_expression[i] = obj->Type[i];
  }
  b_bool = false;
  if (switch_expression.size(1) == 8) {
    loop_ub = 0;
    do {
      exitg1 = 0;
      if (loop_ub < 8) {
        if (switch_expression[loop_ub] != b_cv[loop_ub]) {
          exitg1 = 1;
        } else {
          loop_ub++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (b_bool) {
    loop_ub = 0;
  } else {
    b_bool = false;
    if (switch_expression.size(1) == 9) {
      loop_ub = 0;
      do {
        exitg1 = 0;
        if (loop_ub < 9) {
          if (switch_expression[loop_ub] != cv1[loop_ub]) {
            exitg1 = 1;
          } else {
            loop_ub++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (b_bool) {
      loop_ub = 1;
    } else {
      loop_ub = -1;
    }
  }
  switch (loop_ub) {
  case 0:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv[i];
    }
    poslim_data[0] = -3.1415926535897931;
    poslim_data[1] = 3.1415926535897931;
    obj->VelocityNumber = 1.0;
    obj->PositionNumber = 1.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    obj->VelocityNumber = 1.0;
    obj->PositionNumber = 1.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 1.0;
    break;
  default:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    obj->VelocityNumber = 0.0;
    obj->PositionNumber = 0.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 0.0;
    break;
  }
  obj->MotionSubspace.set_size(6, 1);
  for (int i{0}; i < 6; i++) {
    obj->MotionSubspace[i] = msubspace_data[i];
  }
  obj->PositionLimitsInternal.set_size(1, 2);
  for (int i{0}; i < 2; i++) {
    obj->PositionLimitsInternal[i] = poslim_data[i];
  }
  obj->HomePositionInternal.set_size(1);
  obj->HomePositionInternal[0] = 0.0;
  return obj;
}

//
// Arguments    : void
// Return Type  : rigidBodyJoint *
//
rigidBodyJoint *rigidBodyJoint::g_init()
{
  static const char b[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const char b_cv[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const signed char b_iv[6]{0, 0, 1, 0, 0, 0};
  static const signed char b_iv1[6]{0, 0, 0, 0, 0, 1};
  rigidBodyJoint *obj;
  array<char, 2U> switch_expression;
  double poslim_data[12];
  int exitg1;
  int loop_ub;
  signed char msubspace_data[36];
  boolean_T b_bool;
  obj = this;
  obj->InTree = false;
  for (int i{0}; i < 16; i++) {
    obj->JointToParentTransform[i] = iv[i];
  }
  for (int i{0}; i < 16; i++) {
    obj->ChildToJointTransform[i] = iv[i];
  }
  obj->NameInternal.set_size(1, 4);
  obj->NameInternal[0] = 'j';
  obj->NameInternal[1] = 'n';
  obj->NameInternal[2] = 't';
  obj->NameInternal[3] = '5';
  obj->Type.set_size(1, 8);
  for (int i{0}; i < 8; i++) {
    obj->Type[i] = b[i];
  }
  switch_expression.set_size(1, obj->Type.size(1));
  loop_ub = obj->Type.size(1);
  for (int i{0}; i < loop_ub; i++) {
    switch_expression[i] = obj->Type[i];
  }
  b_bool = false;
  if (switch_expression.size(1) == 8) {
    loop_ub = 0;
    do {
      exitg1 = 0;
      if (loop_ub < 8) {
        if (switch_expression[loop_ub] != b_cv[loop_ub]) {
          exitg1 = 1;
        } else {
          loop_ub++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (b_bool) {
    loop_ub = 0;
  } else {
    b_bool = false;
    if (switch_expression.size(1) == 9) {
      loop_ub = 0;
      do {
        exitg1 = 0;
        if (loop_ub < 9) {
          if (switch_expression[loop_ub] != cv1[loop_ub]) {
            exitg1 = 1;
          } else {
            loop_ub++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (b_bool) {
      loop_ub = 1;
    } else {
      loop_ub = -1;
    }
  }
  switch (loop_ub) {
  case 0:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv[i];
    }
    poslim_data[0] = -3.1415926535897931;
    poslim_data[1] = 3.1415926535897931;
    obj->VelocityNumber = 1.0;
    obj->PositionNumber = 1.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    obj->VelocityNumber = 1.0;
    obj->PositionNumber = 1.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 1.0;
    break;
  default:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    obj->VelocityNumber = 0.0;
    obj->PositionNumber = 0.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 0.0;
    break;
  }
  obj->MotionSubspace.set_size(6, 1);
  for (int i{0}; i < 6; i++) {
    obj->MotionSubspace[i] = msubspace_data[i];
  }
  obj->PositionLimitsInternal.set_size(1, 2);
  for (int i{0}; i < 2; i++) {
    obj->PositionLimitsInternal[i] = poslim_data[i];
  }
  obj->HomePositionInternal.set_size(1);
  obj->HomePositionInternal[0] = 0.0;
  return obj;
}

//
// Arguments    : void
// Return Type  : rigidBodyJoint *
//
rigidBodyJoint *rigidBodyJoint::h_init()
{
  static const char b[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const char b_cv[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const signed char b_iv[6]{0, 0, 1, 0, 0, 0};
  static const signed char b_iv1[6]{0, 0, 0, 0, 0, 1};
  rigidBodyJoint *obj;
  array<char, 2U> switch_expression;
  double poslim_data[12];
  int exitg1;
  int loop_ub;
  signed char msubspace_data[36];
  boolean_T b_bool;
  obj = this;
  obj->InTree = false;
  for (int i{0}; i < 16; i++) {
    obj->JointToParentTransform[i] = iv[i];
  }
  for (int i{0}; i < 16; i++) {
    obj->ChildToJointTransform[i] = iv[i];
  }
  obj->NameInternal.set_size(1, 4);
  obj->NameInternal[0] = 'j';
  obj->NameInternal[1] = 'n';
  obj->NameInternal[2] = 't';
  obj->NameInternal[3] = '6';
  obj->Type.set_size(1, 8);
  for (int i{0}; i < 8; i++) {
    obj->Type[i] = b[i];
  }
  switch_expression.set_size(1, obj->Type.size(1));
  loop_ub = obj->Type.size(1);
  for (int i{0}; i < loop_ub; i++) {
    switch_expression[i] = obj->Type[i];
  }
  b_bool = false;
  if (switch_expression.size(1) == 8) {
    loop_ub = 0;
    do {
      exitg1 = 0;
      if (loop_ub < 8) {
        if (switch_expression[loop_ub] != b_cv[loop_ub]) {
          exitg1 = 1;
        } else {
          loop_ub++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (b_bool) {
    loop_ub = 0;
  } else {
    b_bool = false;
    if (switch_expression.size(1) == 9) {
      loop_ub = 0;
      do {
        exitg1 = 0;
        if (loop_ub < 9) {
          if (switch_expression[loop_ub] != cv1[loop_ub]) {
            exitg1 = 1;
          } else {
            loop_ub++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (b_bool) {
      loop_ub = 1;
    } else {
      loop_ub = -1;
    }
  }
  switch (loop_ub) {
  case 0:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv[i];
    }
    poslim_data[0] = -3.1415926535897931;
    poslim_data[1] = 3.1415926535897931;
    obj->VelocityNumber = 1.0;
    obj->PositionNumber = 1.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    obj->VelocityNumber = 1.0;
    obj->PositionNumber = 1.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 1.0;
    break;
  default:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    obj->VelocityNumber = 0.0;
    obj->PositionNumber = 0.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 0.0;
    break;
  }
  obj->MotionSubspace.set_size(6, 1);
  for (int i{0}; i < 6; i++) {
    obj->MotionSubspace[i] = msubspace_data[i];
  }
  obj->PositionLimitsInternal.set_size(1, 2);
  for (int i{0}; i < 2; i++) {
    obj->PositionLimitsInternal[i] = poslim_data[i];
  }
  obj->HomePositionInternal.set_size(1);
  obj->HomePositionInternal[0] = 0.0;
  return obj;
}

//
// Arguments    : void
// Return Type  : rigidBodyJoint *
//
rigidBodyJoint *rigidBodyJoint::i_init()
{
  static const char b[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const char b_cv[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const signed char b_iv[6]{0, 0, 1, 0, 0, 0};
  static const signed char b_iv1[6]{0, 0, 0, 0, 0, 1};
  rigidBodyJoint *obj;
  array<char, 2U> switch_expression;
  double poslim_data[12];
  int exitg1;
  int loop_ub;
  signed char msubspace_data[36];
  boolean_T b_bool;
  obj = this;
  obj->InTree = false;
  for (int i{0}; i < 16; i++) {
    obj->JointToParentTransform[i] = iv[i];
  }
  for (int i{0}; i < 16; i++) {
    obj->ChildToJointTransform[i] = iv[i];
  }
  obj->NameInternal.set_size(1, 4);
  obj->NameInternal[0] = 'j';
  obj->NameInternal[1] = 'n';
  obj->NameInternal[2] = 't';
  obj->NameInternal[3] = '7';
  obj->Type.set_size(1, 8);
  for (int i{0}; i < 8; i++) {
    obj->Type[i] = b[i];
  }
  switch_expression.set_size(1, obj->Type.size(1));
  loop_ub = obj->Type.size(1);
  for (int i{0}; i < loop_ub; i++) {
    switch_expression[i] = obj->Type[i];
  }
  b_bool = false;
  if (switch_expression.size(1) == 8) {
    loop_ub = 0;
    do {
      exitg1 = 0;
      if (loop_ub < 8) {
        if (switch_expression[loop_ub] != b_cv[loop_ub]) {
          exitg1 = 1;
        } else {
          loop_ub++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (b_bool) {
    loop_ub = 0;
  } else {
    b_bool = false;
    if (switch_expression.size(1) == 9) {
      loop_ub = 0;
      do {
        exitg1 = 0;
        if (loop_ub < 9) {
          if (switch_expression[loop_ub] != cv1[loop_ub]) {
            exitg1 = 1;
          } else {
            loop_ub++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (b_bool) {
      loop_ub = 1;
    } else {
      loop_ub = -1;
    }
  }
  switch (loop_ub) {
  case 0:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv[i];
    }
    poslim_data[0] = -3.1415926535897931;
    poslim_data[1] = 3.1415926535897931;
    obj->VelocityNumber = 1.0;
    obj->PositionNumber = 1.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    obj->VelocityNumber = 1.0;
    obj->PositionNumber = 1.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 1.0;
    break;
  default:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    obj->VelocityNumber = 0.0;
    obj->PositionNumber = 0.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 0.0;
    break;
  }
  obj->MotionSubspace.set_size(6, 1);
  for (int i{0}; i < 6; i++) {
    obj->MotionSubspace[i] = msubspace_data[i];
  }
  obj->PositionLimitsInternal.set_size(1, 2);
  for (int i{0}; i < 2; i++) {
    obj->PositionLimitsInternal[i] = poslim_data[i];
  }
  obj->HomePositionInternal.set_size(1);
  obj->HomePositionInternal[0] = 0.0;
  return obj;
}

//
// Arguments    : void
// Return Type  : rigidBodyJoint *
//
rigidBodyJoint *rigidBodyJoint::init()
{
  static const char b_cv1[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const char jname[8]{'b', 'a', 's', 'e', '_', 'j', 'n', 't'};
  static const signed char b_iv[6]{0, 0, 1, 0, 0, 0};
  static const signed char b_iv1[6]{0, 0, 0, 0, 0, 1};
  static const char b_cv[5]{'f', 'i', 'x', 'e', 'd'};
  rigidBodyJoint *obj;
  array<char, 2U> switch_expression;
  double poslim_data[12];
  int exitg1;
  int loop_ub;
  signed char msubspace_data[36];
  boolean_T b_bool;
  obj = this;
  obj->InTree = false;
  for (int i{0}; i < 16; i++) {
    obj->JointToParentTransform[i] = iv[i];
  }
  for (int i{0}; i < 16; i++) {
    obj->ChildToJointTransform[i] = iv[i];
  }
  obj->NameInternal.set_size(1, 8);
  for (int i{0}; i < 8; i++) {
    obj->NameInternal[i] = jname[i];
  }
  obj->Type.set_size(1, 5);
  for (int i{0}; i < 5; i++) {
    obj->Type[i] = b_cv[i];
  }
  switch_expression.set_size(1, obj->Type.size(1));
  loop_ub = obj->Type.size(1);
  for (int i{0}; i < loop_ub; i++) {
    switch_expression[i] = obj->Type[i];
  }
  b_bool = false;
  if (switch_expression.size(1) == 8) {
    loop_ub = 0;
    do {
      exitg1 = 0;
      if (loop_ub < 8) {
        if (switch_expression[loop_ub] != b_cv1[loop_ub]) {
          exitg1 = 1;
        } else {
          loop_ub++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (b_bool) {
    loop_ub = 0;
  } else {
    b_bool = false;
    if (switch_expression.size(1) == 9) {
      loop_ub = 0;
      do {
        exitg1 = 0;
        if (loop_ub < 9) {
          if (switch_expression[loop_ub] != cv1[loop_ub]) {
            exitg1 = 1;
          } else {
            loop_ub++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (b_bool) {
      loop_ub = 1;
    } else {
      loop_ub = -1;
    }
  }
  switch (loop_ub) {
  case 0:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv[i];
    }
    poslim_data[0] = -3.1415926535897931;
    poslim_data[1] = 3.1415926535897931;
    obj->VelocityNumber = 1.0;
    obj->PositionNumber = 1.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    obj->VelocityNumber = 1.0;
    obj->PositionNumber = 1.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 1.0;
    break;
  default:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    obj->VelocityNumber = 0.0;
    obj->PositionNumber = 0.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 0.0;
    break;
  }
  obj->MotionSubspace.set_size(6, 1);
  for (int i{0}; i < 6; i++) {
    obj->MotionSubspace[i] = msubspace_data[i];
  }
  obj->PositionLimitsInternal.set_size(1, 2);
  for (int i{0}; i < 2; i++) {
    obj->PositionLimitsInternal[i] = poslim_data[i];
  }
  obj->HomePositionInternal.set_size(1);
  obj->HomePositionInternal[0] = 0.0;
  return obj;
}

//
// Arguments    : void
// Return Type  : rigidBodyJoint *
//
rigidBodyJoint *rigidBodyJoint::j_init()
{
  static const char b[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const char b_cv[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const signed char b_iv[6]{0, 0, 1, 0, 0, 0};
  static const signed char b_iv1[6]{0, 0, 0, 0, 0, 1};
  rigidBodyJoint *obj;
  array<char, 2U> switch_expression;
  double poslim_data[12];
  int exitg1;
  int loop_ub;
  signed char msubspace_data[36];
  boolean_T b_bool;
  obj = this;
  obj->InTree = false;
  for (int i{0}; i < 16; i++) {
    obj->JointToParentTransform[i] = iv[i];
  }
  for (int i{0}; i < 16; i++) {
    obj->ChildToJointTransform[i] = iv[i];
  }
  obj->NameInternal.set_size(1, 4);
  obj->NameInternal[0] = 'j';
  obj->NameInternal[1] = 'n';
  obj->NameInternal[2] = 't';
  obj->NameInternal[3] = '8';
  obj->Type.set_size(1, 8);
  for (int i{0}; i < 8; i++) {
    obj->Type[i] = b[i];
  }
  switch_expression.set_size(1, obj->Type.size(1));
  loop_ub = obj->Type.size(1);
  for (int i{0}; i < loop_ub; i++) {
    switch_expression[i] = obj->Type[i];
  }
  b_bool = false;
  if (switch_expression.size(1) == 8) {
    loop_ub = 0;
    do {
      exitg1 = 0;
      if (loop_ub < 8) {
        if (switch_expression[loop_ub] != b_cv[loop_ub]) {
          exitg1 = 1;
        } else {
          loop_ub++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (b_bool) {
    loop_ub = 0;
  } else {
    b_bool = false;
    if (switch_expression.size(1) == 9) {
      loop_ub = 0;
      do {
        exitg1 = 0;
        if (loop_ub < 9) {
          if (switch_expression[loop_ub] != cv1[loop_ub]) {
            exitg1 = 1;
          } else {
            loop_ub++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (b_bool) {
      loop_ub = 1;
    } else {
      loop_ub = -1;
    }
  }
  switch (loop_ub) {
  case 0:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv[i];
    }
    poslim_data[0] = -3.1415926535897931;
    poslim_data[1] = 3.1415926535897931;
    obj->VelocityNumber = 1.0;
    obj->PositionNumber = 1.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    obj->VelocityNumber = 1.0;
    obj->PositionNumber = 1.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 1.0;
    break;
  default:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    obj->VelocityNumber = 0.0;
    obj->PositionNumber = 0.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 0.0;
    break;
  }
  obj->MotionSubspace.set_size(6, 1);
  for (int i{0}; i < 6; i++) {
    obj->MotionSubspace[i] = msubspace_data[i];
  }
  obj->PositionLimitsInternal.set_size(1, 2);
  for (int i{0}; i < 2; i++) {
    obj->PositionLimitsInternal[i] = poslim_data[i];
  }
  obj->HomePositionInternal.set_size(1);
  obj->HomePositionInternal[0] = 0.0;
  return obj;
}

//
// Arguments    : void
// Return Type  : rigidBodyJoint *
//
rigidBodyJoint *rigidBodyJoint::k_init()
{
  static const char b[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const char b_cv[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const signed char b_iv[6]{0, 0, 1, 0, 0, 0};
  static const signed char b_iv1[6]{0, 0, 0, 0, 0, 1};
  rigidBodyJoint *obj;
  array<char, 2U> switch_expression;
  double poslim_data[12];
  int exitg1;
  int loop_ub;
  signed char msubspace_data[36];
  boolean_T b_bool;
  obj = this;
  obj->InTree = false;
  for (int i{0}; i < 16; i++) {
    obj->JointToParentTransform[i] = iv[i];
  }
  for (int i{0}; i < 16; i++) {
    obj->ChildToJointTransform[i] = iv[i];
  }
  obj->NameInternal.set_size(1, 4);
  obj->NameInternal[0] = 'j';
  obj->NameInternal[1] = 'n';
  obj->NameInternal[2] = 't';
  obj->NameInternal[3] = '9';
  obj->Type.set_size(1, 8);
  for (int i{0}; i < 8; i++) {
    obj->Type[i] = b[i];
  }
  switch_expression.set_size(1, obj->Type.size(1));
  loop_ub = obj->Type.size(1);
  for (int i{0}; i < loop_ub; i++) {
    switch_expression[i] = obj->Type[i];
  }
  b_bool = false;
  if (switch_expression.size(1) == 8) {
    loop_ub = 0;
    do {
      exitg1 = 0;
      if (loop_ub < 8) {
        if (switch_expression[loop_ub] != b_cv[loop_ub]) {
          exitg1 = 1;
        } else {
          loop_ub++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (b_bool) {
    loop_ub = 0;
  } else {
    b_bool = false;
    if (switch_expression.size(1) == 9) {
      loop_ub = 0;
      do {
        exitg1 = 0;
        if (loop_ub < 9) {
          if (switch_expression[loop_ub] != cv1[loop_ub]) {
            exitg1 = 1;
          } else {
            loop_ub++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (b_bool) {
      loop_ub = 1;
    } else {
      loop_ub = -1;
    }
  }
  switch (loop_ub) {
  case 0:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv[i];
    }
    poslim_data[0] = -3.1415926535897931;
    poslim_data[1] = 3.1415926535897931;
    obj->VelocityNumber = 1.0;
    obj->PositionNumber = 1.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    obj->VelocityNumber = 1.0;
    obj->PositionNumber = 1.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 1.0;
    break;
  default:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    obj->VelocityNumber = 0.0;
    obj->PositionNumber = 0.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 0.0;
    break;
  }
  obj->MotionSubspace.set_size(6, 1);
  for (int i{0}; i < 6; i++) {
    obj->MotionSubspace[i] = msubspace_data[i];
  }
  obj->PositionLimitsInternal.set_size(1, 2);
  for (int i{0}; i < 2; i++) {
    obj->PositionLimitsInternal[i] = poslim_data[i];
  }
  obj->HomePositionInternal.set_size(1);
  obj->HomePositionInternal[0] = 0.0;
  return obj;
}

//
// Arguments    : void
// Return Type  : rigidBodyJoint *
//
rigidBodyJoint *rigidBodyJoint::l_init()
{
  static const char b[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const char b_cv[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const signed char b_iv[6]{0, 0, 1, 0, 0, 0};
  static const signed char b_iv1[6]{0, 0, 0, 0, 0, 1};
  static const char jname[5]{'j', 'n', 't', '1', '0'};
  rigidBodyJoint *obj;
  array<char, 2U> switch_expression;
  double poslim_data[12];
  int exitg1;
  int loop_ub;
  signed char msubspace_data[36];
  boolean_T b_bool;
  obj = this;
  obj->InTree = false;
  for (int i{0}; i < 16; i++) {
    obj->JointToParentTransform[i] = iv[i];
  }
  for (int i{0}; i < 16; i++) {
    obj->ChildToJointTransform[i] = iv[i];
  }
  obj->NameInternal.set_size(1, 5);
  for (int i{0}; i < 5; i++) {
    obj->NameInternal[i] = jname[i];
  }
  obj->Type.set_size(1, 8);
  for (int i{0}; i < 8; i++) {
    obj->Type[i] = b[i];
  }
  switch_expression.set_size(1, obj->Type.size(1));
  loop_ub = obj->Type.size(1);
  for (int i{0}; i < loop_ub; i++) {
    switch_expression[i] = obj->Type[i];
  }
  b_bool = false;
  if (switch_expression.size(1) == 8) {
    loop_ub = 0;
    do {
      exitg1 = 0;
      if (loop_ub < 8) {
        if (switch_expression[loop_ub] != b_cv[loop_ub]) {
          exitg1 = 1;
        } else {
          loop_ub++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (b_bool) {
    loop_ub = 0;
  } else {
    b_bool = false;
    if (switch_expression.size(1) == 9) {
      loop_ub = 0;
      do {
        exitg1 = 0;
        if (loop_ub < 9) {
          if (switch_expression[loop_ub] != cv1[loop_ub]) {
            exitg1 = 1;
          } else {
            loop_ub++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (b_bool) {
      loop_ub = 1;
    } else {
      loop_ub = -1;
    }
  }
  switch (loop_ub) {
  case 0:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv[i];
    }
    poslim_data[0] = -3.1415926535897931;
    poslim_data[1] = 3.1415926535897931;
    obj->VelocityNumber = 1.0;
    obj->PositionNumber = 1.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    obj->VelocityNumber = 1.0;
    obj->PositionNumber = 1.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 1.0;
    break;
  default:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    obj->VelocityNumber = 0.0;
    obj->PositionNumber = 0.0;
    obj->JointAxisInternal[0] = 0.0;
    obj->JointAxisInternal[1] = 0.0;
    obj->JointAxisInternal[2] = 0.0;
    break;
  }
  obj->MotionSubspace.set_size(6, 1);
  for (int i{0}; i < 6; i++) {
    obj->MotionSubspace[i] = msubspace_data[i];
  }
  obj->PositionLimitsInternal.set_size(1, 2);
  for (int i{0}; i < 2; i++) {
    obj->PositionLimitsInternal[i] = poslim_data[i];
  }
  obj->HomePositionInternal.set_size(1);
  obj->HomePositionInternal[0] = 0.0;
  return obj;
}

//
// Arguments    : double T[16]
// Return Type  : void
//
void rigidBodyJoint::transformBodyToParent(double T[16]) const
{
  static const char b_cv1[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const char b_cv[5]{'f', 'i', 'x', 'e', 'd'};
  double b[16];
  double obj[16];
  int exitg1;
  int kstr;
  boolean_T b_bool;
  b_bool = false;
  if (Type.size(1) == 5) {
    kstr = 0;
    do {
      exitg1 = 0;
      if (kstr < 5) {
        if (Type[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (b_bool) {
    kstr = 0;
  } else {
    b_bool = false;
    if (Type.size(1) == 8) {
      kstr = 0;
      do {
        exitg1 = 0;
        if (kstr < 8) {
          if (Type[kstr] != b_cv1[kstr]) {
            exitg1 = 1;
          } else {
            kstr++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (b_bool) {
      kstr = 1;
    } else {
      kstr = -1;
    }
  }
  switch (kstr) {
  case 0:
    std::memset(&b[0], 0, 16U * sizeof(double));
    b[0] = 1.0;
    b[5] = 1.0;
    b[10] = 1.0;
    b[15] = 1.0;
    break;
  case 1: {
    double b_v[4];
    double v[3];
    get_JointAxis(v);
    b_v[0] = v[0];
    b_v[1] = v[1];
    b_v[2] = v[2];
    b_v[3] = 0.0;
    axang2tform(b_v, b);
  } break;
  default: {
    double v[3];
    signed char b_I[9];
    get_JointAxis(v);
    for (int i{0}; i < 9; i++) {
      b_I[i] = 0;
    }
    b_I[0] = 1;
    b_I[4] = 1;
    b_I[8] = 1;
    for (int i{0}; i < 3; i++) {
      kstr = i << 2;
      b[kstr] = b_I[3 * i];
      b[kstr + 1] = b_I[3 * i + 1];
      b[kstr + 2] = b_I[3 * i + 2];
      b[i + 12] = v[i] * 0.0;
    }
    b[3] = 0.0;
    b[7] = 0.0;
    b[11] = 0.0;
    b[15] = 1.0;
  } break;
  }
  for (int i{0}; i < 4; i++) {
    double d;
    double d1;
    double d2;
    double d3;
    d = JointToParentTransform[i];
    d1 = JointToParentTransform[i + 4];
    d2 = JointToParentTransform[i + 8];
    d3 = JointToParentTransform[i + 12];
    for (int i1{0}; i1 < 4; i1++) {
      kstr = i1 << 2;
      obj[i + kstr] = ((d * b[kstr] + d1 * b[kstr + 1]) + d2 * b[kstr + 2]) +
                      d3 * b[kstr + 3];
    }
    d = obj[i];
    d1 = obj[i + 4];
    d2 = obj[i + 8];
    d3 = obj[i + 12];
    for (int i1{0}; i1 < 4; i1++) {
      kstr = i1 << 2;
      T[i + kstr] = ((d * ChildToJointTransform[kstr] +
                      d1 * ChildToJointTransform[kstr + 1]) +
                     d2 * ChildToJointTransform[kstr + 2]) +
                    d3 * ChildToJointTransform[kstr + 3];
    }
  }
}

//
// Arguments    : const double q_data[]
//                int q_size
//                double T[16]
// Return Type  : void
//
void rigidBodyJoint::transformBodyToParent(const double q_data[], int q_size,
                                           double T[16]) const
{
  static const char b_cv1[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const char b_cv[5]{'f', 'i', 'x', 'e', 'd'};
  double b[16];
  double obj[16];
  double tempR[9];
  double b_b;
  double result_data_idx_1;
  double result_data_idx_2;
  double result_data_idx_3;
  double sth;
  int exitg1;
  int kstr;
  boolean_T b_bool;
  b_bool = false;
  if (Type.size(1) == 5) {
    kstr = 0;
    do {
      exitg1 = 0;
      if (kstr < 5) {
        if (Type[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (b_bool) {
    kstr = 0;
  } else {
    b_bool = false;
    if (Type.size(1) == 8) {
      kstr = 0;
      do {
        exitg1 = 0;
        if (kstr < 8) {
          if (Type[kstr] != b_cv1[kstr]) {
            exitg1 = 1;
          } else {
            kstr++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (b_bool) {
      kstr = 1;
    } else {
      kstr = -1;
    }
  }
  switch (kstr) {
  case 0:
    std::memset(&b[0], 0, 16U * sizeof(double));
    b[0] = 1.0;
    b[5] = 1.0;
    b[10] = 1.0;
    b[15] = 1.0;
    break;
  case 1: {
    double R[9];
    double v[3];
    get_JointAxis(v);
    sth = v[0];
    result_data_idx_1 = v[1];
    result_data_idx_2 = v[2];
    kstr = (q_size != 0);
    for (int i{0}; i < kstr; i++) {
      result_data_idx_3 = q_data[0];
    }
    double b_tempR_tmp;
    double c_tempR_tmp;
    double cth;
    double d_tempR_tmp;
    double e_tempR_tmp;
    double f_tempR_tmp;
    double tempR_tmp;
    b_b = 1.0 / std::sqrt((sth * sth + result_data_idx_1 * result_data_idx_1) +
                          result_data_idx_2 * result_data_idx_2);
    v[0] = sth * b_b;
    v[1] = result_data_idx_1 * b_b;
    v[2] = result_data_idx_2 * b_b;
    cth = std::cos(result_data_idx_3);
    sth = std::sin(result_data_idx_3);
    b_b = v[0] * v[0] * (1.0 - cth) + cth;
    tempR[0] = b_b;
    result_data_idx_3 = v[0] * v[1] * (1.0 - cth);
    tempR_tmp = v[2] * sth;
    b_tempR_tmp = result_data_idx_3 - tempR_tmp;
    tempR[1] = b_tempR_tmp;
    c_tempR_tmp = v[0] * v[2] * (1.0 - cth);
    d_tempR_tmp = v[1] * sth;
    e_tempR_tmp = c_tempR_tmp + d_tempR_tmp;
    tempR[2] = e_tempR_tmp;
    result_data_idx_3 += tempR_tmp;
    tempR[3] = result_data_idx_3;
    tempR_tmp = v[1] * v[1] * (1.0 - cth) + cth;
    tempR[4] = tempR_tmp;
    f_tempR_tmp = v[1] * v[2] * (1.0 - cth);
    result_data_idx_1 = v[0] * sth;
    result_data_idx_2 = f_tempR_tmp - result_data_idx_1;
    tempR[5] = result_data_idx_2;
    c_tempR_tmp -= d_tempR_tmp;
    tempR[6] = c_tempR_tmp;
    d_tempR_tmp = f_tempR_tmp + result_data_idx_1;
    tempR[7] = d_tempR_tmp;
    f_tempR_tmp = v[2] * v[2] * (1.0 - cth) + cth;
    tempR[8] = f_tempR_tmp;
    R[0] = b_b;
    R[1] = b_tempR_tmp;
    R[2] = e_tempR_tmp;
    R[3] = result_data_idx_3;
    R[4] = tempR_tmp;
    R[5] = result_data_idx_2;
    R[6] = c_tempR_tmp;
    R[7] = d_tempR_tmp;
    R[8] = f_tempR_tmp;
    for (kstr = 0; kstr < 3; kstr++) {
      R[kstr] = tempR[3 * kstr];
      R[kstr + 3] = tempR[3 * kstr + 1];
      R[kstr + 6] = tempR[3 * kstr + 2];
    }
    std::memset(&b[0], 0, 16U * sizeof(double));
    for (int i{0}; i < 3; i++) {
      kstr = i << 2;
      b[kstr] = R[3 * i];
      b[kstr + 1] = R[3 * i + 1];
      b[kstr + 2] = R[3 * i + 2];
    }
    b[15] = 1.0;
  } break;
  default: {
    double v[3];
    get_JointAxis(v);
    std::memset(&tempR[0], 0, 9U * sizeof(double));
    tempR[0] = 1.0;
    tempR[4] = 1.0;
    tempR[8] = 1.0;
    for (int i{0}; i < 3; i++) {
      kstr = i << 2;
      b[kstr] = tempR[3 * i];
      b[kstr + 1] = tempR[3 * i + 1];
      b[kstr + 2] = tempR[3 * i + 2];
      b[i + 12] = v[i] * q_data[0];
    }
    b[3] = 0.0;
    b[7] = 0.0;
    b[11] = 0.0;
    b[15] = 1.0;
  } break;
  }
  for (int i{0}; i < 4; i++) {
    sth = JointToParentTransform[i];
    result_data_idx_1 = JointToParentTransform[i + 4];
    result_data_idx_2 = JointToParentTransform[i + 8];
    b_b = JointToParentTransform[i + 12];
    for (int i1{0}; i1 < 4; i1++) {
      kstr = i1 << 2;
      obj[i + kstr] = ((sth * b[kstr] + result_data_idx_1 * b[kstr + 1]) +
                       result_data_idx_2 * b[kstr + 2]) +
                      b_b * b[kstr + 3];
    }
    sth = obj[i];
    result_data_idx_1 = obj[i + 4];
    result_data_idx_2 = obj[i + 8];
    b_b = obj[i + 12];
    for (int i1{0}; i1 < 4; i1++) {
      kstr = i1 << 2;
      T[i + kstr] = ((sth * ChildToJointTransform[kstr] +
                      result_data_idx_1 * ChildToJointTransform[kstr + 1]) +
                     result_data_idx_2 * ChildToJointTransform[kstr + 2]) +
                    b_b * ChildToJointTransform[kstr + 3];
    }
  }
}

} // namespace coder

//
// File trailer for rigidBodyJoint.cpp
//
// [EOF]
//
