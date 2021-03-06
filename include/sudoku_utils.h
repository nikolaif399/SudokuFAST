/*
 * sudoku_utils.h
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

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

typedef std::vector<std::vector<int>> board_t;

bool load_board_from_file(std::string filename, board_t &board);

void print_board(board_t board);

std::vector<int> flatten_board(board_t board);

board_t create_sudoku_board(int N2);

bool verify_valid_set(std::vector<int> in);

bool verify_sudoku_board(board_t in, bool use_diag);


