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

int main(void) {

	uint32_t pulsador [2] = {0, 0};
	configGpio();

    while(1) {
    	for(uint32_t i=0; i<2; i++){
			pulsador[i] = (LPC_GPIO0->FIOPIN >> i) & 1; // se lee el pin y se guarda el valor en el arreglo
    	}												//0 corresponde a pulsador presionado en este caso

    }
    return 0 ;
}

void configGpio(void){
	LPC_PINCON->PINSEL0 &= ~(0xf); // P0.0 a P0.1 como GPIO
	LPC_PINCON->PINMODE0 &= ~(0xf); // P0.0 a P0.1 con resistencias de pull up
	LPC_GPIO0->FIODIR &= ~(0b11); // P0.0 a P0.1 como entradas
}
