#include <stdio.h>
#include <stdlib.h>

char** ppMatrix;

// free allocated memory
void freeMatrix(int rows) {
    for (int r = 0; r < rows; r++) {
        free(ppMatrix[r]);
    }
    free(ppMatrix);
}

// Print the matrix. You could probably calculate the 
void printMatrix(int rows, int cols) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) printf("%2c", ppMatrix[r][c]);
        printf("\n");
    }
}

// test function to see how accessing the 2D array works
void editElement(int r, int c) {
    ppMatrix[r-1][c-1] = 'o';
}


int main(int argc, char *argv[]){
    // argc: Provice H and W for grid
    int row = atoi(argv[1]);
    int col = atoi(argv[2]);
    printf("H: %d, W: %d\n", row, col);

    // create the 2D array: a double pointer that points to an array of pointers
    // that point to an array of chars. Cool stuff!
    ppMatrix = (char**)malloc(row * sizeof(char*));
    for (int i = 0; i < row; i++) {
        ppMatrix[i] = (char*)malloc(col * sizeof(char));
    }

    // fill the 2D array with "dead cells". Just something so that it can be printed
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) ppMatrix[r][c] = '-';
    }

    editElement(2,3);

    printMatrix(row, col);

    freeMatrix(row);
    
}