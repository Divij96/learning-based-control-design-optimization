# Learning-Based Control and Design Co-Optimization

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

Research code from my master's thesis on jointly optimizing control policies and physical system parameters. The experiments combine reinforcement learning with Bayesian optimization and Gaussian-mixture sampling across simulated control systems ranging from cart-pole and quadcopter models to robot arms and MuJoCo locomotion tasks.

## What this project demonstrates

- PPO-based control with parallelized Gym/Gymnasium environments
- design-space exploration with HEBO and Gaussian mixture models
- controller/design co-optimization for systems with different dynamics and morphology
- integration of Python, MuJoCo, ROS 1, and MATLAB/Simulink dynamics
- evaluation and visualization pipelines for policies, trajectories, and optimized designs

## Experiment families

| System | Main location | Runtime |
| --- | --- | --- |
| Cart-pole | `src/cart_pole/` | Python, Gym, ROS |
| Quadcopter | `src/model_dynamics/` | Python, ROS, MATLAB/Simulink |
| Planar and serial robot arms | `src/custom_robot/`, `src/robot_chain/`, `src/scara_2dof_robot/`, `src/forward_dynamics_robot_arm/` | Python, ROS, generated C++ |
| Ant and HalfCheetah | `src/ant/`, `src/half_cheetah/` | Python, Gymnasium, MuJoCo |
| Aeroelastic model | `aerofoil_matlab/` | Python, MATLAB/Simulink |

The core experimental pattern is:

1. train a policy over one or more candidate physical designs;
2. evaluate design-dependent returns in vectorized environments;
3. propose new designs with HEBO or a fitted Gaussian mixture;
4. continue policy training and record the best controller/design pair.

## Reproducible Python environment

The environment specification was reconstructed from the repository's historical Conda file and metadata embedded in a saved Stable-Baselines3 model. That model records Python 3.7.16, Stable-Baselines3 2.0.0, PyTorch 1.13.1, NumPy 1.21.6, Gymnasium 0.28.1, and Gym 0.26.2 on Linux.

Create the environment with Miniconda or Anaconda:

```bash
conda env create -f environment.yml
conda activate master-thesis
python scripts/check_repository.py
```

For direct script execution, run commands from the repository root. For example, start a new Ant training run with:

```bash
python src/ant/rl/train.py
```

Training entry points are compute-intensive. Review the constants near the top of each script before starting a run. Pretrained checkpoints are intentionally not included in this public source snapshot, so evaluation scripts require a locally trained or separately downloaded checkpoint.

### ROS and MATLAB experiments

The robot, quadcopter, and aeroelastic experiments additionally depend on the original Linux toolchain:

- Ubuntu 20.04 and ROS Noetic
- Catkin Tools
- MATLAB/Simulink R2023a with ROS support
- generated model wrappers available on `PYTHONPATH`

The generated C/C++ wrappers are excluded from this public repository. The editable MATLAB/Simulink models and Python integration code are retained, but running those experiments requires regenerating the wrappers with the original toolchain.

## Repository layout

```text
.
├── src/                         # primary Python/ROS experiments
│   ├── ant/                     # MuJoCo Ant morphology optimization
│   ├── half_cheetah/            # MuJoCo HalfCheetah design experiments
│   ├── cart_pole/               # cart-pole control/design experiments
│   ├── model_dynamics/          # quadcopter environments and training
│   └── {custom_robot,robot_chain,scara_2dof_robot,
│        forward_dynamics_robot_arm}/
├── cartpole_system/             # MATLAB scripts and Simulink models
├── MultirotorSim_Vervoorst/     # licensed multirotor model and integration
├── robot/ and robot_arm/        # robot model sources and MATLAB assets
├── aerofoil_matlab/             # aeroelastic Simulink experiment
├── environment.yml              # Conda environment entry point
└── requirements.txt             # pinned Python dependencies
```

## Reproducibility notes

- Random seeds were not consistently recorded in the original experiments, so exact learning curves may vary.
- Large training runs can require tens or hundreds of millions of environment steps.
- `MASTER_THESIS_INPUT_CMD` can point model-comparison scripts to an external MATLAB input file; `.mat` inputs are not distributed here.
- New checkpoints, TensorBoard logs, build products, and generated outputs are ignored by Git and should be stored outside the source history.

## Intentionally excluded

This public repository contains source code and editable model definitions only. It excludes experiment `.mat` files, checkpoints, TensorBoard logs, plots, generated C/C++ wrappers, compiled objects, build directories, caches, and the original experimental Git history.

## License and attribution

Original work in this repository is released under the [MIT License](LICENSE). Third-party and generated components retain their own terms; see [THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md), including the BSD-licensed multirotor model in `MultirotorSim_Vervoorst/`.
