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


void retardo(uint32_t);
void secuenciaA();
void secuenciaB();
void configGpio(void);
uint32_t delayLeds = 1000;

int main(void) {

	configGpio();

    while(1) {
       secuenciaA();  //se realiza secuencia A, y al terminar se cambia a la secuencia B
       secuenciaB();  // se puede controlar el retardo entre el encendido de cada led
    }
    return 0 ;
}

void configGpio(void){
	LPC_PINCON->PINSEL0 &= ~(0xfffff); // P0.0 a P0.9 como GPIO
	LPC_GPIO0->FIODIR |= 0x3ff; // P0.0 a P0.9 como salidas
}

void retardo(uint32_t cuenta){
	for(uint32_t i=0; i<cuenta; i++)
			for(uint32_t j=0; j<cuenta; j++);
}

void secuenciaA(){
	for(uint32_t i=0; i<=9; i++){
		LPC_GPIO0->FIOSET |= (1<<i);
		retardo(delayLeds);
	}
	for(uint32_t i=0; i<=9; i++){
		LPC_GPIO0->FIOCLR |= (1<<i);
		retardo(delayLeds);
	}

}

void secuenciaB(){
	for(uint32_t i=9; i>=0; i--){
		LPC_GPIO0->FIOSET |= (1<<i);
		retardo(delayLeds);
	}
	for(uint32_t i=9; i>=0; i--){
		LPC_GPIO0->FIOCLR |= (1<<i);
		retardo(delayLeds);
	}

}

