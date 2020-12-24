find_package(Catch2 REQUIRED)

add_executable(tests test.cpp)
target_link_libraries(tests sudoku_solver sudoku_utils Catch2::Catch2)
target_include_directories(tests PUBLIC ../include)

include(CTest)
include(Catch)
catch_discover_tests(tests)