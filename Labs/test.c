#include <stdio.h>
#include <stdlib.h>

int main() {
    int arr[] = {0,1,0,1,1,1,0,0};
    int size = sizeof(arr) / sizeof(arr[0]);

    int binary = 0;
    int base = 1;
    for(int i = size-1; i >= 0; i--) {
        binary += arr[i] * base;
        base *= 2;
    }

    printf("Binary: 0x%x\n", binary);
    return 0;
}