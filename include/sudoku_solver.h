/*
 * sudoku_solver.h
 * Created on Mon Dec 21 2020
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

#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <iostream>
#include <vector>
#include <sudoku_utils.h> // typedef board_t as 2D int vector
#include <math.h>

class SudokuSolver {

public:
  SudokuSolver(bool diag_constraint=false);

  bool set_board(board_t board);

  bool solve();

  board_t get_board();

private:

  void mark_cell(int r, int c, int val, bool free);

  /*
  void add_cell_val(int r, int c, int val);

  void remove_cell_val(int r, int c);
  */

  int get_first_available_val_from(int r, int c, int val_start);

  int serialize(int r, int c);

  void deserialize(int idx, int &r, int &c);

  int get_block_idx(int r, int c);

  int N_;
  int N2_;
  int N4_;

  board_t board_;

  std::vector<std::vector<bool>> row_free_;
  std::vector<std::vector<bool>> col_free_;
  std::vector<std::vector<bool>> block_free_;

  bool diag_constraint_;

  std::vector<bool> pos_diag_free_;
  std::vector<bool> neg_diag_free_;
};

#endif // SUDOKU_SOLVER