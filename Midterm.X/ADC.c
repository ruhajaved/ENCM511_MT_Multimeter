/* 
 * File:   ADC.c
 * Author: ruhajaved
 *
 * Created on November 22, 2020, 4:14 PM
 */
#include <xc.h>
#include "ADC.h"
#include <stdio.h>

uint16_t do_ADC(uint16_t mode)  
{
    uint16_t ADCvalue;          // declare variable to store ADCvalue
    
    AD1CON1bits.ADON = 0;       // turn off ADC module
    AD1CON1bits.FORM = 0b00;    // set data output format to integer
    AD1CON1bits.SSRC = 0b111;   // set ADC conversion to auto-convert
    AD1CON1bits.ASAM = 0;       // sample when SAMP bit is set
    
    AD1CON2bits.VCFG = 0b000;   // select reference voltages Vdd and Vss
    AD1CON2bits.CSCNA = 0;      // set such that inputs aren't scanned
    AD1CON2bits.BUFM = 0;       // configure buffer as a 16-word buffer
    AD1CON2bits.ALTS = 0;       // always use MUXA input settings  
    AD1CON2bits.SMPI = 0;       // interrupts at the completion of conversion for each sample sequence
    
    AD1CON3bits.ADRC = 0;       // use system clock
    AD1CON3bits.SAMC = 0b00001; // set sampling time to the fastest possible
    
    AD1CHSbits.CH0NA = 0;       // set negative input for channel 0 to Vr-
    
    if (mode == 1)              // if in voltmeter mode
       AD1CHSbits.CH0SA = 0b0101;  // set positive input for channel 0 to Voltage at AN5 
    else if (mode == 2)         // if in ohmmeter mode
       AD1CHSbits.CH0SA = 0b1011;  // set positive input for channel 0 to Voltage at AN11
    else                        // if in pulse meter mode
       AD1CHSbits.CH0SA = 0b1100;  // set positive input for channel 0 to Voltage at AN12
   
    AD1CSSL = 0;                // omit analog channel from input scan
    
    AD1CON1bits.DONE = 0;       // clear ADC done bit
    
    IPC3bits.AD1IP = 7;         // set priority level of ADC interrupt to 7
    IFS0bits.AD1IF = 0;         // clear ADC interrupt flag
    IEC0bits.AD1IE = 1;         // enable ADC interrupt
    AD1CON1bits.ADON = 1;       // turn on ADC module
    AD1CON1bits.SAMP=1;         // start sampling
    
    Idle();                     // put MCU in idle mode until ADC interrupt occurs
    
    ADCvalue = ADC1BUF0;        // store ADC value in ADCvalue
    
    return (ADCvalue);          // return ADCvalue
}

void __attribute__((interrupt, no_auto_psv))_ADC1Interrupt(void)
{
    IFS0bits.AD1IF = 0;         // clear ADC interrupt flag
    AD1CON1bits.SAMP = 0;       // turn off sampling
    AD1CON1bits.ADON = 0;       // turn off ADC module
}
