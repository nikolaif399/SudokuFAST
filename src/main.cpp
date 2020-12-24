/*
 * main.cpp
 * Created on Sun Dec 20 2020
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
#include <sudoku_utils.h>
#include <colors.h>
#include <chrono>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc,char** argv) {

  po::options_description desc("Allowed options");
  bool use_diag = false;
  std::string sudoku_file;
  int sudoku_size;
	desc.add_options()
		("help,h", "usage ./main path-to-txt-file")
    ("input-file,i", po::value<std::string >(&sudoku_file), "input sudoku txt file")
    ("sudoku-size,n", po::value<int >(&sudoku_size)->required()->default_value(3), "input sudoku block size (2 for 4x4, 3 for 9x9, 4 for 16x16, etc")
    ("sudokux,x", po::bool_switch(&use_diag), "sudokuX (diagonal constraints)")
    ;

  // Named parameters
	po::variables_map vm;
	po::store(parse_command_line(argc,argv,desc), vm);

  // Redirect positional args to input-file
  po::positional_options_description p;
  p.add("input-file", -1);
  po::store(po::command_line_parser(argc, argv).
    options(desc).positional(p).run(), vm);

	po::notify(vm);	

  if (vm.count("help")) {
    std::cout << desc << std::endl;
    return 1;
  }
  if (!vm.count("input-file")) {
    std::cout << "Please specify sudoku input txt file" << std::endl;
    return 1;
  }

  // Load board from file
  board_t board;
  int N2 = sudoku_size*sudoku_size;
  board.resize(N2,std::vector<int>(N2,0)); 

  std::cout << board.size() << std::endl;
  std::cout << board[0].size() << std::endl;

  if (!load_board_from_file(sudoku_file,board)) {
    return 1;
  }

  print_board(board);

  // Setup solver class
  SudokuSolver solver(use_diag);
  solver.set_board(board);

  using namespace std::chrono;
  steady_clock::time_point t1 = steady_clock::now();
  bool success = solver.solve();
  steady_clock::time_point t2 = steady_clock::now();
  if(!success) {
    std::cerr << BOLD(FRED("Error! Puzzle not solvable.")) << std::endl;
  }
  else {
    std::cout << BOLD(FGRN("Puzzle solved.")) << std::endl;
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << "Solve time: " << time_span.count()*1000 << " ms" << std::endl;
    std::cout << std::endl;
    board_t solved_board = solver.get_board();
    print_board(solved_board);
  }
  return 0;  
}