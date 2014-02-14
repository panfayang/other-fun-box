Hello! Welcome to Sudoku Validator~

This program creates 27 threads to check the valid of each of the 9 rows, 9 columns, and 9 sub-squares in a sudoku solution.

How to use: 

1. Write your solution into a file, say, answer.txt 

2. When you finish writing, you should have 9 9-digit numbers in 9 rows, like this:

123456789
123456789
123456789
123456789
123456789
123456789
123456789
123456789
123456789

3. If you are in the current director, please enter the following:
	./sudokuValidator answer.txt

4. You should be able to see your answer displayed, and whether your solution is valid.

5. Good luck!

A Project by Fayang Pan, Kalamazoo College, Winter 2014, Operating Systems and Networking.
Feb 14 2014

/**

Known bugs: This program is very bad at handling exceptions... invalid input will break the program.


**/
