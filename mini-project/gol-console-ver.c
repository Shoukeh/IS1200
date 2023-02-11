#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    // argc: Provice H and W for grid
    printf("H: %d, W: %d", atoi(argv[1]), atoi(argv[2]));

    char matrix[atoi(argv[1])][atoi(argv[2])];
    char (*pMatrix)[atoi(argv[1])][atoi(argv[2])];;
    pMatrix = &matrix;

    (*pMatrix)[1][2] =  "c";

    for (int i = 0; i < atoi(argv[1]); i++){
        for (int j = 0; j < atoi(argv[2]); j++){
            printf("%c", (*pMatrix)[i][j]);
        }
        printf("\n");
    }
    
}