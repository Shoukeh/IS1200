/*
 pointers.c
 By Juris Homickis
 Last modified: 2023-02-08
*/


#include <stdio.h>

char* text1 = "This is a string.";
char* text2 = "Yet another thing.";
int numbers1[40];         // init an array of 40x2=80 bytes
int numbers2[40];
int *list1 = numbers1;    // create pointers that point to arrays numbers1-2
int *list2 = numbers2;
int count = 0;            // create the counter
int *counter = &count;    // create the pointer to the counter 

void copycodes(char* text, int* list, int* c){
  while(*text != 0){      // loop while the current char is not NULL (0x00)
    char temp = *text;    // Save the current char to a temporary variable
    *list = (int) temp;   // typecast the temp var and save it to the list via pointer
    list++;               // increment all pointers, this is the addi part of the asm program
    text++;
    *c += 1;              // increment the counter via reference
  }
}

void work(){
  copycodes(text1, list1, counter);   // set input arguments a0 to a2, jump to fun copycodes
  copycodes(text2, list2, counter);
}

void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char* c){
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n", 
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));
  
}

int main(void){
  work();

  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);

  endian_proof((char*) &count);
}
