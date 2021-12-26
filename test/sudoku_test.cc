#include <sudoku_solver.h>
#include <sudoku_utils.h>

#include <gtest/gtest.h>

TEST(BasicSolver, NineXNine ) {
  bool use_diag = false;
  SudokuSolver solver(use_diag);
  board_t board_in = create_sudoku_board(9);
  solver.set_board(board_in);
  bool success = solver.solve();
  board_t board_out = solver.get_board();

  EXPECT_TRUE(success);
  EXPECT_TRUE(verify_sudoku_board(board_out,use_diag));
} 

TEST(BasicSolver, NineXNineDiag ) {
  bool use_diag = true;
  SudokuSolver solver(use_diag);
  board_t board_in = create_sudoku_board(9);
  solver.set_board(board_in);
  bool success = solver.solve();
  board_t board_out = solver.get_board();

  EXPECT_TRUE(success);
  EXPECT_TRUE(verify_sudoku_board(board_out,use_diag));
}

TEST(BasicSolver, FourXFour ) {
  bool use_diag = false;
  SudokuSolver solver(use_diag);
  board_t board_in = create_sudoku_board(4);
  solver.set_board(board_in);
  bool success = solver.solve();
  board_t board_out = solver.get_board();

  EXPECT_TRUE(success);
  EXPECT_TRUE(verify_sudoku_board(board_out, use_diag));
}

TEST(BasicSolver, FourXFourDiag ) {
  bool use_diag = true;
  SudokuSolver solver(use_diag);
  board_t board_in = create_sudoku_board(4);
  solver.set_board(board_in);
  bool success = solver.solve();
  board_t board_out = solver.get_board();
  
  EXPECT_TRUE(success);
  EXPECT_TRUE(verify_sudoku_board(board_out, use_diag));
}