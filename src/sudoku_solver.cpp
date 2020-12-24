/*
 * sudoku_solver.cpp
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
#include <sudoku_solver.h>
#include <colors.h>

SudokuSolver::SudokuSolver(bool diag_constraint) {
  diag_constraint_ = diag_constraint;
}

bool SudokuSolver::set_board(board_t board) {
  // Copy over board
  board_ = board;

  N2_ = board.size();
  N_ = round(sqrt(N2_));
  N4_ = N2_*N2_;

  // Reset row, col, block and diag trackers
  row_free_.resize(N2_,std::vector<bool>(N2_,true));
  col_free_.resize(N2_,std::vector<bool>(N2_,true));
  block_free_.resize(N2_,std::vector<bool>(N2_,true));
  pos_diag_free_.resize(N2_,true);
  neg_diag_free_.resize(N2_,true);

  // Populate row, col, block and diag trackers
  for (int r = 0; r < N2_; ++r) {
    for (int c = 0; c < N2_; ++c) {
      int val = board[r][c];
      if (val != 0) mark_cell(r,c,val,false);
    }
  }

  return true;
}

board_t SudokuSolver::get_board() {
  return board_;
}

bool SudokuSolver::solve() {
  std::vector<int> search_path; // True if searchable
  int r,c;
  for (int i = 0; i < N4_;++i) {
    deserialize(i,r,c);
    if (board_[r][c] == 0) {
      search_path.push_back(i);
    }
  }
  std::vector<int>::iterator search_path_it = search_path.begin();

  int iter_count = 0;
  while(search_path_it != search_path.end()) {
    iter_count++;
    deserialize(*search_path_it,r,c);

    #ifndef NDEBUG
    std::cout << "Checking cell index " << *search_path_it << " (" << r+1 << ", " << c+1 << ")" << std::endl;
    #endif

    int curVal = board_[r][c];
    int nextVal = get_first_available_val_from(r,c,curVal+1);

    #ifndef NDEBUG
    std::cout << "Next value: " << nextVal << std::endl;
    #endif
    
    if (nextVal == 0) { // backtrack
      if (search_path_it == search_path.begin()) {
        return false; // no solution found
      }

      // Mark cell as empty
      board_[r][c] = 0;

      // Move backwards to previous cell on search path
      search_path_it--;

      // Collect row col indicies for previous cell
      deserialize(*search_path_it,r,c);

      // Refree previous val
      int val = board_[r][c];
      mark_cell(r,c,val,true); 

      #ifndef NDEBUG
      std::cout << "Backtracking" << std::endl;
      #endif
    }
    else { // go forwards
      
      #ifndef NDEBUG
      std::cout << "Placing " << nextVal << " at (" << r+1 << ", " <<
        c+1 << ")" << std::endl;
      #endif

      // Mark board with trial val
      board_[r][c] = nextVal;

      // Mark free arrays with this cell candidate
      mark_cell(r,c,nextVal,false);

      // Move to next cell
      search_path_it++;
    }

    #ifndef NDEBUG
    std::cout << std::endl;
    #endif
  }

  #ifndef NDEBUG
    std::cout << "Solved in " << iter_count << " iterations" << std::endl;
  #endif

  return true;
}

void SudokuSolver::mark_cell(int r, int c, int val, bool free) {
  row_free_[r][val-1] = free;
  col_free_[c][val-1] = free;
  block_free_[get_block_idx(r,c)][val-1] = free;
  if (r == c) {
    pos_diag_free_[val-1] = free;
  }
  if (r + c + 1 == N2_) {
    neg_diag_free_[val-1] = free;
  } 
}

int SudokuSolver::get_first_available_val_from(int r, int c, int val_start = 1) {
  for (size_t val = val_start; val <= N2_; ++val) {
    if (row_free_[r][val-1] &&
        col_free_[c][val-1] &&
        block_free_[get_block_idx(r,c)][val-1]) {
      if (!diag_constraint_) return val; // diag constraint not active

      // Check if both diagonals are clear
      if ((r != c || pos_diag_free_[val-1]) && 
          (r + c + 1 != N2_ || neg_diag_free_[val-1])) {
          return val;
      }
    }
  }
  return 0;
}

int SudokuSolver::serialize(int r, int c) {
  return N2_ * r + c;
}

void SudokuSolver::deserialize(int idx, int &r, int &c) {
  r = idx/N2_;
  c = idx % N2_;
}

int SudokuSolver::get_block_idx(int r, int c) {
  int block_r = r / N_;
  int block_c = c / N_;
  return block_r*N_ + block_c;
}
