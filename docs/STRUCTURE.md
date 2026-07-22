# Repository structure

This repository uses a language- and toolchain-oriented layout. Each experiment can span several top-level directories, but generated artifacts are kept separate from authored source.

## Top-level responsibilities

| Directory | Contents | Authorship |
| --- | --- | --- |
| `python/` | RL environments, training, evaluation, trajectory generation, and design optimization | Authored/adapted research code |
| `matlab/` | MATLAB dynamics functions, initialization, analysis, and plotting | Authored research code plus the attributed multirotor model |
| `simulink/` | Editable Simulink model definitions | Research models and attributed upstream models |
| `cpp/bindings/` | Build definitions and generated sources for Python extension modules | Authored build integration plus generated output |
| `cpp/generated/` | MATLAB/Simulink-generated C/C++ and ROS packages | Generated output; separate terms apply |
| `ros/packages/` | Hand-maintained ROS package metadata, launch files, URDFs, meshes, and RViz configuration | Authored integration code/assets |
| `assets/` | MuJoCo XML and VRML visualization assets | Research/upstream assets |
| `data/examples/` | Small example inputs safe to version | Curated example data |
| `scripts/` | Repository-level validation | Maintenance tooling |

## Cross-toolchain map

| Domain | Python | MATLAB | Simulink | ROS/integration | Generated C/C++ |
| --- | --- | --- | --- | --- | --- |
| Cart-pole | `python/cart_pole/` | `matlab/cart_pole/` | `simulink/cart_pole/` | `ros/packages/cart_pole/` | `cpp/bindings/cart_pole/`, `cpp/generated/ros/src/cart_pole_system_dynamics0/` |
| Quadcopter | `python/quadcopter/` | `matlab/quadcopter/` | `simulink/quadcopter/` | `ros/packages/model_dynamics/` | `cpp/bindings/quadcopter/`, `cpp/generated/ros/src/{multirotor0,sim_multi}/` |
| Aerofoil | `python/aerofoil/` | — | `simulink/aerofoil/` | — | `cpp/generated/ros/src/{aerofoil,subsystem,aeroelastic_control_updated_2023a}/` |
| Planar/SCARA robots | `python/{custom_robot,robot_chain,scara_2dof_robot}/` | `matlab/robots/` | `simulink/robots/` | `ros/packages/{custom_robot,robot_chain,scara_2dof_robot}/` | `cpp/bindings/` and `cpp/generated/ros/src/` robot packages |
| Serial robot arms | `python/forward_dynamics_robot_arm/` | `matlab/robots/robot_arm/` | `simulink/robots/` | `ros/packages/forward_dynamics_robot_arm/` | `cpp/generated/{ros,standalone}/` |
| MuJoCo locomotion | `python/{ant,half_cheetah}/` | — | — | `assets/mujoco/` | — |

## Migration from the experimental layout

| Previous location | Current location |
| --- | --- |
| `src/<experiment>/rl/` | `python/<experiment>/rl/` |
| `src/model_dynamics/` | `python/quadcopter/` and `ros/packages/model_dynamics/` |
| `cartpole_system/` | `matlab/cart_pole/` and `simulink/cart_pole/` |
| `MultirotorSim_Vervoorst/` | `matlab/quadcopter/multirotor/` and `simulink/quadcopter/multirotor/` |
| `robot/`, `robot_arm/` | `matlab/robots/` and `simulink/robots/` |
| generated `*/src/` trees | `cpp/generated/ros/src/` or `cpp/generated/standalone/` |
| generated `src/*/env/` trees | `cpp/bindings/` |

Runtime output belongs under the ignored `outputs/` tree. Training checkpoints and TensorBoard runs stay beside their Python experiment paths but are ignored by Git.
