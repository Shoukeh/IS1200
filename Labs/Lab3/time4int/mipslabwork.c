/* mipslabwork.c

This file written 2015 by F Lundevall
Updated 2017-04-21 by F Lundevall



This file should be changed by YOU! So you must
add comment(s) here with your name(s) and date(s):

Edited on 17-02-23 by Juris Homickis

For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;
int timeoutcount = 0;
int prime = 1234567;
volatile int* writeLedE = (volatile int*) 0xbf886110;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void ) {
    if (IFS(0) & 0x8000) {
        IFSCLR(0) = 0x8000;
        PORTE += 1;
        display_string( 3, "interrupt" );
    }
    if (IFS(0) & 0x100) IFSCLR(0) = 0x100; timeoutcount++;
    if (timeoutcount == 10) {
        time2string( textstring, mytime );
        display_string( 3, textstring );
        display_update();
        tick( &mytime );
        timeoutcount = 0;
    }
}

/* Lab-specific initialization goes here */
void labinit( void )
{
    // Init timer
    INTCONSET = 0x8;
    T2CON = 0x0070;
    PR2 = 31250;
    IECSET(0) = 0x100;
    IECSET(0) = 0x8000;
    IFS(0) = 0x00000000;
    IPC(2) = 0x1F; // set highest priority
    IPC(3) = 0x05000000;
    T2CON += 0x8000;

    // Init LEDs
    volatile int* initLedE = (volatile int*) 0xbf886100;
    *initLedE = 0x00;
    PORTE = 0x00;

    // Init buttons?
    TRISD = 0xFE0;

    enable_interrupt();
    
    return;
}

/* This function is called repetitively from the main program */
void labwork( void ) {
    prime = nextprime( prime );
    display_string( 0, itoaconv( prime ) );
    display_update();
}