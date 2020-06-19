#include "fsl_common.h"
#include "3140_accel.h"
#include "3140_serial.h"
#include "3140_i2c.h"

#include <stdio.h>

#include "3140_concur.h"
#include "utils.h"
#include "Math.h"

static char accelStart[100];
static char accelFinal[100];
static char xdiff[100];
static char ydiff[100];
static char zdiff[100];
static char totdiff[100];


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
	
	float xval_init = 0;
	float yval_init = 0;
	float zval_init = 0;
	float xval_fin = 0;
	float yval_fin = 0;
	float zval_fin = 0;
			
	for(;;){
		
			ACCEL_getAccelDat(&accelDat);
			sprintf(accelStart, "ACCELStart: ( %d, %d, %d ) S: %d \n\r",accelDat.x,accelDat.y,accelDat.z,accelDat.s);
		//sprintf(accelStart, "ACCELStart: ( %d ) S: %d \n\r",accelDat.z);
			uart_putString(accelStart);
			xval_init = accelDat.x;
			yval_init = accelDat.y;
			zval_init = accelDat.z;
		
		if (xval_init<150 && xval_init>-150){
			//LEDBlue_On();
		}
		else if (yval_init<150 && yval_init>-150){
			//LEDGreen_On();
		}
		else if (zval_init<150 && zval_init>-150){
			LEDRed_On();
		}
		else{
			LED_Off();
		}
	}
	
	
	
	
	
	/*
	ACCEL_getAccelDat(&accelDat);
	sprintf(accelFinal, "ACCELfinish: ( %d, %d, %d ) S: %d \n\r",accelDat.x,accelDat.y,accelDat.z,accelDat.s);
	uart_putString(accelFinal);
			
	xval_fin = accelDat.x;
	yval_fin = accelDat.y;
	zval_fin = accelDat.z;
	
	LED_Off();
	
	
	// Maths
	float xval_diff = fabs(xval_fin - xval_init);
	float yval_diff = fabs(yval_fin - yval_init);
	float zval_diff = fabs(zval_fin - zval_init);
	float tot_diff = sqrtf(powf(xval_diff,2) + powf(yval_diff,2) + powf(zval_diff,2)) ;
	
	
	sprintf(xdiff, "ACCELxdiff: %f \n\r", xval_diff);
	uart_putString(xdiff);
	sprintf(ydiff, "ACCELydiff: %f \n\r", yval_diff);
	uart_putString(ydiff);
	sprintf(zdiff, "ACCELzdiff: %f \n\r", zval_diff);
	uart_putString(zdiff);
	sprintf(totdiff, "ACCELtotdiff: %f \n\r", tot_diff);
	uart_putString(totdiff);
	
	*/
	while (1) ;

	return 0;
}
