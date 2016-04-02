#include"Sudoku.h"

Sudoku::Sudoku()
{
    int empty[SIZE];
    memset(empty,0,sizeof(empty));
    setBoard(empty);
}
Sudoku::Sudoku(const int init_board[])
{
    setBoard(init_board);
}
void Sudoku::setBoard(const int set_board[])
{
    int i;
    for(i=0;i<SIZE;i++)
    {
        _board[i]=set_board[i];
    }
}
int Sudoku::getElement(int index)
{
    return _board[index];
}
void Sudoku::printBoard()
{//print out the _board[]
    int i;
    for(i=0;i<SIZE;i++)
    {
        cout<<_board[i];
        cout<<(((i+1)%9==0)?'\n':' ');
    }
}
void Sudoku::printSolve()
{//print out the answer which store in _solveboard[]
    int i;
    for(i=0;i<SIZE;i++)
    {
        cout<<_solveboard[i];
        cout<<(((i+1)%9==0)?'\n':' ');
    }
}
bool Sudoku::checkCorrect()
{//using to check whole board
    int i,num=0;
    int check_tmp[27];
    for(i=0;i<27;i++)check_tmp[i]=1;
    //#define DEBUG_2//test check output
    for(i=0;i<SIZE;i++)
    {//row check
        #ifdef DEBUG_2
            cout<<i<<'\t';
        #endif
        check_tmp[num]*=_board[i];
        if(i%9==8)
        {
            #ifdef DEBUG_2
                cout<<setw(2)<<num<<":"<<check_tmp[num]<<endl;
            #endif
            if(check_tmp[num]!=362880)
            {
                return false;
            }
            num++;
        }
    }
    for(i=0;i<SIZE;i+=((i+9>80&&i!=80)?(-71):9))
    {//col check
        #ifdef DEBUG_2
            cout<<i<<'\t';
        #endif
        check_tmp[num]*=_board[i];
        if(i+9>80)
        {
            #ifdef DEBUG_2
                cout<<setw(2)<<num<<":"<<check_tmp[num]<<endl;
            #endif
            if(check_tmp[num]!=362880)
            {
                return false;
            }
            num++;
        }
    }
    for(i=0;i<SIZE;i+=((i%3==2&&i!=26&&i!=53)?((i==20||i==23||i==47||i==50||i==74||i==77)?(-17):7):1))
    {//cell check
        #ifdef DEBUG_2
            cout<<i<<'\t';
        #endif
        check_tmp[num]*=_board[i];
        if(i==20||i==23||i==26||i==47||i==50||i==53||i==74||i==77||i==80)
        {
            #ifdef DEBUG_2
                cout<<setw(2)<<num<<":"<<check_tmp[num]<<endl;
            #endif
            if(check_tmp[num]!=362880)
            {
                return false;
            }
            num++;
        }
    }
}
bool Sudoku::checkQuestion()
{//because the question maybe wrong, solve after checking
    int i;
    for(i=0;i<SIZE;i++)
    {
        if(_board[i]!=0)
        {
            if(checkIndexCorrect(i)==false)
            {
                return false;
            }
        }
    }
    return true;
}
bool Sudoku::checkIndexCorrect(int index)
{
    int col,row,cell,i,j;
    col=index%9;
    row=static_cast<int>(index/9);
    cell=(static_cast<int>(row/3))*3+(static_cast<int>(col/3));
    for(i=0,j=9*row;i<9;i++,j++)//row check
    {
        if(_board[index]==_board[j]&&j!=index)
        {//if check index has the same number then return false
            return false;
        }
    }
    for(i=0,j=col;i<9;i++,j+=9)//col check
    {
        if(_board[index]==_board[j]&&j!=index)
        {//if check index has the same number then return false
            return false;
        }
    }
    switch(cell)//cell check
    {//using switch to get the cell's first index
        case 0:
        case 1:
        case 2:
            j=cell*3;
            break;
        case 3:
        case 4:
        case 5:
            j=cell*3+18;
            break;
        case 6:
        case 7:
        case 8:
            j=cell*3+36;
            break;
    }
    for(i=0,j;i<9;i++,j+=((j%3==2)?7:1))
    {
        if(_board[index]==_board[j]&&j!=index)
        {//if check index has the same number then return false
            return false;
        }
    }
    return true;//if all correct return true
}
void Sudoku::backtrace(int num)
{
    int i,solve_count=0;
    /*if(num==SIZE)//can comment out to see all solutions
    {
        printBoard();
    }*/
    if(num==SIZE)//trace finish
    {
        for(i=0;i<SIZE;i++)
        {//store first solution to check have any other solution
            _solveboard[i]=_board[i];
        }
        _solvenum++;
        if(_solvenum>1)
        {//more than 1 solution
            return ;
        }
        else;
    }
    int col,row;
    col=num%9;
    row=static_cast<int>(num/9);
    if(_board[num]==0)//find where can insert number
    {
        for(i=1;i<=9;i++)
        {//insert number from 1 to 9
            _board[num]=i;
            if(checkIndexCorrect(num))
            {
                //cout<<num<<":"<<i<<endl;
                backtrace(num+1);
            }
        }
        _board[num]=0;//back to up one level's for loop
    }
    else
    {//if meet problem number, insert the next index
        backtrace(num+1);
    }
}
void Sudoku::readIn()
{
    int i;
    int in_board[SIZE];
    _zeronum=0;
    for(i=0;i<SIZE;i++)
    {
        cin>>in_board[i];
        if(in_board[i]==0)//count the zero's number
        {
            _zeronum++;
        }
    }
    setBoard(in_board);
}
void Sudoku::solveBacktrace()//solve by using backtrace
{
    int solve_count=0;
    _solvenum=0;
    //cout<<_zeronum<<endl;
    if(checkQuestion()&&_zeronum>64)//there is no solution if numbers are less than 17
    {
        cout<<2<<endl;
    }
    else if(checkQuestion())
    {
        backtrace(0);
        solve_count++;
        switch(_solvenum)
        {
            case 0://no solution
                cout<<0;
                break;
            case 1://only 1 solution
                cout<<1<<endl;
                printSolve();
                break;
            default://more than 1 solution
                cout<<2;
                break;
        }
    }
    else//problem is wrong
    {
        cout<<0;
    }
}
