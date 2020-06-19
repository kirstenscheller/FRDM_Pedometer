#include "fsl_common.h"
#include "3140_accel.h"
#include "3140_serial.h"
#include "3140_i2c.h"
#include <stdio.h>
#include "3140_concur.h"
#include "utils.h"
#include "Math.h"
#include "pedometer_parameters.h"

/**
 * @file pedometer_wSW.h
 * @author Claire Noel, Kevin Healy, Kirsten Scheller
 * @copyright All rights reserved, 2020
 *
 * This is the main program for the FRDM pedometer. The pedometer will begin counting steps from the time 
 * SW3 is pressed and will stop counting when SW3 is pressed. It will then indicate the number of steps taken.
 *
 * Press the reset button to begin a new path. 
 */

// Values that can be serial printed. These can be viewed using PuTTY for Windows.
static char frontCount[100];
static char backCount[100];
static char totalCount[100];
static char yMeas[100];

//Global Variables
float zval_init = 0;
int forward = 0;
int back = 0;
float lastMeas = 0;

int runFlag = 0; // the flag to indicate if the pedometer is running. 0 if not running and 1 if yes running

// global variable to keep track of whether the switch has been pressed
int SW3Pressed = 0;				// SW3 button

int main (void){
	int clock;

	clock=SystemCoreClock;

	LED_Initialize();

	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; /*Enable Port A Clock Gate Control*/
	PORTA->PCR[4] = 0x90100; //Push button SW3
	GPIOA->PDDR |= (0 << 4); //Push button SW3 connected to PORTA-4
	NVIC_EnableIRQ(PORTA_IRQn);  /*Enable the PORTA interrupt*/
	
	
	I2C_ReleaseBus(); // Force Restart the bus, this is done via GPIO commands
										// and not via the onboard i2c module

	I2C_Init();				// Initialize I2C bus and Uart Serial Communications
	uart_init();

	uint8_t a = ACCEL_ReadWhoAmI();
	uint8_t b = ACCEL_getDefaultConfig();

	char string[100];
	

	SRAWDATA accelDat;
	
	while(SW3Pressed==0){
			LEDBlue_On();
	}
	
	LED_Off();
  SW3Pressed=0;
	
	while (SW3Pressed==0){ // SW3 acts a run flag for the recording period.
			delay();
			LEDGreen_On();
			ACCEL_getAccelDat(&accelDat);
			zval_init = accelDat.z;
			sprintf(yMeas, "ACCELydiff: %f \n\r", zval_init);
			uart_putString(yMeas);
		
		if ( zval_init>median){
			if (lastMeas<=median){ // only count true swings. Want to increment counter not for duplicate measures.
				// This is because the accelerometer is giving readings faster than the arm is swinging.
				forward ++;
				lastMeas = zval_init; // Update the temporary compare-to value.
			}

		}
		else if (zval_init<median){
			if (lastMeas>=median){
				back ++;
				lastMeas = zval_init;
			}

		}
		else{
			LED_Off();
		}
	}
	LED_Off();
	
	int totalSteps = forward+ back;
	
	// Serial Print the number of forward swins, back swings, total steps
	sprintf(frontCount, "forward: %d \n\r", forward);
	uart_putString(frontCount);
	sprintf(backCount, "backward: %d \n\r", back);
	uart_putString(backCount);
	sprintf(totalCount , "total steps: %d \n\r", totalSteps);
	uart_putString(totalCount);
	
	
	// Blink red to indicate # steps taken
	while(totalSteps>0) {
		LEDRed_On();
		delay();
		LED_Off();
		delay();
		totalSteps--;
	}
	

	while (1) ;

	return 0;
}


// INTERRUPT HANDLERS


void PORTA_IRQHandler(void)
{ 
		PORTA->ISFR = PORT_ISFR_ISF(0x10);
	//LED_Off(); 
	  SW3Pressed = 1;
}




//end of main.c
