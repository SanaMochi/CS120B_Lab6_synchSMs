/*	Author: Sana
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #6  Exercise 1
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

enum States {start, pb0, waitfall0, wait0, pb1, waitfall1, wait1, pb2, waitfall2, wait2, pb11, waitfall11, wait11} state;

unsigned char A0 = 0x00;

void Tick() {
	switch(state) {
		case start:
			state = pb0;
			break;
		case pb0:
			if (!A0) state = pb1;
			else state = waitfall0;
			break;
		case waitfall0:
			if (!A0) state = wait0;
			else state = waitfall0;
			break;
		case wait0:
			if (!A0) state = wait0;
			else state = pb1;
			break;
		case pb1:
			if (!A0) state = pb2;
			else state = waitfall1;
			break;
		case waitfall1:
			if (!A0) state = wait1;
			else state = waitfall1;
			break;
		case wait1:
			if (!A0) state = wait1;
			else state = pb2;
			break;
		case pb2:
			if (!A0) state = pb11;
                        else state = waitfall2;
                        break;
                case waitfall2:
                        if (!A0) state = wait2;
                        else state = waitfall2;
                        break;
                case wait2:
                        if (!A0) state = wait2;
                        else state = pb11;
			break;			
		case pb11:
			if (!A0) state = pb0; 
                        else state = waitfall11;
                        break;
                case waitfall11:
                        if (!A0) state = wait11;
                        else state = waitfall11;
                        break;
                case wait11:
                        if (!A0) state = wait11;
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
		case waitfall0:	break;
		case wait0: 	break;
		case pb1:
			PORTB = 0x02;
			break;
		case waitfall1: break;
		case wait1:	break;
		case pb2:
			PORTB = 0x04;
			break;
		case waitfall2:	break;
		case wait2:	break;
		case pb11:
			PORTB = 0x02;
			break;
		case waitfall11:break;
		case wait11:	break;
		default: 	break;
	};
}
	
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; // Set port A to input
	DDRB = 0xFF; // Set port B to output
	PORTA = 0xFF; //Init port A to 0xFF
	PORTB = 0x00; // Init port B to 0x00
	TimerSet(300);
	TimerOn();
//	unsigned char tmpB = 0x00;
    /* Insert your solution below */
    while (1) {
	A0 = (PINA & 0x01);
	//User code (i.e. synchSM calls)
//	tmpB = ~tmpB; // Toggle PORTB; Temporary, bad programming style
//	PORTB = tmpB;
	Tick();
	while(!TimerFlag); // Wait 1 sec
	TimerFlag = 0;
    }
    return 1;
}
