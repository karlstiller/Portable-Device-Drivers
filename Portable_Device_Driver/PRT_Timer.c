/*
 * PORT_Timer.c
 *
 * Created: 19/05/2014 21:43:17
 * Author: Karl Stiller
 * Notes: Porting functions and default init, etc
 *        in this file is where the os/complier dependencies can occur
 */

/**********************
 * Includes           *
 **********************/
#include "ATMEGA2560.h"
#include "PRT_API.h"
#include "PRT_Timer.h"

/**********************
 * Local Global Vars  *
 **********************/
/* Function pointer to application function */
void ( *pTimerAppFunc)( void ) = 0; 

/**********************/
/* Functions / (ISRs) */
/**********************/

/*******************************************
 * UINT8 PRT_Timer_bInitializeTimer( UINT8 bVal )
 * Brief: Function to initialize the timer
 * Parameters: bVal - value for the output compare reg
 * Return: 0 - Success
 *         1 - Error
 *******************************************/
UINT8 PRT_Timer_bInitializeTimer( UINT8 bVal )
{
	/* Clear all bits of the general timer counter control register */
	WRITEREG8( GTCCR, (UINT8)!GTCCR_PSRSYNC );
	/* Clear all pending interrupts */
	WRITEREG8( TIFR0, TIFR0_TOV0 | TIFR0_OCF0A | TIFR0_OCF0B );
	/* Confirm that timer is in normal operation mode */
	WRITEREG8( TCCR0A, TCCR0A_CTC );
	/* Set clock select div 1024 */
	WRITEREG8( TCCR0B, TCCR0B_CLK_1024 );
	/* Set compare register to preset value */
	WRITEREG8( OCR0A, bVal );
	/* Set timer counter to preset value */
	WRITEREG8( TCNT0, 0 );
	/* Enable Output Timer Output Compare Match A Interrupt Enable */
	WRITEREG8(TIMSK0, TIMSK0_OCIE0A );

	/* Timer function executed correctly, return success */
	return 0;
}

/*******************************************
 * UINT8 PRT_Timer_bSet_Callback( void ( *pTimerFunc)( void ) )
 * Brief: Function to set application callback function
 * Parameters: pTimerFunc - pointer to a function with no parameters and no 
 *             return value.
 * Return: 0 - Success
 *         1 - Error
 *******************************************/
UINT8 PRT_Timer_bSet_Callback( void ( *pTimerFunc)( void ) )
{
	/* Make sure Timer function is set properly */
	if( pTimerFunc )
	{
		pTimerAppFunc = pTimerFunc;
		return 0;
	}
	return 1;
}

/*******************************************
 * UINT8 PRT_Timer_bGenerate_Interrupt( void )
 * Brief: Attempt at a test function to force a hardware interrupt on OC0A.
 *        TESTED AS NOT WORKING - DO NOT USE!!
 * Parameters: none
 * Return: 0 - Success
 *         1 - Error
 *******************************************/
UINT8 PRT_Timer_bGenerate_Interrupt( void )
{
	/* Force a Output compare match interrupt */
	WRITEREG8( TCCR0B, TCCR0B_FOC0A );
	return 0;
}

/*******************************************
 * UINT8 PRT_Timer_bTest_Callback( void )
 * Brief: Test function for API to call callback function by software
 * Parameters: none
 * Return: 0 - Success
 *         1 - Error
 *******************************************/
UINT8 PRT_Timer_bTest_Callback( void )
{
	/* Make sure the function pointer is valid before calling */
	if ( pTimerAppFunc )
	{
		/*  Call application space function */
		pTimerAppFunc();
		return 0;
	}	
	return 1;
}


/*******************************************
 * void ISR_TIMER0_COMPA (void)
 * Brief: Timer 0 Compare A ISR __vector_21
 * Parameters: none
 * Return: none
 *******************************************/
void ISR_TIMER0_COMPA (void)
{
	/* Make sure the function pointer is valid before calling */
	if ( pTimerAppFunc )
	{
		/* Call application space function */
		pTimerAppFunc();
	}
}

/*******************************************
 * void ISR_TIMER0_COMPA (void)
 * Brief: Timer 0 Compare B ISR __vector_22
 * Parameters: none
 * Return: none
 *******************************************/
void ISR_TIMER0_COMPB (void)
{
	
}

/*******************************************
 * void ISR_TIMER0_COMPA (void)
 * Brief: Timer 0 Overflow ISR __vector_23
 * Parameters: none
 * Return: none
 *******************************************/
void ISR_TIMER0_OVF (void)
{
	
}


