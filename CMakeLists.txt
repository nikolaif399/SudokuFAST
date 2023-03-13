cmake_minimum_required(VERSION 3.12)
add_definitions(-std=c++17)
set (PROJECT_VERSION "1.2")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RELEASE)
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

project(sudoku_solver
VERSION ${PROJECT_VERSION}
DESCRIPTION "Sudoku Solver using constraint programming")

# Build Sudoku Solver Library
add_library(sudoku_solver
  SHARED
  src/sudoku_solver.cc)
target_include_directories(sudoku_solver
  PUBLIC
  include)
target_compile_definitions(sudoku_solver PUBLIC -DNDEBUG)
set_target_properties(sudoku_solver
  PROPERTIES
  VERSION ${PROJECT_VERSION})

# Build Sudoku Utils Library
add_library(sudoku_utils
  SHARED
  src/sudoku_utils.cc)
target_include_directories(sudoku_utils
  PUBLIC
  include)
set_target_properties(sudoku_solver
  PROPERTIES
  VERSION ${PROJECT_VERSION})

# Build C++ Executable
find_package( Boost REQUIRED COMPONENTS filesystem program_options)
add_executable(main src/main.cc)
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

  pybind11_add_module(sudoku_solver_py src/sudoku_solver_py.cc)
  target_include_directories(sudoku_solver_py PUBLIC include)
  target_link_libraries(sudoku_solver_py PUBLIC sudoku_solver sudoku_utils)
  
  file(COPY scripts/interface_test.py
    DESTINATION .)
else()
  message("Skipping Python Bindings.")
endif()

# Build tests with google test
message("Building unit tests.")
enable_testing()

add_executable(
  sudoku_test
  test/sudoku_test.cc
)
target_link_libraries(
  sudoku_test
  sudoku_solver
  sudoku_utils
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(sudoku_test)