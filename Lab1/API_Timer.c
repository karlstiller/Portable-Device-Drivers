/*
 * API_Timer.c
 *
 * Created: 19/05/2014 21:48:07
 * Author: Karl Stiller
 * THIS FILE HAS NO PORTABLITY dependencies and should not have to
 * change for a different environment.
 */

/**********************
 * Includes           *
 **********************/
#include "Port.h"
#include "PORT_Timer.h"

/**********************/
/* Functions          */
/**********************/

/********************************************
 * UINT8 bInitializeTimer(					
 *			void ( *pTimerFunc)( void ),	
 *			UINT8 bVal )					
 * Brief: Function to initialize the timer 	
 * Parameters: pTimerFunc - Pointer to a function with no parameters and no
 *                         return value.
 *             bVal       - Max count value		
 * Return: 0 - Success
 *         1 - Error
 ********************************************/
UINT8 API_Timer_bInitializeTimer( void ( *pTimerFunc)( void ), UINT8 bVal )
{
	/* Set application callback function */
	if( PRT_Timer_bSet_Callback( pTimerFunc ) )
	{
		return 1;
	}
	/* Initialize Timer */
	if( PRT_Timer_bInitializeTimer( bVal ) )
	{
		return 1;
	}
	return 0;
}

/*******************************************
 * UINT8 API_Timer_bGenerate_Interrupt( void )
 * Brief: Attempt at a test function to force a hardware interrupt on OC0A.
 *        TESTED AS _NOT_ WORKING - DO NOT USE!!
 * Parameters: none
 * Return: 0 - Success
 *         1 - Error
 *******************************************/
UINT8 API_Timer_bGenerate_Interrupt( void )
{
	return PRT_Timer_bGenerate_Interrupt( );
}

/*******************************************
 * UINT8 API_Timer_bTest_Callback( void )
 * Brief: Test function for API to call callback function by software
 * Parameters: none
 * Return: 0 - Success
 *         1 - Error
 *******************************************/
UINT8 API_Timer_bTest_Callback( void )
{
	return PRT_Timer_bTest_Callback( );
}

