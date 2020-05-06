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



enum States {start, Init, wait, dec, waitDec, inc, waitInc, reset, waitReset} state;

      unsigned char tmpA;

void Tick() {
	switch(state) {
		case start:
			state = Init;
			break;
		case Init:
			state = wait;
			PORTC = 0x07;
			break;
		case wait:
			if (tmpA == 0x00) {	 state = wait;}
			else if (tmpA == 0x01) { state = inc;}
			else if (tmpA == 0x02) { state = dec;}
			else 		       {  state = reset;}
			break;
		case dec:
//			state = waitDec;
			if (tmpA == 0x02) {	 state = waitDec;}
			else if (tmpA == 0x03) { state = reset;}
			else {			 state = wait;}
			break;
		case waitDec:
			if (tmpA == 0x02) {	 state = waitDec;}
			else if (tmpA == 0x03) { state = reset;}
			else {			 state = wait;}
			break;
		case inc:
//			state = waitInc;
			if (tmpA == 0x01) {      state = waitInc;}
                        else if (tmpA == 0x03) { state = reset;}
                        else {                   state = wait;}
			break;
		case waitInc:
			if (tmpA == 0x01) {	 state = waitInc;}
                        else if (tmpA == 0x03) { state = reset;}
			else { 			 state = wait;}
                        break;
		case reset:
//			state = waitReset;
                        if (tmpA == 0x03) { state = waitReset;}
                        else {              state = wait;}
			break;
		case waitReset:
			if (tmpA == 0x03) { state = waitReset;}
			else {		    state = wait;}
                        break;
		default:
			PORTC = 0x07;
			state = start;
			break;
	};
	switch(state) {
		case Init:					break;
		case wait:					break;
		case dec:	if (PORTC != 0x00) {PORTC--;}	break;
		case waitDec:					break;
		case inc:	if (PORTC != 0x09) {PORTC++;}	break;
		case waitInc:					break;
		case reset:	PORTC = 0x00;			break;
		case waitReset:					break;
		default:					break;
	};
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; //PORTA = input
	DDRC = 0xFF; PORTC = 0x00; //PORTB = output

	TimerSet(100);
	TimerOn();

	state = start;
    while (1) {
	tmpA = ~PINA & 0x03;
	Tick();	
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
