/*
 * API_Timer.c
 *
 * Created: 19/05/2014 21:48:07
 *  Author: Karl Stiller
 */
/* THIS FILE HAS NO PORTABLITY dependencies and should not have to    */
/* change for a different environment.                                 */
#include "Port.h"
#include "PORT_Timer.h"

/********************************************/
/* UINT8 bInitializeTimer(					*/
/*			void ( *pTimerFunc)( void ),	*/
/*			UINT8 bVal )					*/
/* Brief: Function to initialize the timer 	*/
/* Parameters: bVal: Max count value		*/
/* Return: 0: timer function executed		*/
/*            correctly						*/
/*         1: an error occurred				*/
/********************************************/
UINT8 API_Timer_bInitializeTimer( void ( *pTimerFunc)( void ), UINT8 bVal )
{
	/* Set application callback function */
	if( PRT_Timer_Set_Callback( pTimerFunc ) )
	{
		return 1;
	}
	/* Initialize Timer */
	if( PRT_Timer_InitializeTimer( bVal ) )
	{
		return 1;
	}
	return 0;
}

UINT8 API_Timer_bGenerate_Interrupt( void )
{
	return PRT_Timer_bGenerate_Interrupt( );
}

UINT8 API_Timer_bTest_Callback( void )
{
	return PRT_Timer_bTest_Callback( );
}

