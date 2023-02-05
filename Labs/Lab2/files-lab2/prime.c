/*
 prime.c
 By Juris Homickis
 Last modified: 2023-02-05
*/


#include <stdio.h>

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

int main(void){
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
  return 0;
}
