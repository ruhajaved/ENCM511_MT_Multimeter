 
#ifndef IOs_H
#define	IOs_H

#include <xc.h>     // include header file xc.h

void IOinit();          // function declaration for IOinit function
void IOcheck();         // function declaration for IOcheck function
void outputR(uint16_t); // function declaration for outputR function
void outputV(uint16_t); // function declaration for outputV function
void outputf();         // function declaration for outputf function
void outputA(uint16_t); // function declaration for outputA function
extern unsigned int clkval; // use global variable clkval

#endif

