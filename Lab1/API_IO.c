/*
 * API_IO.c
 *
 * Created: 19/05/2014 22:03:27
 *  Author: Karl Stiller
 */
/* THIS FILE HAS NO PORTABLITY dependencies and should not have to    */
/* change for a different environment.                                */
#include "Port.h"
#include "PORT_IO.h"

/*******************************************
 * UINT8 PRT_IO_bInitIO( void )
 * Brief: Function to initialize the io
 *        ports on the development board
 *        the switches. Keys are active
 *        low so an inversion is made
 * Parameters: None
 * Return: 0 - Success
 *         1 - Error
 *******************************************/
UINT8 API_IO_bInitIO( void )
{
	return PRT_IO_bInitIO( );
}

/*******************************************
 * UINT8 ReadSwitches( void )
 * Brief: Function to read the value from
 *        the switches. Keys are active
 *        low so an inversion is made
 * Parameters: None
 * Return: value of switches port
 *******************************************/UINT8 API_IO_bReadSwitches( void ){	return PRT_IO_bReadSwitches( );}/*******************************************
 * UINT8 API_IO_bWriteLEDs( UINT8 bVal )
 * Brief: Function to write the value to
 *        the LED. LEDs are sourced high
 *        so so an inversion is made
 * Parameters: bVal - Value to write to the LEDS
 * Return: 0 - Success
 *         1 - Error
 *******************************************/UINT8 API_IO_bWriteLEDs( UINT8 bVal ){	return PRT_IO_bWriteLEDs( bVal );}