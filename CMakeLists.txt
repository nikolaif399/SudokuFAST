cmake_minimum_required(VERSION 3.0.0)
add_definitions(-std=c++17)

set (PROJECT_VERSION "1.2")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

project(sudoku_solver
VERSION ${PROJECT_VERSION}
DESCRIPTION "Sudoku Solver using constraint programming")

# Build Sudoku Solver Library
add_library(sudoku_solver
  SHARED
  src/sudoku_solver.cpp)
target_include_directories(sudoku_solver
  PUBLIC
  include)
set_target_properties(sudoku_solver
  PROPERTIES
  VERSION ${PROJECT_VERSION})

# Build Sudoku Utils Library
add_library(sudoku_utils
  SHARED
  src/sudoku_utils.cpp)
target_include_directories(sudoku_utils
  PUBLIC
  include)
set_target_properties(sudoku_solver
  PROPERTIES
  VERSION ${PROJECT_VERSION})

# Build C++ Executable
find_package( Boost REQUIRED COMPONENTS filesystem program_options)
add_executable(main src/main.cpp)
target_include_directories(main
  PUBLIC
  include
  ${Boost_INCLUDE_DIRS})
target_link_libraries(main
  sudoku_solver
  sudoku_utils
  ${Boost_LIBRARIES})

# Build Python Bindings with -DPYTHON_VERSION 3.x
if(PYTHON_VERSION)

  set(PYBIND11_PYTHON_VERSION ${PYTHON_VERSION})
  message("Generating python${PYTHON_VERSION} module")
  find_package(pybind11 REQUIRED)

  pybind11_add_module(sudoku_solver_py src/sudoku_solver_py.cpp)
  target_include_directories(sudoku_solver_py PUBLIC include)
  target_link_libraries(sudoku_solver_py PUBLIC sudoku_solver sudoku_utils)
  
  file(COPY scripts/interface_test.py
    DESTINATION .)
else()
  message("Skipping Python Bindings.")
endif()

# Build tests with catch2
if (BUILD_TESTS)
  message("Building unit tests.")
  enable_testing()
  add_subdirectory("test")
else()
  message("Skipping Tests.")
endif()