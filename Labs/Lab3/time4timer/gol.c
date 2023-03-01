#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <stdlib.h>
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */

#define ROWS 32
#define COLS 128
void *stdout;

// Define two 2D arrays
char ppMatrix[ROWS][COLS];
char nextMatrix[ROWS][COLS];

// fill the 2D array with "dead cells"
void clearMatrix() {
    int r,c;
    for (r = 0; r < ROWS; r++) {
        for (c = 0; c < COLS; c++) nextMatrix[r][c] = '-';
    }
}

//initializes a matrix based on the chosen state (1,2,3,R)
void initMatrix(int state) {
    int r,c;
    for (r = 0; r < ROWS; r++) {
        for (c = 0; c < COLS; c++) ppMatrix[r][c] = '-';
    }
    // initialize mode 1,2,3,R
    switch (state) {
    case 1: //Glider
        ppMatrix[1][2] = 'o';
        ppMatrix[2][3] = 'o';
        ppMatrix[3][1] = 'o';
        ppMatrix[3][2] = 'o';
        ppMatrix[3][3] = 'o';
        break;

    case 2: //Pure glider generator
        //row 11
        ppMatrix[11][62] = 'o';
        ppMatrix[11][63] = 'o';
        ppMatrix[11][64] = 'o';
        ppMatrix[11][65] = 'o';

        //row 13
        ppMatrix[13][60] = 'o';
        ppMatrix[13][61] = 'o';
        ppMatrix[13][62] = 'o';
        ppMatrix[13][63] = 'o';
        ppMatrix[13][64] = 'o';
        ppMatrix[13][65] = 'o';
        ppMatrix[13][66] = 'o';
        ppMatrix[13][67] = 'o';

        //row 15
        ppMatrix[15][58] = 'o';
        ppMatrix[15][59] = 'o';
        ppMatrix[15][60] = 'o';
        ppMatrix[15][61] = 'o';
        ppMatrix[15][62] = 'o';
        ppMatrix[15][63] = 'o';
        ppMatrix[15][64] = 'o';
        ppMatrix[15][65] = 'o';
        ppMatrix[15][66] = 'o';
        ppMatrix[15][67] = 'o';
        ppMatrix[15][68] = 'o';
        ppMatrix[15][69] = 'o';

        //row 17
        ppMatrix[17][60] = 'o';
        ppMatrix[17][61] = 'o';
        ppMatrix[17][62] = 'o';
        ppMatrix[17][63] = 'o';
        ppMatrix[17][64] = 'o';
        ppMatrix[17][65] = 'o';
        ppMatrix[17][66] = 'o';
        ppMatrix[17][67] = 'o';

        //row 19
        ppMatrix[19][62] = 'o';
        ppMatrix[19][63] = 'o';
        ppMatrix[19][64] = 'o';
        ppMatrix[19][65] = 'o';
        break;

    case 3: //Gosper glider gun
        break;

    case 4: ;//R
        int i,k;
        for (i = 0; i < ROWS; i++) {
            for (k = 0; k < COLS; k++) {
                int seed = k + i + i;
                //srand(seed);
                int ran = random();
                if (ran%2 == 1) {
                    ppMatrix[i][k] = 'o';
                }   
            }
        }
        break;
    }
}

//count all neighbours of a given cell
int countNeighbors(int r, int c) {
    int count = 0;
    int i,j;
    for (i = -1; i < 2; i++) {
        for (j = -1; j < 2; j++) {
            if (i == 0 && j == 0) continue; //ignore self
            int row = r + i;
            int col = c + j;
            //wraparound checks and adjustments
            if (row < 0) row = 31;
            if (row > 31) row = 0;
            if (col < 0) col = 127;
            if (col > 127) col = 0;
            //add to count if a "alive" neighbor is found
            if (ppMatrix[row][col] == 'o') count += 1;
        }
    }
    //if (count > 1) printf("%d\n",count);
    return count;
}

