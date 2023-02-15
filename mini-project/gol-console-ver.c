#include <stdio.h>
#include <stdlib.h>

char** ppMatrix;

int main(int argc, char *argv[]){
    // argc: Provice H and W for grid
    int row = atoi(argv[1]);
    int col = atoi(argv[2]);
    printf("H: %d, W: %d\n", row, col);

    ppMatrix = (char**)malloc(row * sizeof(char*));
    for (int i = 0; i < row; i++) {
        ppMatrix[i] = (char*)malloc(col * sizeof(char));
    }

    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) ppMatrix[r][c] = 'o';
    }

    ppMatrix[2][3] = '-';

    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) printf("%2c", ppMatrix[r][c]);
        printf("\n");
    }

    for (int r = 0; r < row; r++) {
        free(ppMatrix[r]);
    }
    
    free(ppMatrix);
    
}