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
 * @file pedometer_noSW.c
 * @author Claire Noel, Kevin Healy, Kirsten Scheller
 * @copyright All rights reserved, 2020
 *
 * This is a test case for the FRDM pedometer. This is a hard test case that registers a certain
 * number of steps. It should be used for calibration purposes to adjust for different step size and 
 * gait among users.
 *
 * Here you can input the number of steps you would like to make (line 62) and verify that the pedometer
 * senses this many steps. The results are outputted with the red LED (one flash per step) and in serial print. 
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

	
int main (void)
{
	
	int clock;

	clock=SystemCoreClock;

	LED_Initialize();


	I2C_ReleaseBus(); // Force Restart the bus, this is done via GPIO commands
										// and not via the onboard i2c module

	I2C_Init();				// Initialize I2C bus and Uart Serial Communications
	uart_init();

	uint8_t a = ACCEL_ReadWhoAmI();
	uint8_t b = ACCEL_getDefaultConfig();

	char string[100];
	

	SRAWDATA accelDat;

	

	while (steps>=0){
			delay();
			ACCEL_getAccelDat(&accelDat);
			zval_init = accelDat.z;
			sprintf(yMeas, "ACCELydiff: %f \n\r", zval_init);
			uart_putString(yMeas);
		
		if ( zval_init>median){
			LEDBlue_On();
			if (lastMeas<=median){
				forward ++;
				lastMeas = zval_init;
				steps--;
			}

		}
		else if (zval_init<median){
			LEDGreen_On();
			if (lastMeas>=median){
				back ++;
				lastMeas = zval_init;
				steps--;
			}

		}
		else{
			LED_Off();
		}
	}
	LED_Off();
	int totalSteps = forward+ back-1;
	
	// Serial Print the number of forward swins, back swings, total steps
	sprintf(frontCount, "forward: %d \n\r", forward);
	uart_putString(frontCount);
	sprintf(backCount, "backward: %d \n\r", back);
	uart_putString(backCount);
	sprintf(totalCount , "total steps: %d \n\r", totalSteps);
	uart_putString(totalCount);
	
	delay();
	delay();
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

