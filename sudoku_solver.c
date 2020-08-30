/*
Implementation of the Backtracking technique for solving any Sudoku puzzle. 
Instead of generating the 9^81 possible combinations, the Backtracking algorithm
only checks the value set in a square, given an assumed value for the previous square.
Author: Tomas Coronado Gonzalez
Date: September 2020
*/

#include<stdio.h>
#define N 9

void print_board(int bo[][N]);
int find_empty(int bo[][N], int pos[]);          // Function that finds the nearest empty square (to the right) to the last one we solved. This function also returns 0 if the sudoku isn't solved yet, or returns 1 if it is already solved
int valid(int bo[][N], int num, int pos[]);      // Function that returns 1 if the number num is valid, for any square, and 0 if not
int solve(int bo[][N]);                          // Recursive function with the backtracking algorithm for solving the sudoku

int board[N][N] = {                              // 0 squares mean empty squares
        {7,8,0,4,0,0,1,2,0},
        {6,0,0,0,7,5,0,0,9},
        {0,0,0,6,0,1,0,7,8},
        {0,0,7,0,4,0,2,6,0},
        {0,0,1,0,5,0,9,3,0},
        {9,0,4,0,6,0,0,0,5},
        {0,7,0,3,0,0,0,1,2},
        {1,2,0,0,0,7,4,0,0},
        {0,4,9,2,0,6,0,0,7},
    };
int position[2] = {0,0};                         // Position of any empty square; pos[0] is the row and pos[1] is the column
    
int main(){
    int a;
    printf("Sudoku:\n");
    print_board(board);

    a = solve(board);
    if (a){
        printf("\nSolution:\n");
        print_board(board);
    }
    else printf("\nSolution not found, the initial board is invalid:");

    return 0;
}

void print_board(int bo[][N]){
    int i,j;

    for (i=0;i<N;i++){
        if (i%3 == 0 && i != 0) printf("---------------------\n");

        for (j=0;j<N;j++){
            if (j%3 == 0 && j != 0) printf("| ");

            if (j != N-1) printf("%d ", bo[i][j]);
            else printf("%d\n", bo[i][j]);
        }
    }
}

int find_empty(int bo[][N], int pos[]){          // We use pos[] as an argument to return the position of the empty square we are searching
    int i,j;

    for (i=0;i<N;i++){
        for (j=0;j<N;j++){
            if (bo[i][j] == 0){
                pos[0] = i;
                pos[1] = j;
                return 0;
            } 
        }
    }

    return 1;                                    // We return 1 in case there are no more empty squares. This means the puzzle is already solved
}

int valid(int bo[][N], int num, int pos[]){
    int i,j;
    int box[2] = {0,0};                          // The sudoku board is devided in 3x3=9 boxes. The array box[2] tells us in which box is the square  

    // Check row:
    i = pos[0];
    for (j=0;j<N;j++){
        if (bo[i][j] == num && j != pos[1]) return 0;
    }

    // Check column:
    j = pos[1];
    for (i=0;i<N;i++){
        if (bo[i][j] == num && i != pos[0]) return 0;
    }

    // Check box:
    box[0] = pos[0] / 3;
    box[1] = pos[1] / 3;
    for (i = box[0]*3 ; i < box[0]*3 + 3 ; i++){
        for (j = box[1]*3 ; j < box[1]*3 + 3 ; j++){
            if (bo[i][j] == num && i != pos[0] && j != pos[1]) return 0;
        }
    }

    return 1;
}

int solve(int bo[][N]){        
    int n;
    int row_col[2];

    int solved = find_empty(board,position);     // #
    if (solved) return 1;                        // When we reach the last square (bottom-left corner) the algorithm finishes
    else{
        row_col[0] = position[0];
        row_col[1] = position[1];
        // We now loop from 1 to 9 in attemp to put a number in our square
        for (n=1;n<=N;n++){
            if (valid(board,n,row_col)){
                bo[row_col[0]][row_col[1]] = n;

                if (solve(bo)) return 1;  // ##  // We enter again in the solve function, but with the difference that we now have a new number weitten on the board
                                                 // We only return 1 if in # we have checked that the sudoku is solved
                bo[row_col[0]][row_col[1]] = 0;  // This is the backtracking step. We do it if solve() isn't true, which means we've finished the n loop whithout finding a valid number 
            }
        }
        return 0;
    }
}
// We do solve() recursively as long as we continue finding valid numbers and we don't finish the sudoku
// When doing solve() recursively, if there is a time in which the program doesn't find a valid number, it sets the previous square to 0
// In each recursion we call solve() but remember, the privious call to solve is stopped in the n loop and this loop has to continue till the puzzle is solved

// When we finish the sudoku the last call of solve() returns 1, because of #, and thus all the previous calls return 1 as well because of ##
// If in the last call to solve() we've finished its n loop whithout finding a valid number, then we return 0 in that call of solve() and thus, the n loop of the previous call of solve() continues
// The statement ''bo[row_col[0]][row_col[1]] = 0;'' is used for setting the square to 0 (which means empty) if the n loop finishes and it needs more than 9 iterations. We return 0 in that call of solve() and thus, the n loop of the previous call of solve() continues