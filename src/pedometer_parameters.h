/**
 * @file pedometer_parameters.h
 * @author Claire Noel, Kevin Healy, Kirsten Scheller
 * @copyright All rights reserved, 2020
 *
 * This file holds the global variables for calibration of the pedometer. The median value 
 * should be set for the zval accelerometer reading when the users arms are at their side
 * and the board is flat on their palm, with the pins facing forward and the cord upwards. 
 * 
 * This adjusts for different gait among users.
 *
 */



#ifndef __pedometer_parameters__
#define __pedometer_parameters__

// The number of steps to be tested in the provided test file "pedometer_noSW"
int steps = 14 ;

// Z value accelerometer reading when arms by side.
int median = 0;

#endif