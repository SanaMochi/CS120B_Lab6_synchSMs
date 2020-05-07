/*	Author: Sana
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #6  Exercise 3
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
      unsigned char i = 0x00;

void Tick() {
	switch(state) {
		case start:
			state = Init;
			break;
		case Init:
			PORTB = 0x07;
			state = wait;
			break;
		case wait:
			if (tmpA == 0x00) {	 state = wait;}
			else if (tmpA == 0x01) { state = inc;}
			else if (tmpA == 0x02) { state = dec;}
			else 		       {  state = reset;}
			break;
		case dec:
			if (tmpA == 0x02) {	 state = waitDec;}
			else if (tmpA == 0x03) { state = reset;}
			else {			 state = wait;}
			break;
		case waitDec:
			if (tmpA == 0x02 && i < 10) {	   state = waitDec;}
			else if (tmpA == 0x03 && i < 10) { state = reset;}
			else if (i >= 10) {	 	   state = dec; i = 0;}
			else {			 	   state = wait;}
			break;
		case inc:
			if (tmpA == 0x01) {      state = waitInc;}
                        else if (tmpA == 0x03) { state = reset;}
                        else {                   state = wait;}
			break;
		case waitInc:
			if (tmpA == 0x01 && i < 10) {	   state = waitInc;}
                        else if (tmpA == 0x03 && i < 10) { state = reset;}
			else if (i >= 10) { 	 	   state = inc; i = 0;}
			else { 			 	   state = wait;}
                        break;
		case reset:
                        if (tmpA == 0x03) { state = waitReset;}
                        else {              state = wait;}
			break;
		case waitReset:
			if (tmpA == 0x03) { state = waitReset;}
			else {		    state = wait;}
                        break;
		default:
			PORTB = 0x07;
			state = start;
			break;
	}
	switch(state) {
		case Init:	/*PORTB = 0x07;*/		break;
		case wait:					break;
		case dec:	if (PORTB != 0x00) {PORTB--;}	break;
		case waitDec:	i++;				break;
		case inc:	if (PORTB != 0x09) {PORTB++;}	break;
		case waitInc:	i++;				break;
		case reset:	PORTB = 0x00; 			break;
		case waitReset:					break;
		default:	/*PORTB = 0x07;*/		break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; //PORTA = input
	DDRB = 0xFF; PORTB = 0x07; //PORTB = output

	TimerSet(100);
	TimerOn();

	i = 0x00;
	state = start;

    while (1) {
	tmpA = ~PINA & 0x03;
	Tick();	
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
