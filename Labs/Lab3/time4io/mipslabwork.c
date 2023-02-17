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

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
    return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
    // Init LEDs
    volatile int* initLedE = (volatile int*) 0xbf886100;
    *initLedE = 0x00;

    // Init buttons?
    TRISD = 0xFE0;
    return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
    delay( 1000 );
    time2string( textstring, mytime );
    display_string( 3, textstring );
    display_update();
    tick( &mytime );
    volatile int* writeLedE = (volatile int*) 0xbf886110;
    *writeLedE += 0x1;
    display_image(96, icon);

    // get status of buttons and switches
    int buttons = getbtns();
    int newtime = getsw();

    switch (buttons){
        case 1: //BTN2
            newtime = newtime<<4; // Shift the new time to the right "space"
            mytime = mytime & 0xFF0F; // bitwise mask, remove old value
            mytime += newtime;  // add new value, it will fill in the new "hole" of 0s
            break;

        case 2: //BTN3
            newtime = newtime<<8;
            mytime = mytime & 0xF0FF;
            mytime += newtime;
            break;

        case 4: //BTN4
            newtime = newtime<<12;
            mytime = mytime & 0x0FFF;
            mytime += newtime;
            break;

    }
}
