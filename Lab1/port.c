/*
 * PORT_Timer.c
 *
 * Created: 24/05/2014 15:33:17
 * Author: Karl Stiller
 * Notes: Porting functions and default init, etc
 *        in this file is where the os/complier dependencies can occur
 */

#include "Port.h"

UINT8 PORT_bEnableInterrupts( void )
{
	/* Enable Global Interrupts */
	sei();
	return 0;
}

UINT8 PORT_bDisableInterrupts( void )
{
	/* Disable Global Interrupts */
	cli();
	return 0;
}
