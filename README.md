This program used backtrace to solve sudoku<br>
<br>
Because of Makefile, can compile by using "make" command<br>
<br>
There are 3 test files :<br>
test0.in : no solution<br>
testH.in : only one solution<br>
testW.in : more than one solution<br>
<br>
Can use "<" to input file into program<br>
ex:<br>
./solve_backtrace.exe < testH.in<br>
<br>
Can use "time" to check time-consuming<br>
ex:<br>
time ./solve_backtrace.exe < testH.in<br>
