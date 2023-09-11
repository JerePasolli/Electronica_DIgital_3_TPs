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
uint32_t acumulador = 0;

int main(void) {

    configGpio();
    while(1) {
       if((LPC_GPIO0->FIOPIN>>4) & 1){ //leo P0.4
    	  for(uint32_t i=0; i<=3; i++)
    		  acumulador += LPC_GPIO0->FIOPIN>>i & 1;  //en caso de ser 1 los pines 0 a 3 suman al acumulador
       }
       else{
    	   for(uint32_t i=0; i<=3; i++)
			  acumulador -= LPC_GPIO0->FIOPIN>>i & 1;  //en caso de ser 0 los pines 0 a 3 restan al acumulador

       }
   }
    return 0 ;
}

void configGpio(void){
	LPC_PINCON->PINSEL0 &= ~(0x3ff); // P0.0 a P0.4 como GPIO
	LPC_PINCON->PINMODE0 |= 0x3ff; // P0.0 a P0.4 con resistencias de pull down
	LPC_GPIO0->FIODIR &= ~(0x1f); // P0.0 a P0.4 como entradas
}
