/*
 * sudoku_solver_py.cpp
 * Created on Tue Dec 22 2020
 * Author Nikolai Flowers
 *
 * The MIT License (MIT)
 * Copyright (c) 2020 Nikolai Flowers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <sudoku_solver.h>
#include <colors.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <iostream>
#include <vector>
#include <chrono>

namespace py = pybind11;

std::tuple<py::array,bool> py_solve_sudoku(py::array_t<int> arr, bool sudokuX)
{
  // Collect buffer info from input
  py::buffer_info arr_info = arr.request();

  // Collect sizes
  const int type_size = sizeof(int);
  const int N2 = arr_info.shape[0];

  // Check input dimensions
  if ( arr_info.ndim     != 2 )
    throw std::runtime_error("Input should be 2-D NumPy array");
  if ( arr_info.shape[0] != N2 || arr_info.shape[1] != N2 )
    throw std::runtime_error("Input should have size [N,N]");
  
  // Create and size input board
  board_t input_board;
  input_board.resize(N2,std::vector<int>(N2,0)); 

  // Copy data from ptr over to int array
  int* data_ptr = (int*)arr_info.ptr;

  // Copy int array into input_board
  for (int i = 0; i < N2; ++i) {
    std::memcpy(input_board[i].data(),data_ptr+N2*i,N2*sizeof(int));
  }

  // Setup and solve sudoku
  SudokuSolver solver(sudokuX);
  solver.set_board(input_board);

  using namespace std::chrono;
  steady_clock::time_point t1 = steady_clock::now();
  bool success = solver.solve();
  steady_clock::time_point t2 = steady_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
  
  //  Output regular board if successful, initial board if unsuccesful
  board_t output_board;
  if (success) {
    std::cout << BOLD(FGRN("Puzzle solved!")) << std::endl;
    std::cout << "Solve time: " << time_span.count()*1e6 << " us" << std::endl;
    output_board = solver.get_board();
  }
  else {
    std::cerr << BOLD(FRED("Error! Puzzle not solvable.")) << std::endl;
    output_board = input_board;
  }

  // Flatten board before outputting
  std::vector<int> flat_board = flatten_board(output_board);

  ssize_t              ndim    = 2;
  std::vector<ssize_t> shape   = { N2 , N2};
  std::vector<ssize_t> strides = { N2 * type_size , type_size };

  //return 2-D NumPy array

  py::array output_arr = py::array(py::buffer_info(
    flat_board.data(),                           /* data as contiguous array  */
    sizeof(int),                          /* size of one scalar        */
    py::format_descriptor<int>::format(), /* data type                 */
    ndim,                                    /* number of dimensions      */
    shape,                                   /* shape of the matrix       */
    strides                                  /* strides for each axis     */
  ));

  return std::make_tuple(output_arr,success);
}

PYBIND11_MODULE(sudoku_solver_py, m) {
  m.def("solve_sudoku",
    &py_solve_sudoku,
    "Calculate the length of an array of vectors",
    py::arg(),
    py::arg("sudokuX")=false);
}