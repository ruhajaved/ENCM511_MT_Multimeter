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
5. For the UART connection, ensure that the connections to pin RxD and GND are NOT on the same node (top row and bottom row).

In terms of running the program, build the project, download it to the PIC, and ensure that the program is currently "playing". In settings, ensure you power the PIC with atleast 3.25 V. To actually power they system, you can use either a power sypply or your laptop. When programming the PIC, for newer laptops, you can also use the "low-voltage programming mode" option.

## Possible Improvements

Possible improvements for this project include:

1.	Generate the pulse from an external source, rather than the MCU itself. This is desired because with the current setup as the frequency of the pulse changes, so can the base clock. This affects the timing of the system, which in turn will affect the accuracy of the pulse-meter. 
2.	Use CN interrupts with flag bits, instead of while loops, to detect if a given PB is pressed. This is better in terms of software implementation and organization.
3.	As mechanical pushbuttons are used, implement functionality that filters out debounce effects.

