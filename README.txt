Embedded Systems - ECE3140/CS3420

Final Project - FRDM Pedometer

Claire Noel (cmn83)
Kevin Healy (kah279)
Kirsten Scheller (kes334)


	This project turns the FRDM board into a pedometer. We utilize the on-board accelerometer to detect movement in about the board’s z-axis. This information is used to detect steps taken by the user. This zip file includes a full uVision project with I2C and accelerometer implementation. Additionally, we wrote a series of c programs called level, simple switch, pedometer_noSW, and pedometer_wSW. Full integration of the pedometer is realized when pedometer_wSW is uploaded to the board. In order to calibrate the board to the user’s unique gait, the other c files can be used. The level can be used to update the “median” value declared in the pedometer_parameters.h. The user should read the accelerometer value in PuTTY when the board is held at their side in the proper orientation and update the median variable with this value. This will properly count steps when pedometer_wSW is activated.
	To properly use the pedometer, it should be held in one hand, with the reset switch up, and the on-board component facing out and away from you. When the pedometer is ready to begin recording, the LED will be blue. Begin recording by pressing SW3. At this point, begin taking steps and letting your arms swing freely. The on-board LED will turn green while the pedometer is recording. To stop recording, press SW3 again. At this point, the pedometer will flash red for each step taken. If the board is plugged into a computer, the step count will be outputted to a PuTTY window.

	NOTE: Full integration is acheived when pedometer_wSW.c is uploaded to the board.
