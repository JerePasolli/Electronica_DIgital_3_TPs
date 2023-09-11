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
uint32_t numDisplay [10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67};
uint32_t delayLeds = 1000;

int main(void) {

    while(1) {
      for(uint32_t i=0; i<10; i++){
    	  LPC_GPIO2->FIOSET |= numDisplay[i]; // Muestra numeros del 0 al 9 indefinidamente en display
    	  retardo(delayLeds);
      }
    }
    return 0 ;
}

void configGpio(void){
	LPC_PINCON->PINSEL4 &= ~(0xffff); // P2.0 a P2.7 como GPIO
	LPC_GPIO2->FIODIR |= 0xff; // P2.0 a P2.7 como salidas
}

void retardo(uint32_t cuenta){
	for(uint32_t i=0; i<cuenta; i++)
			for(uint32_t j=0; j<cuenta; j++);
}
