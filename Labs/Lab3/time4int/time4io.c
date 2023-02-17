#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h" 

int getsw (void) {
    // 0xF00
    int status = PORTD;
    status = status>>8;
    status = status & ~0xFF00; //bitwise mask with 0b1111
    return status;
}

int getbtns (void) {
    int status = PORTD;
    status = status>>5;
    status = status & 7; //bitwise mask with 0b0111
    return status;
}