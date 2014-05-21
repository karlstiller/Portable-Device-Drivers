/*
 * PORT_Timer0.c
 *
 * Created: 19/05/2014 21:43:17
 *  Author: Karl Stiller
 */ 
/* Your porting functions and default init, etc                 */
/* in this file is where the os/complier dependencies can occur */
#include "ATMEGA2560.h"
#include "Port.h"
#include "PORT_Timer.h"

/**********************/
/*  Local Variables  */
/**********************/

/* Function pointer to application function */
void ( *pTimerAppFunc)( void ) = 0;

extern void vTimerInterrupt( void );

/**********************/
/* Functions / (ISRs) */
/**********************/

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
	WRITEREG8(TIMSK0, TIMSK0_OCIE0A | TIMSK0_TOIE0);

	sei();	
	/* Timer function executed correctly, return success */
	return 0;
}

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

UINT8 PRT_Timer_bGenerate_Interrupt( void )
{
	/* Force a Output compare match interrupt */
	WRITEREG8( TCCR0B, TCCR0B_FOC0A );
	return 0;
}

UINT8 PRT_Timer_bTest_Callback( void )
{
	/* Make sure the function pointer is valid before calling */
	if ( pTimerAppFunc )
	{
		//  Call application space function 
		pTimerAppFunc();
		return 0;
	}	
	return 1;
}

void test (void)
{
	if( pTimerAppFunc == vTimerInterrupt )
		PRT_IO_bWriteLEDs( 0x04 );
	else
		PRT_IO_bWriteLEDs( 0x05 );
}


/* Timer 0 Compare A Interrupt */
void __vector_21 (void)
{
	/* Make sure the function pointer is valid before calling */
	//if ( pTimerAppFunc )
	//{
		//  Call application space function
		pTimerAppFunc();
	//}
	//test();
	//WRITEREG8( PORTB, ~0x21 );
}

/* Timer 0 Compare B Interrupt */
void __vector_22 (void)
{
	WRITEREG8( PORTB, ~0x22 );
}

/* Timer 0 Overflow ISR*/
void __vector_23 (void)
{
	WRITEREG8( PORTB, ~0x23 );
}

void __vector_20 (void)
{
	WRITEREG8( PORTB, ~0x20 );
}

void __vector_24 (void)
{
	PRT_IO_bWriteLEDs( ~0x24 );
}


