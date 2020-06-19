#include "fsl_common.h"
#include "3140_accel.h"
#include "3140_serial.h"
#include "3140_i2c.h"
#include <stdio.h>
#include "3140_concur.h"
#include "utils.h"
#include "shared_structs.h"
//#include <MK64F12.h>

/* the point of this file is simply to configure the SW2 and SW3 push buttons on the board.
The goal is to provide an interrupt(Green flash) when SW2 is pressed,
then run a different response (blue toggle) SW3 is pressed */



int main (void){
	int clock;

	clock=SystemCoreClock;

	LED_Initialize();

	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; /*Enable Port B Clock Gate Control*/
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK; /*Enable Port C Clock Gate Control*/
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; /*Enable Port A Clock Gate Control*/
	PORTB->PCR[23] = 0x100;
	PORTC->PCR[6] = 0x90100; //Push button SW2
	PORTA->PCR[4] = 0x90100; //Push button SW3
	GPIOB->PDDR |= (1 << 23); //external LED connected to PTB-23 pin
	GPIOC->PDDR |= (0 << 6); //Push button SW2 connected to PORTC-6
	GPIOA->PDDR |= (0 << 4); //Push button SW3 connected to PORTA-4
	//PORTC->ISFR = PORT_ISFR_ISF(0x40); /* Clear interrupt status flag */
	//PORTA->ISFR = PORT_ISFR_ISF(0x10);
	NVIC_EnableIRQ(PORTC_IRQn); /*Enable the PORTC interrupt*/
	NVIC_EnableIRQ(PORTA_IRQn);
	
while (1){
	
	//LED_Off();
	
}
return 0;
}


void PORTC_IRQHandler(void)
{ 
	PORTC->ISFR = PORT_ISFR_ISF(0x40);
	
//GPIOB->PSOR |= (1 <<23); //Turn on external LED
	LEDGreen_On();
	delay();
	LED_Off();
}

void PORTA_IRQHandler(void)
{ 
	PORTA->ISFR = PORT_ISFR_ISF(0x10);
	LEDBlue_On();
	delay();
	LED_Off();

}

 //end of main.c