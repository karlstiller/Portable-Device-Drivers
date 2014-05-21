/*
 * PORT_IO.c
 *
 * Created: 19/05/2014 22:02:48
 * Author: Karl Stiller
 *
 * Your porting functions and default init, etc
 * in this file is where the os/complier dependencies can occur
 */


/**********************
 * Includes           *
 **********************/
#include "Port.h"
#include "PORT_IO.h"

/**********************
 * Functions          *
 **********************/

/*******************************************
 * UINT8 PRT_IO_bInitIO( void )
 * Brief: Function to initialize the io
 *        ports on the development board
 *        the switches. Keys are active
 *        low so an inversion is made
 * Parameters: None
 * Return: 0 - Success
 *         1 - Error
 *******************************************/UINT8 PRT_IO_bInitIO( void ){	/* Set LED port as output */	WRITEREG8( LEDS_DIR, 0xFF );
	/* Set switches port as input */
	WRITEREG8( SWITCHES_DIR, 0 );
	/* Initial state is all LEDs off */
	PRT_IO_bWriteLEDs( 0 );	return 0;}

/*******************************************
 * UINT8 ReadSwitches( void )
 * Brief: Function to read the value from
 *        the switches. Keys are active
 *        low so an inversion is made
 * Parameters: None
 * Return: value of switches port
 *******************************************/
UINT8 PRT_IO_bReadSwitches( void )
{
	return ~READREG8( SWITCHES );
}/*******************************************
 * UINT8 bWriteLEDs( UINT8 bVal )
 * Brief: Function to write the value to
 *        the LED. LEDs are sourced high
 *        so so an inversion is made
 * Parameters: bVal - Value to write to the LEDS
 * Return: 0 - Success
 *         1 - Error
 *******************************************/UINT8 PRT_IO_bWriteLEDs( UINT8 bVal ){	WRITEREG8( LEDS, ~bVal );	return 0;}