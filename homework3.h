/*
 * homework3.h
 *
 *  Created on:
 *      Author:
 */



#ifndef HOMEWORK3_H_
#define HOMEWORK3_H_

// This function initializes the board by turning off the Watchdog Timer.
void initBoard();
// This function indexes a count value to an LED color on Launchpad LED2.
void changeLaunchpadLED2(unsigned int count);
// This function indexes a count value to an LED color on the Boosterpack LED.
void changeBoosterpackLED(unsigned int count);
// This function serves as a debounce state machine for Boosterpack button S1
bool fsmBoosterpackButtonS1(unsigned char buttonhistory);


// TODO: Define any constants that are local to homework.c using #define
#define PRESSED_BUTTON     0x00
#define UNPRESSED_BUTTON   0xFF
#define MASK        0b111

#endif /* HOMEWORK3_H_ */
