# Python C/C++ bindings

These `pybind11` modules expose the generated dynamics implementations to the Python environments under `python/`.

## Build

Install the repository dependencies, then configure and build the modules from the repository root:

```bash
cmake -S cpp/bindings -B cpp/bindings/build \
  -Dpybind11_DIR="$(python -m pybind11 --cmakedir)"
cmake --build cpp/bindings/build --parallel
```

Compiled extension modules are written to `cpp/bindings/build/python/`. The Python environments add that directory to their module search path automatically.

The bindings target the historical Linux/Python 3.7 environment. A compiler with C++14 support and Python development headers is required.

## Modules

| Python module | Experiment |
| --- | --- |
| `cartpole_Model_wrapper` | Cart-pole Simulink dynamics |
| `custom_robot_wrapper` | Custom planar robot dynamics |
| `Model_wrapper` | Multirotor dynamics |
| `robot_chain_dynamics_wrapper` | Robot-chain dynamics |
| `scara_robot_2dof_FD_wrapper` | Two-link SCARA dynamics |
| `forward_dynamics_{4arm,6arm}_wrapper` | Four- and six-link robot arms |
| `forward_dynamics_wrapper` | Ten-link robot arm |

Generated implementation and support files retain their original headers and applicable MathWorks terms. See [THIRD_PARTY_NOTICES.md](../../THIRD_PARTY_NOTICES.md).
