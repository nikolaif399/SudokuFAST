/*
 * sudoku_utils.cpp
 * Created on Wed Dec 23 2020
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

#include <sudoku_utils.h>

bool load_board_from_file(std::string filename, board_t &board){

  int N2 = board.size();
  std::ifstream fp(filename, std::ifstream::in);
  if (! fp) {
    std::cerr << "Error, file couldn't be opened" << std::endl; 
  }

  int val;
  for(int r = 0; r < N2; r++) {  // stop loops if nothing to read
    for(int c = 0; c < N2; c++){
      fp >> val;

      board[r][c] = val;
      
      if ( ! fp ) {
        std::cerr << "Error reading file for element (" << r << ", " << c << std::endl; 
        return false; 
      }
    }
  }
  return true;      
}

void print_board(board_t board) {
  int N2 = board.size();
  for (int r = 0; r < N2; ++r){
    for (int c = 0; c < N2; ++c){
      std::cout << board[r][c] << " ";
    }
    std::cout << std::endl;
  }
}

std::vector<int> flatten_board(board_t board) {
  int N2 = board.size();
  std::vector<int> flat_board(N2*N2);
  
  for (int i = 0; i < N2; ++i) {
    flat_board.insert(flat_board.begin()+i*N2,board[i].begin(),board[i].end());
  }
  return flat_board;
}

// These are each diag compatible
board_t create_sudoku_board(int N2) {
  board_t board;
  board.resize(N2);
  if (N2 == 9) {
    board[0] = {0, 7, 8, 0, 1, 6, 0, 0, 4};
    board[1] = {2, 0, 0, 0, 0, 9, 3, 0, 0};
    board[2] = {4, 5, 9, 0, 0, 0, 0, 0, 0};
    board[3] = {0, 9, 0, 0, 3, 0, 0, 0, 2};
    board[4] = {0, 6, 0, 9, 0, 7, 0, 3, 0};
    board[5] = {1, 0, 0, 0, 5, 0, 0, 8, 0};
    board[6] = {0, 0, 0, 0, 0, 0, 5, 2, 9};
    board[7] = {0, 0, 1, 2, 0, 0, 0, 0, 3};
    board[8] = {9, 0, 0, 7, 4, 0, 8, 1, 0};
  }
  else if(N2 == 4) {
    board[0] = {0,0,0,0};
    board[1] = {2,0,0,0};
    board[2] = {1,0,0,4};
    board[3] = {0,0,0,0};
  }
  return board;
}

bool verify_valid_set(std::vector<int> in) {
  int N2 = in.size();
  
  std::vector<bool> value_present (N2,false);
  for (int i = 0; i < N2; ++i) {
    int val = in[i];
    if (val < 1 || val > N2) return false; //out of range
    if (value_present[val-1]) return false; //duplicate
    value_present[val-1] = true;
  }
  return true;
}

bool verify_sudoku_board(board_t in, bool use_diag) {
  int N2 = in.size();

  // Check rows
  for (int r = 0; r < N2; ++r) {
    if (!verify_valid_set(in[r])) return false;
  }
  
  // Check columns
  for (int c = 0; c < N2; ++c) {
    std::vector<int> col(N2);
    for (int r = 0; r < N2; ++r) {
      col[r] = in[r][c];
    }
    if (!verify_valid_set(col)) return false;
  }

  // Check blocks
  int block_size = std::round(std::sqrt(N2));
  for (int br = 0; br < block_size; br++) {
    for (int bc = 0; bc < block_size; bc++) {
      std::vector<int> block;
      for (int r = br*block_size; r < (br+1)*block_size; ++r){
        for (int c = bc*block_size; c < (bc+1)*block_size; ++c){
          block.push_back(in[r][c]);
        }
      }
      if (!verify_valid_set(block)) return false;
    }
  }

  // Check diagonals
  if (use_diag) {
    std::vector<int> pos_diag(N2);
    std::vector<int> neg_diag(N2);
    for (int i = 0; i < N2; ++i) {
      pos_diag[i] = in[i][i];
      neg_diag[i] = in[i][N2-1-i];
    }
    if (!verify_valid_set(pos_diag)) return false;
    if (!verify_valid_set(neg_diag)) return false;
  }
  
  return true;
}