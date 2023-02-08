/*
 print-prime.c
 By Juris Homickis
 Last modified: 2023-02-05
*/


#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6
int col_flag = 1;

// Checks if input int n is prime by dividing it (modulo) by every number up until itself (inefficient but simple).
// If n mod i is 0, meaning it is perfectly divisible by anything that isnt itself or 1, then it is not a prime.
// The function then returns 0 immediately. If all numbers fail to meet this condition, it returns 1 as it is prime.
int is_prime(int n){
    while(1) {
        for (int i = 2; i < n; i++) {
            if (n % i == 0) {
                return 0;
            }
        }
        return 1;
    }
}

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

// function from lab 1
void print_primes(int n){
  for (int i = 2; i <= n; i++){
      int prime_flag = 0;
      prime_flag += is_prime(i);
      if (prime_flag == 1) {
          print_number(i);
          prime_flag = 0;
      }
  }
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_primes(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}

 
