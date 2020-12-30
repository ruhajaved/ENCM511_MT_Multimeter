# ENCM511_MT_Multimeter

## Introduction

### Problem Statement

This project aimed to design a multi-meter capable of measuring voltage, resistance, and the amplitude and frequency of a pulse signal, to be displayed on the computer terminal. This was to be done using the PIC24F16KA101 MCU and its peripherals.

### Project Objective

The project objectives included:

1.	To gain experience with embedded programming in C on the application level, with a focus on using peripherals like GPIOs, timers, and ADC modules.
2.	To solidify general embedded programming concepts, such as power, software, and hardware optimization methods.
3.	To introduce and achieve real-time operations and applications.

## Technologies

The technologies used include:

1. MPLAB IDE v5.40 (XC16 compiler)
2. PIC24F16KA101 MCU
3. ANSI C

## Launch

In order to successfully execute this project in terms of hardware, ensure that your hardware is:

1. Set up according to the diagram in the "Midterm-PulseMeter v2.pdf" document. 
2. In addition to this diagram, another pin was used. Ensure that you also connect pin RA6 to RB15 using a 1K resistor. 
3. For the voltmeter mode, a 10K potentiometer is used. All three pins are used, with the top connected to VDD, bottom connected to GND, and the middle connected to the respective GPIO (AN5).
4. For the ohmmeter mode, a 10K potentiometer is also used. Here only two pins are used, the middle pin and one of the other pins. The middle pin is connected to GPIO AN11 and forms a voltage divider configuration with a reference resistor as shown in "Midterm-PulseMeter v2.pdf".

In terms of running the program, build the project, downlaod it to the PIC, and ensure that the program is currently "playing".
