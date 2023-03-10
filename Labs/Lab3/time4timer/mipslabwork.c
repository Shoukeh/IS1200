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

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
    display_string( 3, "interrupt" );
    display_update();
    return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
    // Init timer
    T2CON = 0x0070;
    PR2 = 31250;
    IEC(0) = 0x100; // enable interrupts T2
    IFS(0) = 0x000;
    IPC(2) = 0x1F; // set highest priority
    T2CON += 0x8000;

    // Init LEDs
    volatile int* initLedE = (volatile int*) 0xbf886100;
    *initLedE = 0x00;

    // Init buttons?
    TRISD = 0xFE0;
    initGol(4);
    return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
    //delay( 1000 );
    while (timeoutcount < 1) {
        if (IFS(0) & 0x100) {
            IFSCLR(0) = 256;
            timeoutcount++;
        }
    } timeoutcount = 0;

    //time2string( textstring, mytime );
    //display_string( 3, textstring );
    //display_update();
    //tick( &mytime );

    volatile int* writeLedE = (volatile int*) 0xbf886110;
    *writeLedE += 0x1;
    updateMatrix();
    setRow1(icon);
    setRow2(icon2);
    setRow3(icon3);
    setRow4(icon4);
    //icon[3] = 255;
    display_image(0, icon, icon2, icon3, icon4);
    //icon[32] += 4;
}


// Lab questions:
/*
1. Nothing due to switch case
2. Edits bit specific pins. 0x0001 on TRISESET will only set led0.
3. Basic IO Shield ref manual as well as Uno32 board ref manual
3.7.1 on Uno32, Hardware Overview and Appendix A on shield ref
4. v0/v1  
*/ 