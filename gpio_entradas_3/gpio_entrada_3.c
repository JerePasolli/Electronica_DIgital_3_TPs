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
void delay(uint32_t);
void readPort1(void);
void writePort0(void);

int dataReaded [16];

int main(void) {

	configGpio();

    while(1) {
    	readPort1();
    	writePort0();
    	delay(1000000);
    }
    return 0 ;
}

void configGpio(void){
	LPC_GPIO1->FIODIR &= 0x00000000; // Todos los pines del puerto 1 como entradas
	LPC_GPIO0->FIODIR |= 0xffffffff; // Todos los pines del puerto 0 como salidas
}

void delay(uint32_t ticks){
	for(uint32_t i=0; i<ticks; i++)
			for(uint32_t j=0; j<ticks; j++);
}

void readPort1(void){  // se leen 16 bits menos significativos del puerto 1 y se almacenan en dataReaded
	dataReaded[0] = LPC_GPIO1->FIOPIN & 1;
	dataReaded[1] = (LPC_GPIO1->FIOPIN>>1) & 1;
	dataReaded[2]= (LPC_GPIO1->FIOPIN>>4) & 1;
	for(int i=8; i<=10; i++)
		dataReaded[i-5] = (LPC_GPIO1->FIOPIN>>i) & 1;
	for(int b=14; b<=23; b++)
			dataReaded[b-8] = (LPC_GPIO1->FIOPIN>>b) & 1;
}


void writePort0(void){ //los 16 bits leidos se escriben en el puerto 1
	LPC_GPIO0->FIOCLR = 0xffffffff;
	for(int i=0; i<11; i++){
		if(dataReaded[i]){
			LPC_GPIO0->FIOPIN |= (1<<i);
		}
		else{
			LPC_GPIO0->FIOPIN &= ~(1<<i);
		}
	}
	for(int b=12; b<16; b++){
		if(dataReaded[b]){
			LPC_GPIO0->FIOPIN |= (1<<(b+3));
		}
		else{
			LPC_GPIO0->FIOPIN &= ~(1<<(b+3));
		}
	}

}
