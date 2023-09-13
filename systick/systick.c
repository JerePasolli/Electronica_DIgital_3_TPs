
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>


void configGpio(void);
void configEINT(void);
void configSystick(void);


int counter = 1;
int secuencia = 0;

int main(void) {


    while(1) {

    }
    return 0 ;
}

void configGpio(void){
	LPC_PINCON->PINSEL1 &= ~(0x3<<12); // P0.22 como GPIO
	LPC_GPIO0->FIODIR |= (1<<22); // P0.22 como salida
	LPC_PINCON->PINMODE1 |= (1<<13); // Po.22 sin pullup/pulldown
}

void configEINT(void){
	LPC_PINCON->PINSEL4 |= (1<<20); //habilito pin EINT0
	LPC_SC->EXTMODE |= 1; // EINT0 por flanco
	LPC_SC->EXTPOLAR |= 1; // EINT0 por flanco de subida
	NVIC_SetPriority(EINT0_IRQn, 3); // piroridad 1
	NVIC_EnableIRQ(EINT0_IRQn); // se habilita interrupcion EINT0
}

void configSystick(void){
	SysTick->LOAD = (600000-1); //se carga valor al contador npara que interrumpa cada 1ms (cclk de 80 Mhz)
	SysTick->VAL = 0; // se setea valor actuala a 0
	NVIC_SetPriority(SysTick_IRQn, 1); // se setea prioridad alta
	SysTick->CTRL |= 1 | (1<<1) | (1<<2); // se habilita contador, interrupcion y se seleccion cclk

}

void SysTick_Handler(void){
	if (secuencia){
		if (counter == 1 || counter == 2 || counter == 3 || counter == 4 || counter == 12 ||counter == 13
					|| counter == 14 || counter == 15 || counter == 6 || counter == 8 || counter == 10){ // se debe enviar 0 por el pin
			LPC_GPIO0 -> FIOCLR |= (1<<22);
		}
		else{ // caso contrario se envia 1, para respetar la secuencia
			LPC_GPIO0->FIOSET |= (1<<22);
		}
	}

	else{
		LPC_GPIO0->FIOSET |= (1<<22); // si hubo interrupcion por eint se deja de enviar secuencia
	}


	counter ++;
	if (counter == 16)
		counter = 1;
}

void EINT0_IRQHandler(void){
	secuencia = !secuencia; // cada interrupcion inicia o detiene secuencia
}
