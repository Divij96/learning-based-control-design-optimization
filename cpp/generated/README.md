# Generated C/C++ wrappers

This directory contains C/C++ source generated from the repository's MATLAB and Simulink models with the historical R2023a toolchain.

## Layout

- `ros/src/` contains 19 generated Catkin packages. Use `cpp/generated/ros/` as the Catkin workspace root.
- `standalone/forward_dynamics_robot_arm/` contains generated sources for the 4-, 6-, and 10-link robot-arm variants.

## Build environment

The generated ROS packages target Ubuntu 20.04 and ROS Noetic:

```bash
cd cpp/generated/ros
catkin init
catkin build
source devel/setup.bash
```

`catkin init` recreates the workspace-level `src/CMakeLists.txt` link. The original generated link was intentionally omitted because it pointed to an absolute MATLAB installation path on the source machine.

The sources are retained as historical reproducibility artifacts. They have not been regenerated or compiled during the repository cleanup, and successful builds may require the same MATLAB/Simulink R2023a code-generation products and system dependencies used by the original Linux workspace.

## What is excluded

The repository does not include:

- `packageInfo.mat` and experiment `.mat` files;
- raw `_grt_rtw`, `codegen`, and `slprj` intermediate directories;
- Catkin `build`, `devel`, `install`, and `log` directories;
- object files, libraries, MEX files, or other compiled output.

Those files are either metadata, duplicated code-generation output, machine-specific build output, or reproducible intermediates.

## Licensing

These files include MATLAB/Simulink-generated code and MathWorks-copyrighted support code. File headers and applicable MathWorks terms remain in force. The repository's root MIT license does not relicense this directory. Review [THIRD_PARTY_NOTICES.md](../../THIRD_PARTY_NOTICES.md) before redistribution or commercial use.
