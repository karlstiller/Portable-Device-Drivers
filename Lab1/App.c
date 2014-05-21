/* LAB 3.5 - Writing Portable Device Drivers
 * A fine example of portability
 * Fine for tool demonstration
 * Author: Karl Stiller
 * THIS FILE HAS NO PORTABLITY dependencies and should not have to
 * change for a different environment.
 */

/**********************
 * Includes           *
 **********************/
#include "Port.h"
#include "API_IO.h"
#include "API_Timer.h"
#include "App.h"

/**********************
 * Defines            *
 **********************/
#define DELAY_VAL   ( 0x1A )

/**********************
 * Global variables   *
 **********************/
U8 bDir = 1;
U8 bPrevDir = 1;
U8 bLEDS = 1;

/**********************
 * Functions          *
 **********************/
 
/*******************************************
 * void vTimerInterrupt( void )
 * Brief: Application callback function
 *        must have no parameters and return a void
 * Parameters: None
 * Return: None
 *******************************************/
void vTimerInterrupt( void )
{
	/* If key press matches count value for the key release */
	if (( bLEDS == API_IO_bReadSwitches( )) && ( bLEDS != 0 ))
	{
		/* Has direction already been changed? */
		if( bDir == bPrevDir)
		{
			/* Change direction */
			bDir = !bDir;
		}
	}
	/* Change scan value only when not equal to switches */
	else
	{
		/* Save new value of direction */
		bPrevDir = bDir;

		/* If the count direction is up */
		if( bDir )
		{
			/* Count up */
			bLEDS++;
		}
		/* Otherwise count down */
		else
		{
			/* Count down */
			bLEDS--;
		}
	}
	API_IO_bWriteLEDs( bLEDS );
}


/*******************************************
 * int main(void)                          
 * Brief: The main function                
 * Parameters: None                        
 * Return: Never returns                   
 *******************************************/
int main(void)
{
	API_IO_bInitIO();
	API_Timer_bInitializeTimer( vTimerInterrupt, DELAY_VAL );

	while( 1 )
	{
        /* The operational code is contained in the interrupt functions */
	}
    /* Be nice to the compiler */
	return 0;
}