//Updates the matrix
void updateMatrix() {
    int neighbours = 0;
    int i,j;
    //Cycle thru all cells
    for (i = 0; i < ROWS; i++){
        for (j = 0; j < COLS; j++){
            neighbours = countNeighbors(i, j);
            if (ppMatrix[i][j] == 'o'){
                if (neighbours == 2 || neighbours == 3) {
                    nextMatrix[i][j] = 'o';
                } else {
                    nextMatrix[i][j] = '-';
                }
            } else {
                if (neighbours == 3) {
                    nextMatrix[i][j] = 'o';
                } else {
                    nextMatrix[i][j] = '-';
                }
            }
        }
    }
    //TEMP: copy contents, looking for a more efficient way to do this later
    for (i = 0; i < ROWS; i++){
        for (j = 0; j < COLS; j++){
            ppMatrix[i][j] = nextMatrix[i][j];
        }
    }
    //Clear the "temp" nextMatrix before the next update
    clearMatrix();
}

void initGol(int state) {
    clearMatrix();
    //init the ppMatrix with a preset
    //1: gldier, 2: pure glider gen
    //3: UNK, 4: (R:) Random
    initMatrix(state);
}

void setRow1 (uint8_t *row) {
    int i, j, k;
    int arr[8];
    for (i = 0; i < 128; i++) {
        for (j = 0; j <= 7; j++) {
            srand(j*i);
            int ran2 = rand() % 255;
            row[0] = ran2;
            if (ppMatrix[j][i] == 'o') {
                arr[j] = 1;
            } else {
                arr[j] = 0;
            }
        }
        int temp;

        for(k = 0; k<4; k++){
            temp = arr[k];
            arr[k] = arr[8-k-1];
            arr[8-k-1] = temp;
        }

        int size = 8;
        int binary = 0;
        int base = 1;
        for(k = size-1; k >= 0; k--) {
            binary += arr[k] * base;
            base *= 2;
        }
        row[i] = binary;
    }
    return;
}

void setRow2 (uint8_t *row) {
    int i, j, k;
    int arr[8];
    for (i = 0; i < 128; i++) {
        for (j = 0; j <= 7; j++) {
            if (ppMatrix[j+8][i] == 'o') {
                arr[j] = 1;
            } else {
                arr[j] = 0;
            }
        }

        int temp;
        for(k = 0; k<4; k++){
            temp = arr[k];
            arr[k] = arr[8-k-1];
            arr[8-k-1] = temp;
        }

        int size = 8;
        int binary = 0;
        int base = 1;
        for(k = size-1; k >= 0; k--) {
            binary += arr[k] * base;
            base *= 2;
        }
        row[i] = binary;
    }
    return;
}

void setRow3 (uint8_t *row) {
    int i, j, k;
    int arr[8];
    for (i = 0; i < 128; i++) {
        for (j = 0; j <= 7; j++) {
            if (ppMatrix[j+16][i] == 'o') {
                arr[j] = 1;
            } else {
                arr[j] = 0;
            }
        }

        int temp;
        for(k = 0; k<4; k++){
            temp = arr[k];
            arr[k] = arr[8-k-1];
            arr[8-k-1] = temp;
        }

        int size = 8;
        int binary = 0;
        int base = 1;
        for(k = size-1; k >= 0; k--) {
            binary += arr[k] * base;
            base *= 2;
        }
        row[i] = binary;
    }
    return;
}

void setRow4 (uint8_t *row) {
    int i, j, k;
    int arr[8];
    for (i = 0; i < 128; i++) {
        for (j = 0; j <= 7; j++) {
            if (ppMatrix[j+24][i] == 'o') {
                arr[j] = 1;
            } else {
                arr[j] = 0;
            }
        }

        int temp;
        for(k = 0; k<4; k++){
            temp = arr[k];
            arr[k] = arr[8-k-1];
            arr[8-k-1] = temp;
        }

        int size = 8;
        int binary = 0;
        int base = 1;
        for(k = size-1; k >= 0; k--) {
            binary += arr[k] * base;
            base *= 2;
        }
        row[i] = binary;
    }
    return;
}