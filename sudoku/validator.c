#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 27
/*
*
Date: Feb 14, 2014
Author: Fayang Pan
This is a sudoku validator, for Programming Project 2, Operating Systems class, Winter 2014, Kalamazoo College.

This program creates 27 threads to check each row, column, and sub squares.

Referred to http://phanderson.com/files/file_read.html for reading files in.

Thanks go to Mehmet for his help.
**/


void *check();
FILE *file;
int sudoku[9][9];
int valid = 1;

int main(int argc, char *argv[])
{
	// Initialize pthreads
	pthread_t tid[NUM_THREADS];
	pthread_attr_t attr;
	int tCount = 0;
	
	// Read the numbers from a txt file.
	file = fopen(argv[1], "rt");
	if (argc !=2){
		fprintf(stderr, "usage: a.out <integer value> \n");
		return -1;
	}
	int count;
	for (count = 0; count< 9; count++){	
		fscanf(file,"%1d%1d%1d%1d%1d%1d%1d%1d%1d", &sudoku[count][0] , &sudoku[count][1], &sudoku[count][2], &sudoku[count][3], &sudoku[count][4], &sudoku[count][5], &sudoku[count][6], &sudoku[count][7], &sudoku[count][8]);
	}

	
	// Prints out the suduku matrix, and create sudokuTranspose, a transpose of the sudoku matrix.
	int i;
	int j;
	int sudokuTransposed[9][9];
	for (i = 0; i < 9; i++){
		for (j = 0; j < 9; j ++){
			sudokuTransposed[j][i] = sudoku[i][j];
			printf("%d",sudoku[i][j]);
			printf(", ");
		}
		printf("\n");
	}

	

	// Put each sub square into an array, creating sudokuSubSquare two dimensional array of 9*9.
	int col;
	int row;
	int tempCount = 0;
	int sudokuSubSquare[9][9];
	for (row = 0; row < 3; row++){
		for (col = 0; col < 3; col++){
			sudokuSubSquare[0][tempCount] = sudoku[row][col];
			sudokuSubSquare[1][tempCount] = sudoku[row][col+3];
			sudokuSubSquare[2][tempCount] = sudoku[row][col+6];
			sudokuSubSquare[3][tempCount] = sudoku[row+3][col];
			sudokuSubSquare[4][tempCount] = sudoku[row+3][col+3];
			sudokuSubSquare[5][tempCount] = sudoku[row+3][col+6];
			sudokuSubSquare[6][tempCount] = sudoku[row+6][col];
			sudokuSubSquare[7][tempCount] = sudoku[row+6][col+3];
			sudokuSubSquare[8][tempCount] = sudoku[row+6][col+6];
			tempCount++;
		}
	}

	// Creates multiple threads to handle every row of each matrix.
	pthread_attr_init(&attr);
	for (row = 0; row<9; row++){
		pthread_create(&tid[tCount], &attr, check, &sudoku[row]);
		tCount++;
		pthread_create(&tid[tCount], &attr, check, &sudokuTransposed[row]);
		tCount++;
		pthread_create(&tid[tCount], &attr, check, &sudokuSubSquare[row]);
		tCount++;
	}

	
	// Joins every thread and prints the result.
	for (i = 0; i<NUM_THREADS; i++)
	{
		pthread_join(tid[i], NULL);
	}

	if (valid == 1){
		printf ("This solution is right!\n");
	}
	else{
		printf ("There is something wrong...\n");
	}

/**	
	// Test of check method.
	printf("valid = %d\n",valid);
	int test[9] = {3,7,4,5,6,8,9,1,2};
	check(&test);
	printf("valid = %d\n", valid);
**/
}

// Check for validity of 9 numbers: if they are numbers 1-9 or not.
void *check(int* array)
{
	int array2[9] = {0,0,0,0,0,0,0,0,0};
	int i;
	for (i = 0; i<8; i++){
		int temp = *array-1;
		array2[temp] = 1; 
		array++;
	}
	array2[*array-1] = 1;

	for (i = 0; i<9; i++){
		if (array2[i]==0){
			valid = -1;
		}
	}
	pthread_exit(0);
}
