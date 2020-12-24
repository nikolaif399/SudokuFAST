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