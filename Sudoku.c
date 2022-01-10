//Sudoku Project
//Authors: Spencer Chambers, Evan Japundza
//Last Modified: 12/9/2021

#include<stdio.h>
#include<stdlib.h>

//asks user's input to fill board
void fill_sudoku(int board[9][9]);

//prints full sudoku board
void print_sudoku(int board[9][9]);

//checks if move is legal with sudoku's rules
int check_valid(int board[9][9], int row, int col, int value);

//actually solves and fills sudoku board with correct results
int solve_sudoku(int board[9][9]);

//checks if board is full of nonzero numbers
int isFull(int board[9][9]);

//returns next cell of board that needs filled
void getNextEmpty(int board[9][9], int * row, int * col);

int main (void) {

        puts("This program solves a Sudoku Puzzle.");

        int board[9][9];

        fill_sudoku(board); //fill sudoku board with correct numbers

        puts("BOARD BEFORE SOLVING:");
        print_sudoku(board); //print inputted board

        puts("BOARD AFTER SOLVING: ");
        if (solve_sudoku(board) == 1) //if board is finally solved
                print_sudoku(board);

        else //board can not be solved
                puts("ERROR: NO SOLUTION FOUND!!");

}

void fill_sudoku(int board[9][9]) {

        int tempBoard[9][9] = {{2,0,0,0,0,0,6,9,0},
                               {0,5,0,0,0,3,0,0,0},
                               {1,7,0,0,0,9,4,0,5},
                               {0,0,3,0,2,5,0,1,8},
                               {0,0,0,0,4,0,0,0,0},
                               {7,2,0,3,8,0,5,0,0},
                               {5,0,2,6,0,0,0,4,1},
                               {0,0,0,5,0,0,0,7,0},
                               {0,6,7,0,0,0,0,0,3}};

        for (int i = 0; i < 9; i++)
                for (int j = 0; j < 9; j++)
                        board[i][j] = tempBoard[i][j];

}

void print_sudoku(int board[9][9]) {

        //uses dashes to separate board into grid
        //use equal signs to separate between small squares

        puts("");
        for (int i = 0; i < 9; i++) {

                printf("|");
                for (int j = 0; j < 9; j+=3) {
                        printf(" %d   %d   %d  |", board[i][j], board[i][j+1], board[i][j+2]);
                } //prints next 3 numbers in board

                if ((i + 1) % 3 == 0) //every 3 lines, print this instead
                        printf("\n========================================\n");
                else
                        printf("\n----------------------------------------\n");

        }

}

int check_valid(int board[9][9], int row, int col, int value) {

        //Check if Inserting Value into Row is Legal
        for (int i = 0; i < 9; i++) {

                if (board[row][i] == value) //if there's already this value in row
                        return 0; //not valid

        }

        //Check if Inserting Value into Column is Legal
        for (int i = 0; i < 9; i++) {

                if (board[i][col] == value) //if there's already this value in column
                        return 0; //not valid

        }

        //Check if Value is Not In Corresponding Subsquare
        for (int i = 0; i < 9; i++) {

                //if there's already this value in the smaller square
                if (board[3 * (row/3) + i/3][3 * (col/3) + i % 3] == value)
                        return 0; //not valid

        }

        return 1; //If at this point, this move must be valid.

}

int solve_sudoku(int board[9][9]) {

        //Uses Backtracking to Call Function Repeatedly
        //Within every run, the function is called within
        //until board is either completely filled or impossible to solve.

        if (isFull(board)) //if board is full, STOP, board is solved.
                return 1;

        int row = 0;
        int col = 0;

        getNextEmpty(board, &row, &col); //finds next empty cell

        for (int attempt = 1; attempt <= 9; attempt++) { //loop through all possible entries

                if (check_valid(board, row, col, attempt)) { //if this entry is a valid move

                        board[row][col] = attempt; //assign to cell

                        if (solve_sudoku(board)) { //if this eventually leads to a solved board
                                return 1; //solving complete
                        }

                        //if not returned solved, didn't work, so reset cell back to 0
                        board[row][col] = 0;

                }

        }

        return 0; //if gone through all possibilities, board is not solved
}


int isFull(int board[9][9]) {

        for (int i = 0; i < 9; i++) {

                for (int j = 0; j < 9; j++) {

                        if (board[i][j] == 0) //if this value is 0
                                return 0; //value isn't full, so return 0

                }

        }

        return 1; //if at this point, board must be full, return 1

}

void getNextEmpty(int board[9][9], int * row, int * col) {

        for (int i = 0; i < 9; i++) {

                for (int j = 0; j < 9; j++) {

                        if (board[i][j] == 0) { //find next value that is 0
                                *row = i; //assign row to this i value
                                *col = j; //assign col to this j value
                                return; //return to stop any more looping
                        }

                }


        }

}
