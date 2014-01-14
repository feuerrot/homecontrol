// coding: utf-8
#include <avr/io.h>
#include <avr/interrupt.h>
#include "rs232.h"


void init(void){
	TCCR2 |= (1<<WGM21)|(1<<WGM20)|(1<<CS20);
	DDRB |= (1<<PB3);
	_usart_init();
	sei();
}

void timer_stop(void){
	TCCR2 &= ~((1<<COM21)|(1<<COM20));
}

void timer_start(void){
	TCCR2 |= (1<<COM21)|(1<<COM20);
}

int main(void){
	init();

	while(1){
	}
	return 0;
}

ISR(USART_RXC_vect){
	uint8_t chr = UDR;
	if (chr == 0x00){
		timer_stop();
		PORTB |= (1<<PB3);
	} else if (chr == 0xff) {
		timer_stop();
		PORTB &= ~(1<<PB3);
	} else {
		timer_start();
		OCR2 = chr;
	}
}
