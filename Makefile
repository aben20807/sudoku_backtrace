all: Sudoku.o solve_backtrace.cpp
	g++ -o solve_backtrace Sudoku.o solve_backtrace.cpp
	
Sudoku.o:
	g++ -c Sudoku.cpp -o Sudoku.o
	
