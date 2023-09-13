/*
 * Copyright 2022 NXP
 * NXP confidential.
 * This software is owned or controlled by NXP and may only be used strictly
 * in accordance with the applicable license terms.  By expressly accepting
 * such terms or by downloading, installing, activating and/or otherwise using
 * the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to
 * be bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

void configGpio(void);
void configEINT(void);
void delay(uint32_t);

int main(void) {

	configGpio();
	configEINT();

    while(1) {
    	LPC_GPIO0->FIOSET |= 0b11;// se mantienen en 1 las salidas
    }
    return 0 ;
}

void configGpio(void){
	LPC_PINCON->PINSEL0 &= ~(0xf); // pines 0.0 y 0.1 como GPIO
	LPC_GPIO0->FIODIR |= (0x3); // pines 0.0 y 0.1 como salidas
	LPC_PINCON->PINMODE0 |= (1<<1);
	LPC_PINCON->PINMODE0 &= ~(1); // pin 0.0 sin resistencias de pullup o pulldown
	LPC_PINCON->PINMODE0 |= (1<<3);
	LPC_PINCON->PINMODE0 &= ~(1<<2); // pin 0.1 sin resistencias de pullup o pulldown
}

void configEINT(void){
	LPC_PINCON->PINSEL4 |= (1<<20); //se activa eint0
	LPC_PINCON->PINSEL4 |= (1<<22); //se activa eint1
	LPC_SC->EXTMODE |= 1;
	LPC_SC->EXTMODE |= (1<<1); // eint 0 y 1 por flanco
	LPC_SC->EXTPOLAR |= 1; // eint 0 por flanco ascendente
	LPC_SC->EXTPOLAR &= ~(1<<1); // eint1 por flanco descendente
	NVIC_EnableIRQ(EINT0_IRQn); // se habilitan interrupciones por eint0 y eint1
	NVIC_EnableIRQ(EINT1_IRQn);
}

void EINT0_IRQHandler(void){
	LPC_GPIO0->FIOCLR |= 1;
	delay(100);
	LPC_GPIO0->FIOSET |= 1;
	delay(100);
	LPC_GPIO0->FIOCLR |= 1;
	delay(100);
	LPC_GPIO0->FIOCLR |= 1;
	delay(100);
	LPC_GPIO0->FIOSET |= 1;
	delay(100);
	LPC_GPIO0->FIOSET |= 1;
	delay(100);
	LPC_GPIO0->FIOCLR |= 1;
	delay(100);
	LPC_GPIO0->FIOSET |= 1;
	delay(100);
	LPC_GPIO0->FIOCLR |= 1;
	delay(100);
	LPC_SC->EXTINT |= 1; // se limpia la bandera de interrupcion
}

void EINT1_IRQHandler(void){
	LPC_GPIO0->FIOCLR |= 1<<1;
	delay(100);
	LPC_GPIO0->FIOSET |= 1<<1;
	delay(100);
	LPC_GPIO0->FIOSET |= 1<<1;
	delay(100);
	LPC_GPIO0->FIOSET |= 1<<1;
	delay(100);
	LPC_GPIO0->FIOCLR |= 1<<1;
	delay(100);
	LPC_GPIO0->FIOCLR |= 1<<1;
	delay(100);
	LPC_GPIO0->FIOSET |= 1<<1;
	delay(100);
	LPC_GPIO0->FIOSET |= 1<<1;
	delay(100);
	LPC_GPIO0->FIOCLR |= 1<<1;
	delay(100);
	LPC_SC->EXTINT |= (1<<1); // se limpia la bandera de interrupcion
}

void delay(uint32_t ticks){
	for(uint32_t i=0; i<ticks; i++)
			for(uint32_t j=0; j<ticks; j++);
}
