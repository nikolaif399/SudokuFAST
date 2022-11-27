# SudokuFAST
SudokuFAST is a lightweight and efficient sudoku solver written in C++ with easy-to-use C++ and Python bindings. It uses [constraint optimization](https://developers.google.com/optimization/cp) and efficient storage of constraints for rapid solve times of Sudoku or SudokuX puzzles of any (square) size. Solves 9x9 sudoku puzzles rated "Diabolical" in 40-160 microseconds.

Tested and verified on macOS Big Sur and Ubuntu 18.04 (should work with any unix OS).

## Dependencies
1. [CMake](https://cmake.org/) - Build system
2. [Boost](https://www.boost.org/doc/libs/1_66_0/more/getting_started/unix-variants.html) - Needed for running C++ executables
3. GoogleTest - Needed if building tests. Automatically installed with repo.

### Python - Specific Dependencies (if building python bindings)
1. [Miniconda3](https://docs.conda.io/en/latest/miniconda.html) - Manage python versions and dependencies
2. [pybind11](https://github.com/pybind/pybind11) - `conda install -c conda-forge pybind11`
3. [numpy](https://numpy.org/doc/stable/) - `conda install numpy`

## Instructions
```bash
git clone https://github.com/nikolaif399/SudokuFAST.git
cd SudokuFAST
mkdir build
cd build
```
C++ Bindings only:
```bash
cmake ..
make
```
C++ & Python bindings (replace 3.x in all places with your choice of python3 version):
```bash
conda create -n your-env-name-here python=3.x
conda activate your-env-name-here
conda install numpy
conda install -c conda-forge pybind11
cmake .. -DPYTHON_VERSION=3.x
make
```

To build unit tests (requires Catch2 test framework):
```bash
cmake .. -DBUILD_TESTS=1
make
ctest -v
```
