//Declan Schaeffer
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Global variables
int vertices[1024][8][8];
int tilingsGenerated = 0; // Amount of tilings completed

// Function declarations
void recursion(int board[8][8], int direction);
int isComplete(int board[8][8]);
int canRight(int board[8][8], int row, int col);
int canDown(int board[8][8], int row, int col);
void printArray(int array[8][8]);

int main() {
    int example[8][8];
    memset(example, 0, sizeof(example)); // Initialize example with zeros

    // Generate example for layer printing
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if ((row < 2 && col < 2) || (row > 5 && col > 5) || (row < 2 && col > 5) || (row > 5 && col < 2))
                example[row][col] = -1;
            else if (row == 7 && (col == 2 || col == 5))
                example[row][col] = -1;
            else if (row == 0 && (col == 2 || col == 5))
                example[row][col] = -1;
            else if (col == 7 && (row == 2 || row == 5))
                example[row][col] = -1;
            else if (col == 0 && (row == 2 || row == 5))
                example[row][col] = -1;
        }
    }

    // Initialize all 1024 grids
    for (int a = 0; a < 1024; a++) 
        memcpy(vertices[a],example,sizeof(vertices[0]));

    // Recursive start
    recursion(example, 1); // Horizontal
    recursion(example, 2); // Vertical

/* Printing random tilings
    printArray(vertices[100]);
    printf("\n");
    printArray(vertices[200]);
    printf("\n");
    printArray(vertices[300]);
    printf("\n");
    printArray(vertices[400]);
    printf("\n");
    printArray(vertices[500]);
    printf("\n");
    printArray(vertices[600]);
    printf("\n");
    printArray(vertices[700]);
    printf("\n");
*/

    //sum for average
    int sums[8][8]={0};
    for(int row=0;row<8;row++){
        for(int col=0;col<8;col++){
            for(int it=0;it<1024;it++){
                if(vertices[it][row][col]==-1) //outside diamond, break
                    break;
                else{
                    if(vertices[it][row][col]==1 || vertices[it][row][col]==3)
                        sums[row][col]++; //incriment 1 for horizontal domino
                    //would put else here, but incriment 0 for vertical dominos, so leaving it alone
                }
            }
        }
    }

    printf("\n%d distinct domino tilings generated\n\nAverage domino orientation at each vertex\nA horizontal domino contributes 1 to the average, while a vertical domino contributes 0\n\n",tilingsGenerated);

    double average[8][8]={0};
    for(int row=0;row<8;row++){
        for(int col=0;col<8;col++){
            average[row][col] = (double)sums[row][col]/1024;
            if (average[row][col] == 0) {
                printf(" [----] "); // Print 'X' for -1 or 0 (background)
            } else {
                printf(" [%.2f] ", average[row][col]); // Print the value otherwise
            }
        }
        printf("\n\n");
    }
    printf("\n");

    return 0;
}



void recursion(int board[8][8], int direction) {
    int pos = isComplete(board);

    /*
    if (direction == 1)
        printf("Attempting to place horizontal domino in array position [%d][%d]\n", pos / 10, pos % 10);
    else
        printf("Attempting to place vertical domino in array position [%d][%d]\n", pos / 10, pos % 10);
    */

    // Place domino from previous parent call
    if (direction == 1) { // Horizontal
        board[pos / 10][pos % 10] = 1;
        board[pos / 10][pos % 10 + 1] = 3;
    } else if (direction == 2) { // Vertical
        board[pos / 10][pos % 10] = 2;
        board[pos / 10 + 1][pos % 10] = 4;
    }

    // Update next open vertex
    int test = isComplete(board);

    if (test == -1) { // Board is complete
        memcpy(vertices[tilingsGenerated], board, sizeof(vertices[0]));
        tilingsGenerated++;

        if(direction==1){ //horizontal
            board[pos/10][pos%10]=0;
            board[pos/10][pos%10+1]=0;
        }
        else if(direction==2){ //vertical domino
            board[pos/10][pos%10]=0;
            board[pos/10+1][pos%10]=0;
        }

        return;
    }

    // Recursively call and place next domino
    if (canRight(board, test / 10, test % 10))
        recursion(board, 1);

    if (canDown(board, test / 10, test % 10)) {
        recursion(board, 2);
    }

    if(direction==1){ //horizontal
        board[pos/10][pos%10]=0;
        board[pos/10][pos%10+1]=0;
    }
    else if(direction==2){ //vertical domino
        board[pos/10][pos%10]=0;
        board[pos/10+1][pos%10]=0;
    }
}

// Return -1 if board is complete, otherwise return row*10 + col
int isComplete(int board[8][8]) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (board[row][col] == 0)
                return row * 10 + col;
        }
    }
    return -1;
}

int canRight(int board[8][8], int row, int col) {
    if (col == 7)
        return 0;
    return board[row][col + 1] == 0;
}

int canDown(int board[8][8], int row, int col) {
    if (row == 7)
        return 0;
    return board[row + 1][col] == 0;
}

// Function to print an 8x8 array
void printArray(int array[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (array[i][j] == -1 || array[i][j] == 0) {
                printf(" X "); // Print 'X' for -1 (background)
            } else {
                printf(" %d ", array[i][j]); // Print the value otherwise
            }
        }
        printf("\n"); // Move to the next row
    }
    printf("\n"); // Add extra space between prints
}
