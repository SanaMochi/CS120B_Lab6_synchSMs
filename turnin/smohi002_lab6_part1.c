/*	Author: Sana
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #6  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

//Demo: https://drive.google.com/open?id=1yZJrdVppp_-VeKeV-9uQJaxO2dLd7I0l
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif

enum States {start, pb0, pb1, pb2} state;

void Tick() {
	switch(state) {
		case start:
			state = pb0;
			break;
		case pb0:
			state = pb1;
			break;
		case pb1:
			state = pb2;
			break;
		case pb2:
			state = pb0;
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
		default:
			break;
	};
}
	
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; // Set port B to output
	PORTB = 0x00; // Init port B to 0x
	TimerSet(1000);
	TimerOn();
//	unsigned char tmpB = 0x00;
    /* Insert your solution below */
    while (1) {
	//User code (i.e. synchSM calls)
//	tmpB = ~tmpB; // Toggle PORTB; Temporary, bad programming style
//	PORTB = tmpB;
	Tick();
	while(!TimerFlag); // Wait 1 sec
	TimerFlag = 0;
    }
    return 1;
}
