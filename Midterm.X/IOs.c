/* 
 * File:   IOs.c
 * Author: ruhajaved
 *
 * Created on October 11, 2020, 1:02 PM
 */

#include <xc.h>          // include header file xc.h
#include "IOs.h"        // include header file IOs.h
#include "ADC.h"        // include header file ADC.h

static uint16_t TMR2_cnt; // global variable to keep track of TMR2 value

void IOinit() 
{
   
   AD1PCFGbits.PCFG5 = 0;  // configure AN5 as an analog pin - voltmeter mode
   AD1PCFGbits.PCFG11 = 0; // configure AN11 as an analog pin - ohmmeter mode
   AD1PCFGbits.PCFG12 = 0; // configure AN12 as an analog pin - pulse meter mode
   
   TRISAbits.TRISA2 = 1; // make GPIO RA2 a digital input
   CNPU2bits.CN30PUE = 1; // enable pull up resistor on RA2/CN30
   
   TRISAbits.TRISA4 = 1; // make GPIO RA4 a digital input
   CNPU1bits.CN0PUE = 1; // enable pull up resistor on RA4/CN0
   
   TRISBbits.TRISB4 = 1; // make GPIO RB4 a digital input
   CNPU1bits.CN1PUE = 1; // enable pull up resistor on RB4/CN1
   
   TRISAbits.TRISA6 = 1; // make GPIO RA6 a digital input - this is connected to RB15
   
    IPC4bits.CNIP = 6; // set CN interrupt priority to 6 (ADC is 7)
    IFS1bits.CNIF = 0; // Clear CN interrupt flag
    
   return;
}

void IOcheck()
{
    uint16_t mode;      // declare variable to keep track of mode and use to configure ADC
    uint16_t ADCvalue;  // declare variable to store the ADC value
    
     while (PORTAbits.RA2 == 0 && PORTBbits.RB4 == 1 && PORTAbits.RA4 == 1) // while RA2, pb1 is pressed - voltmeter
     {
        mode = 1;                  // set mode to 1
        ADCvalue = do_ADC(mode);   // call do_ADC to do ADC conversion on AN5
        outputV(ADCvalue);         // print voltage value corresponding to ADCvalue
     }
    
     while (PORTAbits.RA2 == 1 && PORTBbits.RB4 == 1 && PORTAbits.RA4 == 0) // while RA4, pb2 is pressed - ohmmeter
     {
        mode = 2;                   // set mode to 2
        ADCvalue = do_ADC(mode);    // call do_ADC to do ADC conversion on AN11
        outputR(ADCvalue);          // print resistance value
     }
    
    while (PORTAbits.RA2 == 1 && PORTBbits.RB4 == 0 && PORTAbits.RA4 == 1) // while RB4, pb3 is pressed - pulse meter mode
    {
        mode = 3;                   // set mode to 3
        CNEN1bits.CN8IE = 1;        // enable CN on CN8
        IEC1bits.CNIE = 1;          // enable CN interrupts
        Idle();                     // put MCU in idle until pulse reaches a rising edge and measure time from falling to rising edge
        ADCvalue = do_ADC(mode);    // calculate amplitude
        outputf();                  // calculate and display pulse signal frequency
        outputA(ADCvalue);          // display amplitude           
    }
    
    return;
}

void outputV(uint16_t ADCvalue)
{
    float v_meas = ADCvalue * 0.00317; // VDD = 3.25 V, Vres = 0.00317, calculate voltage in V corresponding to ADCvalue
    char buf[50];                      // array to store output string
    sprintf(buf, "\rVOLTMETER Voltage = %4.3f V                     ", v_meas);  // format output string
    Disp2String(buf);                                                            // display voltage, formatted
    
    return;
}

void outputR(uint16_t ADCvalue)
{
    float R = 1000.0 * ADCvalue / (1023 - ADCvalue); // calculate resistance using 1000*V2 / (VDD - V2), in ohms
    char buf[50];                                    // array to store output string
    sprintf(buf, "\rOHMMETER Resistance = %7.2f Ohms             ", R); // format output string
    Disp2String(buf);                                                   // display resistance, formatted
    
    return;
}

void outputf()
{
    uint16_t clk = clkval;          // store clkval in temporary variable
    
    if (clkval == 8)                // if clkval is 8MHz
        clk *= 1000;                // then * 1000 to convert clk value into kHz

    float t = TMR2_cnt * 2.0/clk;   // time passed from falling edge to rising edge for pulse signal
    float f = 1 / (2*t);            //  pulse signal frequency in kHz
    char buf[40];                   // array to store output string
    sprintf(buf, "\rPULSEMETER Freq = %5.3f kHz,", f);  // format output string
    Disp2String(buf);                                   // display frequency, formatted
    
    return;
}

void outputA(uint16_t ADCvalue)
{
    float v_meas = ADCvalue * 0.00317; // VDD = 3.25 V, Vres = 0.00317, calculate amplitude corresponding to ADCvalue
    char buf[40];                      // array to store output string
    sprintf(buf, " Amplitude = %4.3f V  ", v_meas);                 // format output string
    Disp2String(buf);                                               // display amplitude, formatted
    
    return;
}

void __attribute__((interrupt, no_auto_psv))_CNInterrupt(void)
{
	IFS1bits.CNIF = 0;		 // clear IF flag
    if (PORTAbits.RA6 == 0)  // if pulse is low
    {
        TMR2 = 0;            // clear TMR2
        T2CONbits.TON = 1;   // start TMR2
        Idle();              // put MCU in idle
    }

    T2CONbits.TON = 0;              // turn off TMR2 once pulse reaches a rising edge
    TMR2_cnt = TMR2;                // store TMR2 value in TMR2_cnt
    IEC1bits.CNIE = 0;              // disable CN interrupts
    CNEN1bits.CN8IE = 0;            // disable CN on CN8
    
    return;
}

