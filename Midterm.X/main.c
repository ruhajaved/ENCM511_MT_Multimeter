/*
 * File:   main.c
 * Author: Rushi V
 *
 * Created on September 26, 2020, 9:17 PM
 */

// MPLAB header libraries
#include <xc.h>
#include <p24fxxxx.h>
#include <p24F16KA101.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>

// User header files
#include "IOs.h"
#include "ChangeClk.h"
#include "UART2.h"
#include "ADC.h"

// Clock control
#pragma config IESO = OFF // 2 Speed Startup disabled
#pragma config FNOSC = FRC // Start up CLK = 8 MHz
#pragma config FCKSM = CSECMD // Clock switching is enabled, clock monitor disabled
#pragma config SOSCSEL = SOSCLP // Secondary oscillator for Low Power Operation
#pragma config POSCFREQ = MS //Primary Oscillator/External clk freq betwn
#pragma config OSCIOFNC = ON //CLKO output disabled on pin 8, use as IO.
#pragma config POSCMOD = NONE // Primary oscillator mode is disabled

// MACROS for Idle, Sleep modes
#define Nop() {__asm__ volatile ("nop");}
#define ClrWdt() {__asm__ volatile ("clrwdt");}
#define Sleep() {__asm__ volatile ("pwrsav #0");}      //Sleep() - put MCU in sleep mode - CPU and some peripherals off
#define Idle() {__asm__ volatile ("pwrsav #1");}       //Idle() - put MCU in idle mode - only CPU off
#define dsen() {__asm__ volatile ("BSET DSCON, #15");}
//#define clkval 32; // in kHz

//Test 1 and 2
//unsigned int clkval = 8;                                // set clk value wanted

// Test 3 and 4
unsigned int clkval = 500;                            // set clk value wanted


void main() 
{
     NewClk();   // set clk to clkval
     IOinit();   // call IOinit to initialize the IO ports
     InitUART2(); // call InitUART2 to initialize the UART
     
     //Clock output on REFO/RB15, PULSE GEN Testing purposes only
     TRISBbits.TRISB15 = 0; // Set RB15 as output for REFO
     REFOCONbits.ROSSLP = 1; // Ref oscillator is disabled in sleep
     REFOCONbits.ROSEL = 0; // Output base clk showing clock switching
     
     //Test 1 and test 3
     //REFOCONbits.RODIV = 0b1001;        // set value for base clock divisor
     
     //Test 2
     //REFOCONbits.RODIV = 0b1111;      // set value for base clock divisor
     
     //Test 4
     REFOCONbits.RODIV = 0b0111;      // set value for base clock divisor
     
     REFOCONbits.ROEN = 1; // Ref oscillator is enabled
    
    while(1)
    {
        IOcheck(); // / call IOcheck to carry out different system states
    }
    
    return;
}
