#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <catch2/catch.hpp>
#include <sudoku_solver.h>
#include <sudoku_utils.h>

TEST_CASE( "9x9 Sudoku can be solved", "[solver]" ) {
  bool use_diag = false;
  SudokuSolver solver(use_diag);
  board_t board_in = create_sudoku_board(9);
  solver.set_board(board_in);
  bool success = solver.solve();
  board_t board_out = solver.get_board();

  REQUIRE(success);
  REQUIRE(verify_sudoku_board(board_out,use_diag));
} 

TEST_CASE( "9x9 SudokuX can be solved", "[solver]" ) {
  bool use_diag = true;
  SudokuSolver solver(use_diag);
  board_t board_in = create_sudoku_board(9);
  solver.set_board(board_in);
  bool success = solver.solve();
  board_t board_out = solver.get_board();

  REQUIRE(success);
  REQUIRE(verify_sudoku_board(board_out, use_diag));
}

TEST_CASE( "4x4 Sudoku can be solved", "[solver]" ) {
  bool use_diag = false;
  SudokuSolver solver(use_diag);
  board_t board_in = create_sudoku_board(4);
  solver.set_board(board_in);
  bool success = solver.solve();
  board_t board_out = solver.get_board();

  REQUIRE(success);
  REQUIRE(verify_sudoku_board(board_out, use_diag));
}

TEST_CASE( "4x4 SudokuX can be solved", "[solver]" ) {
  bool use_diag = true;
  SudokuSolver solver(use_diag);
  board_t board_in = create_sudoku_board(4);
  solver.set_board(board_in);
  bool success = solver.solve();
  board_t board_out = solver.get_board();
  
  REQUIRE(success);
  REQUIRE(verify_sudoku_board(board_out, use_diag));
}
