#include<iostream>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#define SIZE 81
using namespace std;
class Sudoku{
    public:
        Sudoku();
        Sudoku(const int init_board[]);
        
        void readIn();
        void solveBacktrace();//solve by using backtrace
        
        void setBoard(const int set_board[]);
        int getElement(int index);
        void printBoard();
        
    private:
        void printSolve();
        bool checkCorrect();
        bool checkQuestion();
        bool checkIndexCorrect(int index);
        void backtrace(int num);
        
        int _board[SIZE];
        int _zeronum;
        int _solvenum;
        int _solveboard[SIZE];
};
