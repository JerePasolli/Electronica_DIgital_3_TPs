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

void consifgGpio(void);
void configGpioInt(void);
void delay(uint32_t);

int main(void) {

	configGpio();
	configGpioInt();

    while(1) {
    	LPC_GPIO0->FIOSET |= 0b11;// se mantienen en 1 las salidas
    }
    return 0 ;
}

void configGpio(void){
	LPC_PINCON->PINSEL0 &= ~(0xf); // pines 0.0 y 0.1 como GPIO
	LPC_PINCON->PINSEL4 &= ~(0xf); // pines 2.0 y 2.1 como GPIO
	LPC_PINCON->PINMODE4 |= (0x3); // pin 2.0 con pulldown
	LPC_PINCON->PINMODE4 &= ~(0x3<<2); // pin 2.0 con pullup
	LPC_PINCON->PINMODE0 |= (1<<1);
	LPC_PINCON->PINMODE0 &= ~(1); // pin 0.0 sin resistencias de pullup o pulldown
	LPC_PINCON->PINMODE0 |= (1<<3);
	LPC_PINCON->PINMODE0 &= ~(1<<2); // pin 0.1 sin resistencias de pullup o pulldown
	LPC_GPIO2->FIODIR &= ~(0x3); // pines 2.0 y 2.1 como entradas
	LPC_GPIO0->FIODIR |= (0x3); // pines 0.0 y 0.1 como salidas
}

void configGpioInt(void){
	LPC_GPIOINT->IO2IntEnR |= 1; // interrupcion por flanco ascendete en p2.0
	LPC_GPIOINT->IO2IntEnF |= 1; // interrupcion por flanco descendente en p2.1
	NVIC_EnableIRQ(EINT3_IRQn);
}

void EINT3_IRQHandler(void){
	if(LPC_GPIOINT->IO2IntStatF & 1){ // interrupcion por p2.0
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
		LPC_GPIOINT->IO0IntClr |= 1; // limpiar flag de interrupcion
	}
	else{ // interrupcion por p2.1
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
		LPC_GPIOINT->IO0IntClr |= 1<<1; // limpiar flag de interrupcion
	}

}

void delay(uint32_t ticks){
	for(uint32_t i=0; i<ticks; i++)
			for(uint32_t j=0; j<ticks; j++);
}
