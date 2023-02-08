/*
 sieves-heap.c
 By Juris Homickis
 Last modified: 2023-02-08
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COLUMNS 6
int col_flag = 1;

// Prints a number and uses a global variable to keep track of which column it is on right now. If it is on col 6,
// print the last number, print new line, reset global column flag.
void print_number(int n){
    if(col_flag != COLUMNS) {
        printf("%10d ", n);
        col_flag += 1;
    } else {
        printf("%10d ", n);
        printf("\n");
        col_flag = 1;
    }
}


void print_sieves(int n) {
    // create the heap, allocate n bytes to it
    unsigned char *numbers;
    numbers = malloc(n*sizeof(unsigned char));
    // Populate the array
    for (int i = 0; i <= n; i++) {
        numbers[i] = (char) (i+1);
    }

    // print the array
    /* for (int i=0; i<n; i++) {
        int temp = (int) numbers[i];
        temp += 256*(floor((i+1)/256));
        print_number(temp);
    } */

    // set the trues and falses as per wikipedia psuedocode alg
    for (int i = 0; i < sqrt(n); i++) {
        if (i==0) {
            numbers[i] = (char) 0;
            continue;
        }
        // offset. Since unsigned char only goes up to 255, we just add the carry bits manually
        int temp = (int) numbers[i];
        temp += 256*(floor((i+1)/256));
        if (temp > 0){
            for (int j = (i+1)*(i+1); j <= n; j+=(i+1)) {
                // here, False is implemented by setting the number at id j-2 to 0. True would mean having anything that is > 0
                numbers[j-1] = (char) 0;
            }
        }
    }

    // print any number that is not "false"
    for (int i = 0; i < (n-1); i++){
        if (numbers[i] > 0) {
            int temp = (int) numbers[i];
            temp += 256*(floor((i+1)/256));
            print_number(temp);
        }
    }

    // free heap
    free(numbers);
}


// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
// maxval approx 8 360 000
int main(int argc, char *argv[]){
    if(argc == 2)
        print_sieves(atoi(argv[1]));
    else
        printf("Please state an interger number.\n");
    return 0;
}
