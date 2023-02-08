#include <stdio.h>

char* text1 = "This is a string.";
int counter = 0;
int *count = &counter;
int *plist = NULL;


void main(){
    int list[20];
    plist = list;
    while(*text1 != 0){
        printf("Current char hex: 0x%03X, char: %c\n", (int) *text1, *text1);
        char temp = *text1;
        *plist = (int) temp;
        printf("List char hex: 0x%03X, char: %c\n", *plist, (char) *plist);
        plist++;
        text1++;
        *count += 1;
    }
    printf("%d",*count);
}