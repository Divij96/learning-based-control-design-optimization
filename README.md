# Learning-Based Control and Design Co-Optimization

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

Research code from my master's thesis on jointly optimizing control policies and physical system parameters. The experiments combine reinforcement learning, Bayesian optimization, and Gaussian-mixture sampling across cart-pole, quadcopter, robot-arm, aeroelastic, and MuJoCo locomotion systems.

## What this repository demonstrates

- PPO- and SAC-based control with parallelized Gym/Gymnasium environments
- physical design exploration with HEBO and Gaussian mixture models
- controller/design co-optimization across different dynamics and morphologies
- Python integration with ROS 1 and MATLAB/Simulink-generated C/C++ models
- evaluation and visualization pipelines for policies, trajectories, and designs

## Repository organization

The repository is organized by language and toolchain so reviewers can quickly find the relevant implementation:

```text
.
├── python/                     # training, environments, evaluation, optimization
│   ├── ant/                    # MuJoCo Ant morphology experiments
│   ├── half_cheetah/           # MuJoCo HalfCheetah experiments
│   ├── cart_pole/              # cart-pole control and design optimization
│   ├── quadcopter/             # quadcopter environments and training
│   └── {aerofoil,custom_robot,forward_dynamics_robot_arm,
│        robot_chain,scara_2dof_robot}/
├── matlab/                     # authored MATLAB models and analysis scripts
├── simulink/                   # editable `.slx` model definitions
├── cpp/
│   ├── bindings/               # pybind11 modules imported by Python
│   └── generated/
│       ├── ros/src/            # Catkin-compatible generated ROS packages
│       └── standalone/         # standalone generated robot-arm sources
├── ros/packages/               # authored launch, URDF, RViz, and package metadata
├── assets/                     # MuJoCo XML and visualization assets
├── data/examples/              # small checked-in example inputs
├── docs/                       # architecture and migration notes
└── scripts/                    # dependency-free repository checks
```

See [docs/STRUCTURE.md](docs/STRUCTURE.md) for the full directory map and the relationship between the authored models and generated wrappers.

## Experiment families

| System | Python | Models and integration |
| --- | --- | --- |
| Cart-pole | `python/cart_pole/` | `matlab/cart_pole/`, `simulink/cart_pole/` |
| Quadcopter | `python/quadcopter/` | `matlab/quadcopter/`, `simulink/quadcopter/`, `ros/packages/model_dynamics/` |
| Robot arms | `python/{custom_robot,robot_chain,scara_2dof_robot,forward_dynamics_robot_arm}/` | `matlab/robots/`, `simulink/robots/`, `ros/packages/` |
| Ant and HalfCheetah | `python/{ant,half_cheetah}/` | `assets/mujoco/` |
| Aeroelastic model | `python/aerofoil/` | `simulink/aerofoil/` |

The core experimental loop is:

1. train a policy over one or more candidate physical designs;
2. evaluate design-dependent returns in vectorized environments;
3. propose new designs with HEBO or a fitted Gaussian mixture;
4. continue policy training and retain the best controller/design pair.

## Python setup

The environment specification was reconstructed from the historical Conda environment and metadata embedded in a saved Stable-Baselines3 model. The primary versions are Python 3.7.16, Stable-Baselines3 2.0.0, PyTorch 1.13.1, NumPy 1.21.6, Gymnasium 0.28.1, and Gym 0.26.2 on Linux.

```bash
conda env create -f environment.yml
conda activate master-thesis
python scripts/check_repository.py
```

Run experiment entry points from the repository root. For example:

```bash
python python/ant/rl/train.py
```

Training entry points are compute-intensive. Review the constants near the top of each script before starting a run. Pretrained checkpoints are not included, so evaluation scripts require a locally trained or separately supplied checkpoint.

## C/C++ wrappers

Generated source is kept under `cpp/` rather than mixed with authored Python and MATLAB code. Build the Python-facing modules first:

```bash
cmake -S cpp/bindings -B cpp/bindings/build \
  -Dpybind11_DIR="$(python -m pybind11 --cmakedir)"
cmake --build cpp/bindings/build --parallel
```

The Python environments look for the compiled modules in `cpp/bindings/build/python`. See [cpp/bindings/README.md](cpp/bindings/README.md) for the module map.

The ROS wrappers form a Catkin workspace source tree:

```bash
cd cpp/generated/ros
catkin init
catkin build
source devel/setup.bash
```

The historical target environment was Ubuntu 20.04, ROS Noetic, and MATLAB/Simulink R2023a. The wrapper source is preserved for reproducibility, but the complete ROS workspace has not been rebuilt on macOS as part of this cleanup.

Raw `_grt_rtw`, `codegen`, `slprj`, build, devel, and install directories remain excluded because they are intermediate or reproducible build output. MATLAB `packageInfo.mat` files are also excluded. See [cpp/generated/README.md](cpp/generated/README.md) for package details and regeneration notes.

## Licensing and attribution

Original work is released under the [MIT License](LICENSE). Third-party models and generated code retain their own notices and usage terms; they are not relicensed by the root MIT license. See [THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md).
