/*	Author: Sana
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #6  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "../header/timer.h"
#endif

enum States {start, pb0, waitfall, wait, pb1, pb2, pb11} state;

unsigned char A0 = 0x00;

void Tick() {
	switch(state) {
		case start:
			state = pb0;
			break;
		case pb0:
			if (!A0) state = pb1;
			else state = waitfall;
			break;
		case pb1:
			if (!A0) state = pb2;
			else state = waitfall;
			break;
		case pb2:
			if (!A0) state = pb11;
			else state = waitfall;
                        break;
		case pb11:
			if (!A0) state = pb0; 
			else state = waitfall;
			break;
		case waitfall:
                        if (!A0) state = wait;
                        else state = waitfall;
                        break;
                case wait:
                        if (!A0) state = wait;
                        else state = pb0;
                        break;
		default:
			state = start;
			break;
	};
	switch(state) {
		case pb0:
			PORTB = 0x01;
			break;
		case pb1:
			PORTB = 0x02;
			break;
		case pb2:
			PORTB = 0x04;
			break;
		case pb11:
			PORTB = 0x02;
			break;
		case waitfall:  break;
                case wait:      break;
		default: 	break;
	};
}
	
int main(void) {
	DDRA = 0x00; // Set port A to input
	DDRB = 0xFF; // Set port B to output
	PORTA = 0xFF; //Init port A to 0xFF
	PORTB = 0x00; // Init port B to 0x00
	TimerSet(300);
	TimerOn();

    while (1) {
	A0 = (~PINA & 0x01);
	Tick();
	while(!TimerFlag); // Wait 1 sec
	TimerFlag = 0;
    }
    return 1;
}
